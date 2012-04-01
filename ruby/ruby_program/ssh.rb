#!/usr/bin/env ruby

require 'rubygems'
require 'net/ssh'

$cmd = 'ls -l'

#exist flag
$working = true

HOST = ARGV[0]
USER = ARGV[1]
PASS = ARGV[2]

def getInput
    print "elison@#{HOST}$ "
    $cmd = STDIN.gets
end

def execute_cmd(master)
    result = master.exec!($cmd)
    puts result
end

def exist
    $working = false if $cmd == "exit\n"
end

#construct singleton object
ssh = Net::SSH.start(HOST, USER, :password=>PASS) do |ssh|
    while $working do 
        getInput
        
        execute_cmd(ssh)

        exist
    end
end
