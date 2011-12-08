#!/usr/bin/ruby -w

regex = /\<hello\>/i;
"world there, <hello> world" =~ regex;

pattern = /(ruby | perl)(\s+)(rocks | sucks)!/;
text = "ruby\trocks";
pattern =~ text;
#data = Regexp.last_match;
#puts data;
#puts data.size;
#puts data[0];
#puts data[1];


