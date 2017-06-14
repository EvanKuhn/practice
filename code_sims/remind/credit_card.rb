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


CREDIT_CARD_ISSUERS = [
  :visa_electron,
  :visa,
  :amex,
  :diners_club,
]

CREDIT_CARD_PREFIXES = {
  :visa_electron  => ['4026', '417500', '4405', '4508', '4844', '4913', '4917'],
  :visa           => ['4'],
  :amex           => ['34', '37'],
  :diners_club    => ['36'],
}

CREDIT_CARD_LENGTHS = {
  :visa_electron  => 16,
  :visa           => 16,
  :amex           => 15,
  :diners_club    => 14,
}

def string_has_prefix(str, prefixes)
  prefixes.each { |p| return true if str.start_with?(p) }
  false
end

def find_issuer(number)
  CREDIT_CARD_ISSUERS.each do |issuer|
    if number.length == CREDIT_CARD_LENGTHS[issuer]
      if string_has_prefix(number, CREDIT_CARD_PREFIXES[issuer])
        return issuer
      end
    end
  end
  nil
end


puts find_issuer('4175004175004172')     #== 'VISAELECTRON'
puts find_issuer('4917491749174917')     #== 'VISAELECTRON'
puts find_issuer('346416800707698')      #== 'AMEX'
puts find_issuer('376416800707698')      #== 'AMEX'
puts find_issuer('37641680070769832112') #== 'UNAVAILABLE'
puts find_issuer('36641680070769')       #== 'DC'
puts find_issuer('54545641680070769')    #== 'UNAVAILABLE'
puts find_issuer('4111111111111111')     #== 'VISA'





=begin
class CreditCard
  def self.create(number)

  end
end

CREDIT_CARD_TYPES = {
  visa_electron: {
    length: 16,
    prefixes: ['4026', '417500', '4405', '4508', '4844', '4913', '4917'],
  },
  visa: {
    length: 16,
    prefixes: ['4'],
  },
  amex: {
    length: 15,
    prefixes: ['34', '37'],
  },
  diners_club: {
    length: 14,
    prefixes: ['36'],
  },
}

=end

