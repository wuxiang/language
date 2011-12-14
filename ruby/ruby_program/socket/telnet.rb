#!/usr/bin/ruby -w
require 'socket'

host, port = ARGV;
begin
	#connect to server
	STDOUT.print "connecting.........";
	STDOUT.flush;
	s = TCPSocket.open(host, port);
	STDOUT.puts "done";

	local, peer = s.addr, s.peeraddr;
	STDOUT.print "Connect  to #{peer[2]}: #{peer[1]}";
	STDOUT.puts  "using local port #{local[1]}";

	#waiting for initialization information
	begin
		sleep(0.5);
		msg = s.read_nonblock(4096);
		STDOUT.puts msg.chop;
	rescue SystemCallError
	end

	#begin client/server interaction
	loop do
		STDOUT.print '>';
		STDOUT.flush;
		local = STDIN.gets;
		break if !local;
		s.puts(local);
		s.flush;
		response = s.readpartial(4096);
	end
rescue 
	puts $!
ensure
	s.close if s;

end

