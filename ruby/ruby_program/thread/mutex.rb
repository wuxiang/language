#!/usr/bin/ruby -w
require 'thread'

class BankCount
	def initialize(name, checking, saving)
		@name, @checking, @saving = name, checking, saving;
		@lock = Mutex.new;
	end

	def transfer(x)
		@lock.synchronize {
			@saving -= x;
			@checking += x;
		}
	end

	def report
		@lock.synchronize {
			"#@name\nChecking: #@checking\nSaving: #@saving";
		}
	end
end
