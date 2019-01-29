# gabuzo.rb
# a simple oneliner prgm to convert a shadok number to an integer
# ---------------------------------------------------------------

CVT = { "GA" => "0", "BU" => "1", "ZO" => 2, "MEU" => 3 }
puts ARGV[0].upcase.split.map { |x| CVT[x] }.join.to_i(base=4)
