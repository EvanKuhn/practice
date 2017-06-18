#!/usr/bin/env ruby
#===============================================================================
# Generate all combinations of the first N characters of the alphabet. Remember,
# for combinations, order doesn't matter, so we'll simply choose characters in
# alphabetical order. Also, the results can be from length 1 to N.
#
# Refresher:
# - Permutations: order matters
# - Combinations: order doesn't matter
#===============================================================================

ALPHABET = ('a'..'z').to_a

# Recursively generate all combinations of length N of the chars in the alphabet
def generate_recursive(length)
  _generate(length, 0, '')
end

def _generate(length, index, str)
  return if str.length == length
  return if index == length

  # Include ALPHABET[i]
  s = str + ALPHABET[index]
  puts s
  _generate(length, index + 1, s)

  # Skip ALPHABET[i]
  _generate(length, index + 1, str)
end

#===============================================================================
# Main
#===============================================================================

if ARGV.empty?
  puts "USAGE:"
  puts "    ./combinations.rb <length>"
  puts
  puts "PARAMS:"
  puts "    length   Max length of the strings to generate."
  exit
end

length = ARGV.shift
abort "error: invalid length '#{length}'" unless length.to_i > 0
length = length.to_i

generate_recursive(length)
