#!/usr/bin/env ruby
require 'pp'
require 'optparse'

options = {}
OptionParser.new do |parser|
  parser.banner = "Usage: ./#{File.basename(__FILE__)} [options]"
  parser.on("-f", "--file FILE", "The puzzle input file.", :REQUIRED) do |f|
    options[:file] = f
  end
end.parse!

def run(file)
  raise OptionParser::MissingArgument.new("Required argument -f") if file.nil? || file.empty?
  input = IO.readlines(file)

  tls = 0
  ssl = 0

  input.each do |ip|
    parts = split_ip_parts(ip)
    abbas = extract_abbas(parts)
    abas = extract_abas(parts)
    tls += 1 if supports_tls?(abbas)
    ssl += 1 if supports_ssl?(abas)
  end
  puts "IP:s that support TLS: #{tls}"
  puts "IP:s that support SSL: #{ssl}"

end

def split_ip_parts(ip)
  parts = ip.scan(/([a-z]+)/).flatten
  {
    parts: parts.values_at(* parts.each_index.select {|i| i.even?}),
    seqs: parts.values_at(* parts.each_index.select {|i| i.odd?})
  }
end

def extract_abbas(parts)
  result = {}
  result[:parts] = parts[:parts].map do |part|
    extract_abba(part)
  end
  result[:parts].flatten!
  result[:seqs] = parts[:seqs].map do |seq|
    extract_abba(seq)
  end
  result[:seqs].flatten!
  result
end

def extract_abba(part)
  found = []
  part.chars.each_with_index do |val, index|
    a = val
    b = part[index + 1]
    c = part[index + 2]
    d = part[index + 3]
    next unless a == d
    next unless b == c
    next unless a != b
    found.push "#{a}#{b}#{c}#{d}"
  end
  found
end

def extract_abas(parts)
  result = {}
  result[:parts] = parts[:parts].map do |part|
    extract_aba(part)
  end
  result[:parts].flatten!
  result[:seqs] = parts[:seqs].map do |seq|
    extract_aba(seq)
  end
  result[:seqs].flatten!
  result
end

def extract_aba(part)
  found = []
  part.chars.each_with_index do |val, index|
    a = val
    b = part[index + 1]
    c = part[index + 2]
    next unless a == c
    next unless a != b
    found.push "#{a}#{b}#{c}"
  end
  found
end

def supports_tls?(abbas)
  p = abbas[:parts].size > 0
  s = abbas[:seqs].size == 0
  p && s
end

def supports_ssl?(abas)
  abas[:parts].each do |part|
    abas[:seqs].each do |seq|
      return true if inverse? part, seq
    end
  end
  false
end

def inverse?(one, two)
  return false unless one[0] == two[1]
  return false unless one[1] == two[0]
  return false unless one[1] == two[2]
  true
end

run(options[:file])
