#!/usr/bin/env ruby
#===============================================================================
# Given an unsorted array, find the k-th largest element in O(lg n) time.
#
# The approach is similar to the partitioning step of quicksort: we choose a
# pivot and organize lesser elements to the left, and greater elements to its
# right.  We then count the number of elements and determine which side to
# recursively search.
#===============================================================================

@recursive_calls = 0

# Generate an array of size `size` of random integers
def gen_random_array(size)
  array = []
  size.times { array << (rand * 1000).to_i }
  array
end

# Given an array, plus the beginning (inclusive) and ending (exclusive) indexes,
# partition that array by choosing a pivot and moving lesser elements to the
# pivot's left, and greater elements to the pivot's right.
#
# Returns the index of the pivot.
def partition(array, i_beg, i_end)
  # I'm cheating with this implementation, which uses extra space
  pivot = array[i_beg]
  smaller = []
  larger = []

  (i_beg + 1).upto(i_end - 1) do |i|
    if array[i] <= pivot
      smaller << array[i]
    else
      larger << array[i]
    end
  end

  subarray = [smaller, pivot, larger].flatten
  i_beg.upto(i_end-1) do |i|
    array[i] = subarray.shift
  end

  i_beg + smaller.size
end

# Recursive helper function to find the k-th largest elements
# - `array` is the array of numbers
# - `k` is the rank of the largest number to find (eg: 1 = 1st largest,
#   5 = 5th largest).
# - `i_beg` is the index of the first element to consider (inclusive).
# - `i_end` is the index of the last element to consider (exclusive). For
#    example, if considering elements 2 through 6, `i_end` should be 7.
# Returns the k-th largest element
def find_kth_recursive(array, k, i_beg, i_end)
  @recursive_calls += 1

  # Look for input errors
  size = i_end - i_beg
  if k < 1
    raise RuntimeError, "find_kth_largest: k must be > 0"
  end
  if k > size
    raise RuntimeError, "find_kth_largest: k=#{k} larger than array size=#{size}"
  end

  # Partition the array
  i_pivot = partition(array, i_beg, i_end)
  size_right = i_end - i_pivot - 1

  # Search one of the sub-arrays, or return the pivot
  if k <= size_right
    return find_kth_recursive(array, k, i_pivot + 1, i_end)
  elsif k == size_right + 1
    return array[i_pivot]
  else
    k = k - size_right - 1
    return find_kth_recursive(array, k, i_beg, i_pivot)
  end
end

# Find and return the kth largest value in the array. k starts at 1.
def find_kth_largest(array, k)
  find_kth_recursive(array, k, 0, array.size)
end

#===============================================================================
# Main
#===============================================================================

# Get command-line args
k    = ARGV.shift or abort "usage: <k> <array_size>"
size = ARGV.shift or abort "usage: <k> <array_size>"

k = Integer(k) rescue abort("k must be an integer")
size = Integer(size) rescue abort("size must be an integer")

# Generate the array and find the kth largest value
array = gen_random_array(size)
num   = find_kth_largest(array, k)

# Print the results
puts "array:  " + array.join(' ')
sorted = "sorted: " + array.sort.join(' ')
puts sorted

i_val = sorted.rindex(/ #{num}\w?/)
pointer = (' ' * (i_val + 1)) + ('^' * num.to_s.size)
puts pointer
puts "k=#{k} largest: #{num}"
puts "recursive calls: #{@recursive_calls}"
