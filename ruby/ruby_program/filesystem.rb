#!/usr/bin/ruby -w

#here is something about file system

full = '/home/administrator/git_internet/language/ruby/ruby_program/main.rb';
file = File.basename(full);
puts file;
file1 = File.basename(full, '.rb');
puts file1;
dir = File.dirname(full);
puts dir;

puts "++++++++++++++++1+++++++++++++++=";
name1 = File.split(full);
puts name1;
puts "++++++++++++++++2+++++++++++++++=";
puts File.extname(full);
puts File.extname(file);
puts File.extname(file1);
puts "==";
puts File.extname(dir);
puts "==";
puts File.expand_path("~");
puts File.expand_path(".");
puts File.expand_path("..");
puts File.expand_path("hello.rb");
puts File.expand_path("hello.rb", '/');
puts File.join('', 'home');
#puts Dir.chdir("/");
puts "+++++++++++++++3++++++++++++++++++++++"
flags = File::FNM_PATHNAME | File::FNM_DOTMATCH;
puts File.fnmatch("lib/*.rb", "lib/a.rb", flags);
puts "+++++++++++++++3++++++++++++++++++++++"
dirname = Dir.entries("../../..");
puts dirname;
puts "+++++++++++++++4++++++++++++++++++++++"
index = 0;
Dir.foreach(".") {|filename| 
	index += 1;
	print "#{filename} ";
	if(index>5)
		index = 0;
		print "\n";
	end
}
print "\n";
puts "+++++++++++++++5++++++++++++++++++++++"
array = Dir['*.rb'];
puts array;
puts Dir.getwd;
puts "+++++++++++++++6++++++++++++++++++++++"
def findfile(path, ext)
#puts File.expand_path(path);
hasdir = false;
hasmatch = false;
existname = "";
Dir.foreach(path) {|file|
	if(File.directory?(file))
		hasdir = true;
	end

	if(File.extname(file) == ".hpp")#=~ /\.[ch]/)
		hasmatch = true;
		existname = file;
		break;
	end
}
if(!hasdir)
	if(!hasmatch)
		return;
	else
		return existname;
	end
else
	if(hasmatch)
		return existname;
	end
end
Dir.chdir(path) {
	Dir.foreach(".") {|name|
		if(name == "." || name == ".." || name == ".git")
			next;
		end

		if(File.file?(name))
			if(File.extname(name) == ".hpp")#=~ /\.[ch]/)
				return name;
			else
				next
			end
		end

		return	findfile(File.join(path, name), /\.[ch]/);
#	
#	#	Dir.chdir(./name) {
#	#	}
#	
	}
}
end

puts "++++++++++++++++++++++++++++8+++++++++++++++++++++++++++";
puts findfile(File.expand_path("../../"), /\.[ch]/);

















