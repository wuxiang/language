#!/usr/bin/ruby -w
require 'socket'
require 'net/http'

host = "www.baidu.com"
port = 80;
path = "/index.html";

request = "GET #{path} HTTP/1.0\r\n\r";
socket = TCPSocket.open(host, port);
socket.print(request);
response = socket.read;

headers,body = response.split("\r\n\r\n", 2);
print body

http = Net::HTTP.new(host);
headers1, body1 = http.get(path);
if headers1.code == "200"
	print body;
else
	puts "#{headers1.code} #{headers1.message}";
end
