#!/usr/bin/env ruby
require 'rubygems'
require 'net/ssh'
require 'net/scp'

Text_endcolor   = "\033[0m";
Text_red        = "\033[22;31m";
Text_yellow     = "\033[01;31m";
Text_green      = "\033[10;31m";

#resource host
USER_NAME       = "apd"
USER_PASSWD     = "apd"
REMOTE_HOST     = "192.168.1.21";
REMOTE_DB_DIR   = "/home/apd/dbbackup/";

#other destination host
BUSER_NAME      = "apd";
BUSER_PASSWD    = "apd";
BREMOTE_HOST    = "192.168.3.3";
BREMOTE_HOME    = "/home/apd/"
BREMOTE_DB_DIR  = "/home/apd/parallel-0.1.4.5fa66bf/bin/";

#local config
HOME_PATH       = ENV['home'];
LOCAL_DB_DIR    = "/home/wuxiang/penguin/build/";

#command
TAR_DB          = "tar xzvf ";

#postgres config
PSQL_HOST       = "192.168.154.136";
PSQL_PORT       = "5432";
SCANNER_FILE    = "scanner_add_access";
SCANNER_CMD     = "./#{SCANNER_FILE} --psql_addr #{PSQL_HOST}  --psql_port #{PSQL_PORT} --user_name ";

def print_error(text)
    puts Text_red + text + Text_endcolor;
end

def print_notice(text)
    puts Text_yellow + text + Text_endcolor;
end

def print_debug(text)
    puts Text_green + text + Text_endcolor;
end

def detail_instruction
    print_notice("you should do like this: ./scanner.rb [DB NAME] [USER NAME]");
end

class Get_DB
    def initialize(name)
        @m_name = name;
    end

    def run
        unless run_scp_download;
            print_notice("get data success");
            run_scp_upload;
        else
            print_notice("get data failed");
        end
    end

    def run_scp_download
        Net::SCP.start(REMOTE_HOST, USER_NAME, :password=>USER_PASSWD) do |scp|
            #synchronous download
            #local = REMOTE_DB_DIR + @m_name;
            print_debug("+++++++++++++++starting get db from resource host+++++++++++");
            ret = scp.download! (REMOTE_DB_DIR + @m_name), LOCAL_DB_DIR 
            print_debug("+++++++++++++++congraturation: ending get db++++++++++++++++");
        end
    end

    def run_scp_upload
        Net::SCP.start(BREMOTE_HOST, BUSER_NAME, :password=>BUSER_PASSWD) do |scp|
            #synchronous upload
            print_debug("+++++++++++++++starting put db to resource host+++++++++++");
            ret = scp.upload! (LOCAL_DB_DIR + @m_name), BREMOTE_DB_DIR  
            print_debug("+++++++++++++++congraturation: ending put db++++++++++++++++");
        end
    end

end

class Decompose
    def initialize(name)
        @m_name = name;
    end

    def run
        result = system(TAR_DB + @m_name);
        print_error("tar db file failed") unless result;

        dir = @m_name.partition(".").first;

        result = system("mv " + dir + "/* " + ".");
        print_error("mv db file failed") unless result;

        result = system("rm -rf " + dir);
        print_error("rm empty directory failed") unless result;
    end
end

class Remote_decompress
    def initialize(name)
        @m_name = name;
    end

    def run
        ssh = Net::SSH.start(BREMOTE_HOST, BUSER_NAME, :password=>BUSER_PASSWD) do  |ssh|
            #ret = ssh.exec "cd #{BREMOTE_DB_DIR}";
            #print_error("remote change fold failed") unless ret;

            ret = ssh.exec "#{TAR_DB} #{BREMOTE_DB_DIR}#{@m_name}";
            print_error("remote tar failed") unless ret;

            #dir = @m_name.partition(".").first;
            #
            ##cmd1 = "mv " + dir + "/* " + BREMOTE_DB_DIR;
            #ret = ssh.exec "mv #{BREMOTE_HOME}#{dir}/*  #{BREMOTE_DB_DIR}"
            #print_error("mv db file failed") unless ret;
            #
            ##cmd2 = "rm -rf " + dir;
            #ret = ssh.exec "rm -rf #{BREMOTE_HOME}#{dir}";
            #print_error("rm empty directory failed") unless ret;
        end
    end

    def change_position
        ssh = Net::SSH.start(BREMOTE_HOST, BUSER_NAME, :password=>BUSER_PASSWD) do  |ssh|
            dir = @m_name.partition(".").first;
            
            #cmd1 = "mv " + dir + "/* " + BREMOTE_DB_DIR;
            ret = ssh.exec "mv #{BREMOTE_HOME}#{dir}/*  #{BREMOTE_DB_DIR}"
            print_error("mv db file failed") unless ret;
            
            #cmd2 = "rm -rf " + dir;
            ret = ssh.exec "rm -rf #{BREMOTE_HOME}#{dir}";
            print_error("rm empty directory failed") unless ret;
        end
    end
end

class Scanner
    def initialize(name)
        @m_name = name;
    end

    def run()
        ret = false;
        d = Dir.new(".");
        d.each do |x|
            if x == SCANNER_FILE
                ret = true;
                break;
            end
        end

        unless ret
            print_error("scanner file not found")
            return false;
        end

        result = system(SCANNER_CMD + @m_name);
        print_error("scanner login access failed") unless result;
    end
end

if __FILE__ == $0

    if ARGV.size < 2
        print_error("THE NUMBER OF COMMAND ARGUEMENT IS WRONG");
        detail_instruction;
        exit 0;
    end

    #get db file
    puts ARGV[0];
    db = Get_DB.new(ARGV[0]);
    db.run;
    
    #decompress db file
    compose = Decompose.new(ARGV[0]);
    compose.run;

    rcompose = Remote_decompress.new(ARGV[0]); 
    rcompose.run;
    rcompose.change_position;

    #scanner
    scanner = Scanner.new(ARGV[1]);
    scanner.run;

end

