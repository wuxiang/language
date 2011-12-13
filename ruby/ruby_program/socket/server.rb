#!/usr/bin/ruby -w
require 'socket'

server = TCPServer.open(2000);
loop do
	client = server.accept;
	client.puts(Time.now.ctime);
	client.close;
end
