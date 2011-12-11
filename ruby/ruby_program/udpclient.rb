#!/usr/bin/ruby -w
require 'socket'

data = File.read("main.rb");
host, port = ARGV;
ds = UDPSocket.new;
ds.connect(host, port);
ds.send(data, 0);
response, address = ds.recvfrom(1024);
puts response;
