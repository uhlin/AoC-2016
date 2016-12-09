require 'pp'
def run
	inputs = IO.readlines('../input')
	sum = 0
	inputs.each_with_index do |input, index|
		parts = split_input_to_parts(input)
		next if decoy?(parts)
		sum += parts[:id].to_i
		name = decrypt(parts[:name], parts[:id])
		unless name.match(/northpole/i).nil?
			puts name
			puts parts[:id]
		end
	end
	puts sum
end

def decrypt(name, rot)
	name = name.chars.map do |ch|
		next ' ' if ch == '-'
		rest = rot.to_i % 26
		cp = ch.ord + rest
		cp -= 26 if cp > 122
		cp.chr
	end
	name.join
end

def split_input_to_parts(input)
	regex = /(?<name>[a-z\-]+)(?<id>\d+)\[(?<checksum>[a-z]+)\]/
	parts = input.match(regex)
	{
		name: parts[:name].chomp('-'),
		id: parts[:id],
		checksum: parts[:checksum]
	}
end

def decoy?(parts)
	counts = count_name_chars(parts[:name])
	sorted = counts.sort_by { |char, details| details[:occurrences] }.reverse
	top5 = extract_top_5(sorted)
	checksum = top5.join("")
	checksum != parts[:checksum]
end

def extract_top_5(sorted)
	lowest_occurence_in_top_5 = sorted[4][1][:occurrences]
	needed_length = 0
	sorted.each_with_index do |char, index|
		if char[1][:occurrences] < lowest_occurence_in_top_5		
			needed_length = index
			break;
		end
	end
	top5_candidates = sorted[0..needed_length-1]
	groups = top5_candidates.group_by { |obj| obj[1][:occurrences] }
	top5 = groups.map { |occurances, group|
		group.sort_by {|char, details| char } 
	}.flatten[0..9]
	top5 = top5.values_at(* top5.each_index.select {|i| i.even?})
end

def count_name_chars(name) 
	letters = {}
	order = 0
	name.chars.each do |char|
		next if char == '-'
		sym = char.to_sym
		if letters[sym].nil?
			letters[sym] = { occurrences: 1, order: order }
			order += 1 
		else
			letters[sym][:occurrences] += 1
		end
	end
	letters
end


run()

