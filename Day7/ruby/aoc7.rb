
def split_ip_parts(ip)
	parts = ip.scan(/([a-z]+)/).flatten
	{
		parts: parts.values_at(* parts.each_index.select {|i| i.even?}),
		seqs: parts.values_at(* parts.each_index.select {|i| i.odd?})
	}
end

def extract_abbas(parts)
	parts[:parts].map! do |part|
		extract_abba(part)
	end
	parts[:parts].flatten!
	parts[:seqs].map! do |seq|
		extract_abba(seq)
	end
	parts[:seqs].flatten!
	parts
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

def supports_tls?(abbas)
	p = abbas[:parts].size > 0
	s = abbas[:seqs].size == 0
	p && s
end

input = IO.readlines("inputM")

num = 0

input.each do |ip|
	parts = split_ip_parts(ip)
	abbas = extract_abbas(parts)
	num += 1 if supports_tls?(abbas)
#	puts "#{num} - #{ip}"
end
puts num
