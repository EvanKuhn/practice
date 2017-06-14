#!/usr/bin/env ruby
=begin

CC number starts with
'4026', '417500', '4405', '4508', '4844', '4913', '4917'
CC len : 16
Issuer : VISAELECTRON

CC number starts with: '4'
CC len : 16
Issuer: VISA

CC number starts with: '34', '37'
CC len : 15
Issuer : AMEX

CC number starts with: '36'
CC len : 14
Issuer : Diners Club

=end


class CreditCard
  class << self
    attr_reader :length, :prefixes, :title
  end

  attr_reader :number

  def initialize(number)
    @number = number
  end

  def title
    self.class.title
  end

  def self.matches?(number)
    number.length == length && prefixes.any? { |p| number.start_with?(p) }
  end

  def self.create(number)
    descendants.each do |type|
      return type.new(number) if type.matches?(number)
    end
    nil
  end

  def to_s
    "#{title} #{number}"
  end

  def self.descendants
    ObjectSpace.each_object(Class).select { |klass| klass < self }
  end
end

class VisaElectronCard < CreditCard
  @title    = 'Visa Electron'
  @length   = 16
  @prefixes = ['4026', '417500', '4405', '4508', '4844', '4913', '4917']
end

class VisaCard < CreditCard
  @title    = 'Visa'
  @length   = 16
  @prefixes = ['4']
end

class AmericanExpressCard < CreditCard
  @title    = 'American Express'
  @length   = 15
  @prefixes = ['34', '37']
end

class DinersClubCard < CreditCard
  @title    = 'Diners Club'
  @length   = 14
  @prefixes = ['36']
end


puts CreditCard.create('4175004175004172')     #== 'VISAELECTRON'
puts CreditCard.create('4917491749174917')     #== 'VISAELECTRON'
puts CreditCard.create('346416800707698')      #== 'AMEX'
puts CreditCard.create('376416800707698')      #== 'AMEX'
puts CreditCard.create('37641680070769832112') #== 'UNAVAILABLE'
puts CreditCard.create('36641680070769')       #== 'DC'
puts CreditCard.create('54545641680070769')    #== 'UNAVAILABLE'
puts CreditCard.create('4111111111111111')     #== 'VISA'
