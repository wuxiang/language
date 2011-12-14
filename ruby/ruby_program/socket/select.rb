#!/usr/bin/ruby -w
require 'socket'

server = TCPServer.open(2000);
sockets = [server];
log = STDOUT;

while(true)
	ready = select(sockets);
	readable = ready[0];
	readable.each do |socket|
		if(socket == server)
			client = server.accept;
			sockets << client;
			client.puts "i am running on #{socket.gethostname}";
			log.puts "accepted connection from #{client.peeraddr[2]}";
		else
			input = socket.gets;
			if(!input)
				log.puts "client on #{socket.peeraddr[2]} disconnect";
				sockets.delete(socket);
				socket.close;
				next;
			end

			input.chop!;
			if(input == "quit")
				socket.puts "bye";
				log.puts "client on #{socket.peeraddr[2]} disconnect";
				sockets.delete(socket);
				socket.close;
			else
				socket.puts(input.reverse);
			end
		end
	end
end
