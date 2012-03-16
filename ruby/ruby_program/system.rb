#!/usr/bin/ruby -w


#exec "echo  *"

system("echo", "*")
#system("echo *")

ids = %x[ps aux | grep -rIn "elison"]
puts ids
