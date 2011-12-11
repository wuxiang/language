#!/usr/bin/ruby -w
require 'socket'

host,port = ARGV;
s = TCPSocket.open(host, port);
while line=s.gets
	puts line.chop
end
s.close;
