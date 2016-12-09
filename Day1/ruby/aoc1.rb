#!/usr/bin/env ruby
require 'pp'
require 'optparse'

options = {}
OptionParser.new do |parser|
  parser.banner = "Usage: ./#{File.basename(__FILE__)} [options]"
  parser.on("-f", "--file FILE", "The puzzle input file.", :REQUIRED) do |f|
    puts "blarg! #{f.inspect}"
    # if f.nil? || f.empty?
    options[:file] = f
  end
end.parse!

def run(file)
  raise OptionParser::MissingArgument.new("Required argument -f") if file.nil? || file.empty?
 puts "File: #{file}"
end

run(options[:file])
