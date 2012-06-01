#!/usr/bin/env ruby
require "rexml/document"
include REXML
#
class XMLfile
    def initialize(file)
        @m_file = file;
    end

    def run
        root = Document.new(File.new(@m_file)).root;
        puts root.to_s;
        #ns = root.attributes;

        #index = 0;
        #puts "+++++++++print out attributes++++++++++++"
        #ns.each do |name|
        #    puts "#{index} :"
        #    puts name
        #    index += 1;
        #end
        #puts "+++++++++end print out attributes++++++++++++"

        #puts "++++++++++++++++++puts elements++++++++++++++"
        #index = 0;
        #root.elements.each do |elem|
        #    puts "#{index} :"
        #    puts elem.expanded_name;
        #    #puts elem.to_s;
        #    index += 1;
        #end
        #puts "++++++++++++++++++end puts elements++++++++++++++"
    end
end

if __FILE__ == $0
    file = XMLfile.new "bridge_actor.xml"
    file.run
end
