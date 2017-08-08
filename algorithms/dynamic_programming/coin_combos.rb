#!/usr/bin/env ruby

#-------------------------------------------------------------------------------
# Given a value V and a set of coin values [C0, C1, ..., Cn], write a function
# that returns the total number of ways to represent value V using combinations
# of coins. Assume you have access to as many coins as you need.
#
# Eg: how many ways can you choose coins that sum to 95 cents given the standard
# set of US coins [1, 5, 10, 25 cents]
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# Functions
#-------------------------------------------------------------------------------

def coin_combos(target_value, coin_values)
  coin_values.sort!
  _coin_combos(target_value, coin_values)
end

def _coin_combos(target_value, coin_values)
  # We can represent the value of 0 with no coins!
  return 1 if target_value == 0

  # We cannot represent any value if we have no coins!
  return 0 if coin_values.empty?

  # We cannot represent any value smaller than all coins!
  return 0 if target_value < coin_values[0]

  # Temp variables
  ways = 0
  value = target_value
  curr_coin = coin_values[0]
  remaining_coins = coin_values[1..-1]

  # Iteratively reduce 'value' by the lowest coin value, and see how many ways
  # we can represent the difference (value - coin_0) using the remaining coins
  while value >= 0
    ways += _coin_combos(value, remaining_coins)
    value -= curr_coin
  end

  ways
end

def test_answer(value, coins)
  ways = coin_combos(value, coins)
  puts "There are #{ways} ways to represent the value #{value} using coins #{coins.inspect}"
end

#-------------------------------------------------------------------------------
# Main
#-------------------------------------------------------------------------------

coins = [1, 5, 10, 25]

test_answer(3, coins)
test_answer(15, coins)
test_answer(25, coins)
