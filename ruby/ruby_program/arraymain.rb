#!/usr/bin/ruby -w
require "set"

a = [1,2,3];
a.delete_at(2);
puts a;
a.replace([8,9,10]);
puts a;

puts "================set===================";
set = Set.new(1..8)
set1 = Set["hello", "hello", 1]
puts set;
puts set1;
