#!/usr/bin/ruby -w
require 'socket'

ds = UDPSocket.new;
ds.bind(nil, 2000);
loop do
	request, address = ds.recvfrom(1024);
	response = request.upcase;
	ds.send(response, 0, address[3], address[1])
end
