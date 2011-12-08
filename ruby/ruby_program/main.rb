#!/usr/bin/ruby -w
require "class.rb"
require "module.rb"
require "metaprogram.rb"
#include "class.rb"

p = Point.new(8, 8);
q = Point.new(p.x*2, p.y*2);
puts q[:x];
puts q[:y];

q.each {|x| print x; print "\t";}
print "\n";
q.all? {|x| x==0;}

m = Point.new(8, 8);
puts p == m;
#puts "#{Point::CONST_POINT.x}, #{Point::CONST_POINT.y}";
#Point::CONST_POINT2 = Point.new(80, 80);
#puts "#{Point::CONST_POINT2.x}, #{Point::CONST_POINT2.y}";

puts "======================";
NewType = Struct.new(:x);
m = NewType.new(88);
puts m;
puts "======================";
puts Point.sum(p, q).x;

puts "======================";
tmpIns = Instance_0.new(8, 8);
Instance_0.report;
puts "======================";
puts Instance_0.total;

puts "++++++++++++++permission begin+++++++++++++++"
per = Permission.new();
per.pub;
puts "++++++++++++++permission end+++++++++++++++++"
puts "++++++++++++++abstract begin+++++++++++++++++"
ab = World.new.greet;
#puts Father.new.call;
puts Child.new.call;
puts "++++++++++++++abstract end+++++++++++++++++"
ab = Dataf.new(1,2);
puts ab.x;

#c = ab.dup;
c = ab;
puts c.x;
c.set(8, 8);

puts ab.x;
puts c.x;

#Data2.new.try;

puts "++++++++++++++const inheri+++++++++++++++++"
puts Data2::CONST1.x;
puts Data2.new.out;
puts "++++++++++++++const inheri+++++++++++++++++"

puts "++++++++++++++mashal begin +++++++++++++++++"
f = Mashal.new(1,2,3);
puts f.mashal_dump;

g = Mashal.new();
g.mashal_load(f.mashal_dump);
puts g.x;
puts "++++++++++++++mashal end+++++++++++++++++"

PointStatus.instance.report;

puts "+++++++++++++++++++++++module++++++++++++++++++++++++++++";
puts "C<A: #{C < B}";
puts "A-ancestor: #{A.ancestors}";
puts "B-ancestor: #{B.ancestors}";
puts "C-ancestor: #{C.ancestors}";

s = "ni hao";
s.extend(A);
puts s.hi;

String.extend(A);
puts String.hi;
puts D::E;

F = Module.new;
G = Class.new;
H = Class.new(G) {
	include F
}
puts H.to_s;
puts "+++++++++++++++++++++++module++++++++++++++++++++++++++++";

puts "+++++++++++++++++++++++metaprograming++++++++++++++++++++++++++++";
a = Meta.new(0);
puts a.x;

a.instance_variable_set(:@x, 8);
a.instance_variable_get(:@x);

eval("puts @x", a.bindings);
puts a.instance_eval{
	remove_instance_variable :@x;
}
a.instance_eval("@x");
String.class_eval {
	def changdu
		size;
	end
}

b = String.new("hello");
puts b.changdu;
b.method(:reverse);
puts :reverse;
#puts b.methods;
print b.singleton_methods;
print "\n";
puts String.instance_methods==b.public_methods;

add_method(String, :greet) { puts "hello self define"}
b.greet;

add_single(String, :single) { puts "hello self single define"}
String.single;
puts "++++++++++++++++++++++++metaprograming+++++++++++++++++++++++++++";

