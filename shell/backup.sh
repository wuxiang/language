# /bin/bash

# Nebutown Database Backup Tool v1.0
# Author : Xielingjun
#===================================================================================
#
#                            Configuration Fields
#
#===================================================================================
BACKUP_DEST_IP=192.168.3.6  #<---Edit
BACKUP_DEST_USER=tom        #<---Edit
BACKUP_DEST_DIR=dbbackup    #<---Edit
#===================================================================================


# The name-format for snapshot dir (and incremental log tarball)
TIMESTAMP_FORMAT="%Y%m%d%H%M"
DB_TAR_BALL="db.tar.gz"
# File containing latest snapshot info
SNAPSHOT_RECORD="LAST_SNAPSHOT"
# BDB-associated settings
declare -a REGION_FILES=("__db.register" "__db.001" "__db.002" "__db.003" "__db.004" "__db.005" "__db.006")

# the array to hold all database envs
declare -a DB_ENVS=()
function get_all_db_envs
{
    # for dbcore/
    for dir in ./dbcore/* ./dbmedia/*
    do
        if [ -d $dir ]
        then
            DB_ENVS+="$dir "
        fi
    done
}

# the array to hold all logs
declare -a DB_LOGS=()
function get_all_db_logs
{
    for envdir in ${DB_ENVS[@]}
    do
        #echo "Searching logs in $envdir"
        log_files=(`db5.1_archive -l -h $envdir 2>/dev/null`)
        if [ $? -eq 0 ]; then
            for file in ${log_files[@]}; do
                # append to the global logfile array
                DB_LOGS=("${DB_LOGS[@]}" "$envdir/$file")
            done
        fi
    done
}

function make_checkpoint
{
    for envdir in ${DB_ENVS[@]}
    do
        echo "Making checkpoint on $envdir, please wait ..."
        (cd $envdir && db5.1_checkpoint -1)
        if [ $? -ne 0 ]; then
            echo "ERROR : checkpoint failure for $envdir."
            exit 1
        fi
    done
}

function remove_unused_log_files
{
    for envdir in ${DB_ENVS[@]}
    do
        echo "Remove unused log files in $envdir, please wait ..."
        (cd $envdir && db5.1_archive -d)
        if [ $? -ne 0 ]; then
            echo "ERROR : rm log file failed for $envdir."
            exit 1
        fi
    done
}

function remove_all_log_files
{
    for envdir in ${DB_ENVS[@]}
    do
        echo "Remove all log files in $envdir, please wait ..."
	(cd $envdir && find . -name "log.*" -exec rm {} \;)
        if [ $? -ne 0 ]; then
            echo "ERROR : rm log file failed for $envdir."
            exit 1
        fi
    done
}

function remove_region_files
{
    for envdir in ${DB_ENVS[@]}
    do
        echo "Remove region files in $envdir, please wait..."
        for region_file in ${REGION_FILES[@]}; do
            if [ -f $envdir/$region_file ]; then
                rm $envdir/$region_file
            fi
        done
    done
}

function reset_log_lsn()
{
    for envdir in ${DB_ENVS[@]}
    do
        dbfile=(`cd $envdir && find . -name "*.db"`)
	if [ -z "$dbfile" ]; then
            echo "No database file in $envdir, just ignore"
        else
            echo "Reset LSNs for $envdir, please wait..."
            (cd $envdir && find . -name "*.db" -exec db5.1_load -r lsn {} \;)
            if [ $? -ne 0 ]; then
                echo "ERROR : reset LSN failure for $envdir."
                exit 1
            fi
        fi
    done
}

# check if the dir exists on the remote backup server (using cd)
function check_snapshot_dir()
{
    # The first argument is snapshot-timestamp
    snapshot_dir=/home/$BACKUP_DEST_USER/$BACKUP_DEST_DIR/$1

    ssh $BACKUP_DEST_USER@$BACKUP_DEST_IP cd $snapshot_dir 1>/dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo "ERROR : Snapshot dir '$snapshot_dir' not found on '$BACKUP_DEST_IP'"
        exit 1
    fi
}

function check_log_tag()
{
    # The first argument is snapshot-timestamp
    snapshot_dir=/home/$BACKUP_DEST_USER/$BACKUP_DEST_DIR/$1       
    # The second argument is log-tag-timestamp
    logs_tar_ball="logs-$2.tar.gz"

    ssh $BACKUP_DEST_USER@$BACKUP_DEST_IP ls $snapshot_dir/$logs_tar_ball 1>/dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo "ERROR : Log tag  '$snapshot_dir/$logs_tar_ball' not found on '$BACKUP_DEST_IP'"
        exit 1
    fi
}

function check_last_snapshot()
{
    # last snapshot info is stored in a text file $SNAPSHOT_RECORD
    if [ -f $SNAPSHOT_RECORD ]; then
        snapshot_time=(`cat $SNAPSHOT_RECORD`)
        echo "Last snapshot : $snapshot_time"
        check_snapshot_dir $snapshot_time
    else
        echo "ERROR : You should make a snapshot-backup first before using incremental-backup."
        exit 1
    fi
}

function sync_log_files()
{
    echo "Syncing log files with the backup server ..."
    for dir in ./dbcore ./dbmedia; do
        rsync -avz --include "*/" --include "log.*" --exclude "*" $dir  $BACKUP_DEST_USER@$BACKUP_DEST_IP:$snapshot_dir/
        if [ $? -ne 0 ]; then
            echo "ERROR : Sync log files for ./dbcore/ failed."
            exit 1
        fi
    done
}

function tag_log_files()
{
    echo "Makinga a tag for this incremental backup ..."
    inc_time=(`date +$TIMESTAMP_FORMAT`)
    logs_tar_ball="logs-$inc_time.tar.gz"
    ssh $BACKUP_DEST_USER@$BACKUP_DEST_IP "cd $snapshot_dir; tar czvf $logs_tar_ball ./dbcore ./dbmedia"
    if [ $? -ne 0 ]; then
        echo "ERROR : Create tag '$logs_tar_ball' for logs failed on '$BACKUP_DEST_IP'"
        exit 1
    fi
}

function catastrophic_recover()
{
    for envdir in ${DB_ENVS[@]}
    do
        echo "Recover database in $envdir, please wait..."
        (cd $envdir && db5.1_recover -c)
        if [ $? -ne 0 ]; then
            echo "ERROR : Catastrophic recover for '$envdir' failed."
            exit 1
        fi
    done
}

function usage()
{
    echo "usage : $0"
    echo "    --snapshot : make a complete backup of the whole databse (also remove redundant logs)"
    echo "    --inc      : make an incremental backup on the newly-generated logs"
    echo "    --fetch snapshot-time [log-time]"
    echo "               : fetch database from the backup server with a snapshot-timestamp and (optional) log-timestamp"
    echo "    --reset    : init the database for further snapshot-backup and incremental backup (needed only once)"
}


# Get a list of in-use bdb envs
get_all_db_envs

#get_all_db_logs

case $1 in
    --snapshot)
        echo "Making snapshot ..."
        # checkpint all db envs
        make_checkpoint

        # remove unused log files
        remove_unused_log_files

        # mkdir snapshot dir on backup server
        snapshot_time=(`date +$TIMESTAMP_FORMAT`)
        snapshot_dir=/home/$BACKUP_DEST_USER/$BACKUP_DEST_DIR/$snapshot_time
        ssh $BACKUP_DEST_USER@$BACKUP_DEST_IP mkdir -p $snapshot_dir 1>/dev/null 2>&1
        if [ $? -ne 0 ]; then
            echo "ERROR : Create snapshot dir '$snapshot_dir' failed on '$BACKUP_DEST_IP'"
            exit 1
        fi

        # remove all region files
        remove_region_files

        # Pack all the db files into a tarball
        echo "Packing database files, please wait..."
        tar czvf $DB_TAR_BALL ./dbcore ./dbmedia

        # uploading the databse 
        echo "uploading database fiels to $snapshot_dir, please wait..."
        scp $DB_TAR_BALL $BACKUP_DEST_USER@$BACKUP_DEST_IP:$snapshot_dir
        if [ $? -ne 0 ]; then 
            echo "ERROR : uploading databse files failed."
            exit 1
        fi

        # Write a snapshot record
        echo $snapshot_time > $SNAPSHOT_RECORD
        if [ $? -ne 0 ]; then 
            echo "ERROR : write file $SNAPSHOT_RECORD failed."
            exit 1
        fi

        # Clean up
        rm $DB_TAR_BALL

        echo "Snapshot backup completes."
    ;;

    --inc)
        echo "Making incremental backup, check for last snapshot ..."
        # Check if a previous snapshot has been made
        check_last_snapshot

        # Make a checkpoint
        make_checkpoint

        # Sync all the log files using 'rsync' utility to reduce network traffic
        sync_log_files

        # Make a tarball containing up-to-now logs
        tag_log_files

        echo "Incremental backup completes."
    ;;

    --fetch)
        if [ $# -ge 2 ]; then
            # test if the snapshot dir exists
            snapshot_dir=/home/$BACKUP_DEST_USER/$BACKUP_DEST_DIR/$2
            check_snapshot_dir $2

            if [ $# -ge 3 ]; then
                # test if the log-tag exists
                check_log_tag $2 $3
                log_file="logs-$3.tar.gz"
            fi
        else
            usage
            exit 1
        fi
        
        # Remove last snapshot info
	rm $SNAPSHOT_RECORD 1>/dev/null 2>&1 #no error checking

        # Download the database tarball
        echo "Downloading database $snapshot_dir/$DB_TAR_BALL from $BACKUP_DEST_IP, please wait ..."
        scp $BACKUP_DEST_USER@$BACKUP_DEST_IP:$snapshot_dir/$DB_TAR_BALL .
        if [ $? -ne 0 ]; then
            echo "Download database file from backup server failed."
            exit 1
        fi

        # Extract
	echo "Removing current databases, please wait ..."
        rm dbcore/ dbmedia/ -rf 1>/dev/null 2>&1 #no error checking
        echo "Extracting database files, please wait ..."
        tar xvf $DB_TAR_BALL 1>/dev/null 2>&1
        if [ $? -ne 0 ]; then
            echo "Extracting databse file failed."
            exit 1
        fi

        # If specified a log tag, download and extract
        if [ -n "$log_file" ]; then
            # download
            echo "Dowloading log file $snapshot_dir/$log_file from $BACKUP_DEST_IP, please wait ..."
            scp $BACKUP_DEST_USER@$BACKUP_DEST_IP:$snapshot_dir/$log_file .
            if [ $? -ne 0 ]; then
                echo "Download log file from backup server failed."
                exit 1
            fi

            # extract
            echo "Extracting log files, please wait ..."
            tar xvf $log_file 1>/dev/null 2>&1
            if [ $? -ne 0 ]; then
                echo "Extracting log file failed."
                exit 1
            fi
            
            # cleanup
            rm $log_file
        fi

        # recover on all db envs
        echo "Doing database recovery ..."
        catastrophic_recover

        echo "Database recovery completes."
    ;;
    --reset)
        # Make a checkpoint
        make_checkpoint

        echo "Reset database LSNs for furthur backups ... "
        # reset log LSNs
        reset_log_lsn

        # remove all log files
	echo "Remove all log files ..."
        remove_all_log_files

        echo "Doing database recovery ..."
        catastrophic_recover

	echo "Reset database LSNs completes. (No need to reset the database anymore)"
    ;;
    *)
        usage
        exit 1
    ;;
esac
