require "string.rb"

s = "hello";
s.concat("world");
puts s;

s.insert(5, "there");
puts s;

puts "+++++succ+++++";
puts s.succ
puts "+++++succ+++++";

puts s.slice!(3,5);
puts s;
puts s.capitalize;
puts s.swapcase

puts "++++++print++++++++++";
n = 3;
animal = "dogs";
printf("%d blind %s\n", n, animal);
#puts sprintf("%d blind %s\n", n, animal);
puts '%d blind %s\n' % [n + 1, animal]; #must be array
puts "++++++print++++++++++";

#helloworld
