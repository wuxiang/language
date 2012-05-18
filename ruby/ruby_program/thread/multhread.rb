#!/usr/bin/env  ruby


a = Thread.new {puts "a"; puts "c";}
b = Thread.new {puts "b"; puts "d";}

a.run
b.run

a.join
b.join
puts "thread exiting normal"
