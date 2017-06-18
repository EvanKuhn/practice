#!/usr/bin/env ruby
#===============================================================================
# Generate all permutations of the first N characters of the alphabet, either
# iteratively or recursively. Remember, order matters in permutations.
#
# Refresher:
# - Permutations: order matters         (eg: "ab" != "ba")
# - Combinations: order doesn't matter  (eg: "ab" == "ba")
#===============================================================================

ALPHABET = ('a'..'z').to_a

# Iteratively generate all permutations of the first N chars of the alphabet
def generate_iterative(length)
  str = ' ' * length
  (length ** length).times do |n|
    (length-1).downto(0) do |i|
      letter = ALPHABET[n % length]
      break if str[i] == letter
      str[i] = letter
      n /= length
    end
    puts str
  end
end

# Recursively generate all permutations of the first N chars of the alphabet
def generate_recursive(length)
  _permute(length, '')
end

def _permute(length, str)
  if str.length == length
    puts str
  else
    length.times do |i|
      str + ALPHABET[i]
      _permute(length, str + ALPHABET[i])
    end
  end
end

#===============================================================================
# Main
#===============================================================================

if ARGV.empty?
  puts "USAGE:"
  puts "    ./permutations.rb <method> <length>"
  puts
  puts "PARAMS:"
  puts "    method   Enter 'I' for iterative, 'R' for recursive."
  puts "    length   The length of the strings to generate."
  exit
end

method = ARGV.shift.upcase
length = ARGV.shift

abort "error: method '#{method}' not recognized" unless %[I R].include? method
abort "error: invalid length '#{length}'" unless length.to_i > 0

length = length.to_i

if method == 'I'
  generate_iterative(length)
  puts "(iterative)"
elsif method == 'R'
  generate_recursive(length)
  puts "(recursive)"
else
  raise LogicError, "Unrecognized method '#{method}'"
end
