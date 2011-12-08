#!/usr/bin/ruby -w
include Enumerable
include Comparable
#include Singleton
require 'singleton'

class Point
	@@n = 0;
	@@totalx = 0;
	@@totaly = 0;

	#attr_reader :x, :y;
	attr_accessor :x, :y;
	attr :z;
	attr :m;
	def initialize(x, y)
		@x, @y = x, y;
		@z, @m = 0, 0;
		@@n += 1;
		@@totalx += x;
		@@totaly += y;
		PointStatus.instance.record(self);
	end

	#def self.report
	#	puts "Number of Points created: #@@n";
	#	puts "the Average x coordinate: #{@@totalx.to_f/@@n}";
	#	puts "the Average y coordinate: #{@@totaly.to_f/@@n}";
	#end

	def +(other)
		Point.new(@x + other.x, @y + other.y);
	end

	def -@
		Point.new(-@x, -@y);
	end

	def *(scale)
		Point.new(@x*scale, @y*scale);
	end

	def [](index)
		case index
		when 0, -2 then   @x;
		when 1, -1 
			@y;
		when :x, "x": @x;
		when :y, "y": @y;
		else nil;
		end
	end

	def each
		yield @x;
		yield @y;
	end

	def ==(o)
		if o.is_a? Point
			@x == o.x and @y == @y;
		else
			false;
		end
	end

	def eql?(o)
		if o.instance_of? Point
			@x.eql?(o.x) and @y.eql?(o.y);
		elsif
			false;
		end
	end

	def <=>(other)
		return nil unless other.instance_of? Point ;
		@x**2 + @y**2 <=> other.x**2 + other.y**2;
	end

	def add!(other)
		@x += other.x;
		@y += othery;
		self;
	end

	def add(other)
		tmp = self.dup;
		tmp.add!(other);
	end

	def Point.sum(*points)
		x = y = 0;
		points.each {|point| x += point.x; y += point.y}
		Point.new(x, y);
	end

	#same meaning as before
	#class << Point
	#	def sum(*points)
	#		x = y = 0;
	#		points.each {|point| x += point.x; y += point.y}
	#		Point.new(x, y);
	#	end
	#end
	#def to_s
	#	"(#@x, #@y)";
	#end

	#def x
	#	@x;
	#end

	#def y
	#	@y;
	#end

	#def x=(value)
	#	@x = value;
	#end

	#def y=(value)
	#	@y = value;
	#end
	
	#CONST_POINT = Point.new(88, 88);
end

class Instance_0
	attr_accessor :x, :y;
	@total = 0;
	@totalx = 0;
	@totaly = 0;
	def initialize(x, y)
		@x = x;
		@y = y;
	end
	
	def self.new(x, y)
		@total += 1;
		@totalx += x;
		@totaly += y;
		super
	end

	def self.report
		puts "Number of Points created: #@total";
		puts "the Average x coordinate: #{@totalx.to_f/@total}";
		puts "the Average y coordinate: #{@totaly.to_f/@total}";
	end

	class << Instance_0
		attr_accessor :total, :totalx, :totaly;
	end
end

class Permission
	def initialize
		puts "hello initialize";
	end
	public
		def pub
			puts "hello public";
		end
	protected
		def pro
			puts "hello protected";
		end
	private
		def pri
			puts "hello private";
		end
end

#how to define a interface
class AbstractGreeter
	def greet
		puts "#{greeting} #{who}"; #set two abstract interface
	end
end

class World < AbstractGreeter
	def greeting
		"hello";
	end

	def who
		"abstrace";
	end
end

#i want to know what will happen when herit class's func cover a func in it's father
class Father
	def hello
		"father";
	end

	#def call
	#	hello;   #it will print "child"
	#end

	def Father.greet
		"single";
	end
end

class Child < Father
	def hello
		"child";
	end

	def call
		Father.greet;
	end
end

class Dataf
	attr_accessor :x, :y;
	def initialize(x, y)
		@x = x;
		@y = y;
	end

	def set(a, b)
		@x = a;
		@b = b;
	end


	CONST1 = Dataf.new(1,2);
end

class Data2 < Dataf
	def initialize
		@x = 1000;
		super(8, 8);
	end

	def try
		puts @x, @y;
	end
	def out
		CONST1.x;
	end
	CONST1 = Dataf.new(3,4);
end


class Mashal
	attr_accessor :x;
	def initialize(*a)
		@x = a;
	end

	def mashal_dump
		@x.pack("w*");
	end

	def mashal_load(s)
		@x = s.unpack("w*");
	end
end

class PointStatus
	include Singleton
	def initialize
		@n, @totalx, @totaly = 0, 0.0, 0.0;
	end

	def record(point)
		@n += 1;
		@totalx += point.x;
		@totaly += point.y;
	end

	def report
		puts "created point: #@n";
		puts "averages: #{@totalx/@n}";
		puts "averages: #{@totaly/@n}";
	end
end
