#!/usr/bin/ruby -w

module A
	def hi
		"hello world";
	end
end

module B
	include A
end

class C
	include B;
end

module D
	class E
		Module.nesting
	end
end


