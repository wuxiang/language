#!/usr/bin/ruby -w
#vim: set fileencoding=utf-8
require 'enumerator'

a = 0;
if a
	puts "hello";
end

if false
	puts "false";
else
	puts "true";
end

if false
	puts "false";
elsif a
	puts "true";
end

puts "other express" if a;
begin
	puts "one";
	puts "two";
end if a;

#error express
#{
#	puts "one";
#	puts "two";
#}end if a;

puts "================";
String x = "two";
str = 
	case 
	when x == "one"
		puts "one";
	when x == "two"
		puts "two";
	else
		puts "not found";
	end
result = case x
		 when Fixnum
			 puts "fixnum";
		 when String
			 puts "String";
		 else
			 puts "other type";
		 end

def how_many_messages(n)
	"you have" + n.to_s() + (n==1 ? "message." : "messages.");
end

index = 0;
while index < 10 #do
	print index;
	print ", ";
	index += 1;
end
print "\n";

index = 0;
until index > 10 #do
	print index;
	print ", ";
	index += 1;
end
print "\n";

index = 0;
puts index += 1 while index < 10;

array = [1, 2, 3, 4,5];
for element in array do
	puts element;
end

hash = {:a=>1, :b=>2, :c=>8}
for key, value in hash
	puts "#{key}=>#{value}";
end

#index = 0;
#for index < 5 do
#	putx index;
#	index += 1;
#end

#Integer iterator
0.upto(5) { |x| x += 1; puts x }
0.upto(5) { |x| 
	x += 2; 
	puts x }

["a","b","c"].each {|x| print x}
["d","e","f"].each do |x| 
	print x
end
print "\n";

#File.open("learn.txt") do |f|
#	f.each_with_index do |line, number|
#		print "#{number}: #{line}";
#	end
#end

s = "hello";
s.enum_for(:each_char).map {|c| c.succ}
enumerator = s.each_char.with_index;

#enumerator = 100.downto(80);
#begin
#	print enumerator.next while true;
#rescue StopIteration
#	puts "...blastoff"
#end

#loop do
#	print enumerator.next;
#end
#puts "loop end";
#
puts "please enter the first word of you think of";
words = %w(apple, banana, orange);
response = words.collect do |word|
			print word + ">";
			response = gets.chop
			if(response.size == 0)
				word.upcase!
				redo
			end
			response
end
puts response;
