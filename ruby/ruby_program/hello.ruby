#!/usr/bin/ruby -w
#vi: set fileencoding=utf-8 :
#command irb --simple-prompt
=begin
this is my first ruby program
=end
puts "hello world!";
print 10 + 20;
print "\n";
#puts __ENCODING__;
#Rational b = 9/10;
#puts b;

#there is test about array below
array = Array.new(3) {|i| i+1};
#0.upto(array.size()) {|i| print "#{array[i]}"}
print "\n"
array[1,1] = [8,9,10];
array.each {|i| puts i};
array[0..array.size()]=[8,8,8,8,8,8];
#array.each {|i| puts i};
puts array.object_id;
array += [1,2,3];
array -= [8,3];
puts array.object_id;
#array.each {|i| puts i};

#there is Hash test below
hash = Hash.new;
hash = {"one" => 1, "two" => 2, "three" => 3}	
hash.each { |x| puts x}

String s = "hello";
String t = s;
t[0] = "world";
puts s;
puts t;

def fib(x0, y0)
	Fiber.new do
		x,y = x0, y0;
		loop do
			Fiber.yield y
			x, y = y, x + y;
		end
	end
end

g = fib(0,1);
10.times {print g.resume, ""}
print "\n";
