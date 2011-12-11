#!/usr/bin/ruby -w
require "open-uri"

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
dirname = Dir.entries("../../.."); #first
puts dirname;
puts "+++++++++++++++4++++++++++++++++++++++"
index = 0;
Dir.foreach(".") {|filename| #second
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
def findfile(path, ext)  #find a file whose extent name is ext
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
File.open("test.txt", "w") { |filename|
	filename.write("hello");
}
puts "+++++++++++++++deal file+++++++++++++++";

File.open("test.txt", "a") {|filename|
filename.write(" world");
}

#Dir.mkdir("temp");
#Dir.chdir("temp") {
#	Dir.mkdir("temp1");
#	File.open("hello.txt", "w");
#	File.open("hello1.txt", "w");
#}

#Dir.rmdir("temp");
#Dir.delete("temp");
#Dir.unlink("temp");
puts "==============get page======================";
f = open("http://www.baidu.com");
webpage = f.read;
puts webpage;
f.close;

puts "==============get file======================";
data = File.read("main.rb");
puts data;

f = File.open("main.rb");
data1 = f.read();
puts data1 == data;
out = STDIN;
c = "";
c = out.getc();
puts c;



















