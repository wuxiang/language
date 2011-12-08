#!/usr/bin/ruby -w
#vim: set fileencoding=utf-8

def max(first, *rest)
	max = first;
	rest.each do |x|
		max = x if x > max;
	end
	max
end

puts max(1,2);
puts max(1,2,3);
puts max(1,2,5);

puts max(*"helloworld".each_char);

def arg(a, b = 0, c = 1, *d)
	puts "hello";
end

#arg(0);
#arg

def sequence(args)
	n = args[:n] || 0;
	m = args[:m] || 0;
	c = args[:c] || 0;
	a = [];
	n.times {|i| a << m * i + c}
	a
end

puts sequence(:n=>3, :m=>2, :c=>8);
puts sequence({:n=>3, :m=>2, :c=>8});

def sequence2(n, m, c)
	i = 0;
	while(i < n) do
		yield i * m + c;
		i += 1;
	end
end

sequence2(1,2,3) {|x| puts x}

pro = Proc.new {|total, x| total + x}
def func(arg, &cal)
	arg.inject(0, &cal);
end

def func2(arg, &cal)
	arg.each do |i|
		cal.call(i);
	end
end
def func3(arg, cal)
	puts arg;
	arg.each do |i|
		cal.call(i);
	end
end

puts func([1,2,3], &pro);

puts "==================================";
pro1 = Proc.new {|i| puts i}
func2([1,2,3], &pro1);
puts "==================================";
[1,2,3].each {|i| puts i}
#puts func3([1,2,3], pro1);
#
#puts "==================================";
#total = func([8,8,8]) {|tot, x| tot + x}
#puts total;

lambda1 = lambda {|x| puts x;}
#lambda2 = ->(x=10) { puts x ;}
#->{}
puts "+++++++++++++++++++++++++++++++++++"
pro1[100];
#pro1.(200);
puts lambda {|*args|}.arity;
puts pro1.arity;
