#!/usr/bin/env ruby


if __FILE__ == $0
    i = 0;
    while i < ARGV.size do
        puts ARGV[i];
        i += 1;
    end

    puts "ARGV SIZE #{ARGV.size}"
    j = 0;
    puts j;
    ++j;
    puts j;
end
