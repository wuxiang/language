#!/usr/bin/env ruby

require 'rubygems'
require 'net/ssh'
require 'net/ssh/shell'

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
#ssh = Net::SSH.start(HOST, USER, :password=>PASS) do |ssh|
#    while $working do 
#        getInput
#        
#        execute_cmd(ssh)
#
#        exist
#    end
#end

ssh = Net::SSH.start(HOST, USER, :password=>PASS) do |session|
    puts "begin ssh"
    shell = session.shell.open
#        while $working do 
#            getInput
#
#            if command = /[a-zA-Z]*/.match($cmd)
#                puts "regexp match success(#{command})"
#                #arg = $cmd.sub(command)
#                #puts "(#{arg})"
#            end
#            
#            exist
#        end
    puts "ssh"
    shell.exit
end

puts "end"

