#!/usr/bin/ruby  -w
require 'open-uri'

def conread(filenames)
	h = {};
	filenames.each do |filename|
		h[filename] = Thread.new do
			open(filename) {|f| f.read}
		end
	end

	h.each_pair do |filename, thread|
		begin
			h[filename] = thread.value
		rescue 
			h[filename] = $!;
		end
	end
end

module Enumerable
	def conmap(&block)
		threads = [];
		self.each do |element|
			threads << Thread.new {block.call(element)}
		end
		threads.map {|t| t.value}
	end
end
