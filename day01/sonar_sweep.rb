inputData = File.readlines("input.txt").map(&:to_i)

part1 = inputData.each_cons(2).map { |a, b| "inc" if b > a }.count("inc")
part2 = inputData.each_cons(3).map{ |nums| nums.sum }.each_cons(2).map { |a, b| "inc" if b > a }.count("inc")

puts part1
puts part2