#!/usr/bin/env ruby
require 'rubygems'
require 'net/ssh'
require 'net/scp'

Text_endcolor = "\033[0m";
Text_red      = "\033[22;31m";
Text_yellow   = "\033[01;31m";
Text_green    = "\033[10;31m";

USER_NAME     = "apd"
USER_PASSWD   = "apd"
REMOTE_HOST   = "192.168.1.21";
REMOTE_DB_DIR = "/home/apd/dbbackup/";

HOME_PATH     = ENV['home'];
LOCAL_DB_DIR  = "/home/wuxiang/penguin/build/";

#command
TAR_DB        = "tar xzvf ";

#postgres config
PSQL_HOST     = "192.168.154.136";
PSQL_PORT     = "5432";
SCANNER_FILE  = "scanner_add_access";
SCANNER_CMD   = "./#{SCANNER_FILE} --psql_addr #{PSQL_HOST}  --psql_port #{PSQL_PORT} --user_name ";

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
        if run_scp;
            print_notice("get data success");
        else
            print_notice("get data failed");
        end
    end

    def run_scp
        Net::SCP.start(REMOTE_HOST, USER_NAME, :password=>USER_PASSWD) do |scp|
            #synchronous download
            #local = REMOTE_DB_DIR + @m_name;
            print_debug("+++++++++++++++starting get db from resource host+++++++++++");
            ret = scp.download! (REMOTE_DB_DIR + @m_name), LOCAL_DB_DIR 
            print_debug("+++++++++++++++congraturation: ending get db++++++++++++++++");
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

    #scanner
    scanner = Scanner.new(ARGV[1]);
    scanner.run;

end

