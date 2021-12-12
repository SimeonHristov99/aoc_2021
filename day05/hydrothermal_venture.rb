inputData = File
  .read(ARGV[0] || 'input.txt').lines
  .map { |line| line.split(' -> ').map { |num| num.split(',').map(&:to_i)}}
  
  straightLines, diagonalLines = inputData.partition { |(x1, y1),(x2, y2)| x1 == x2 || y1 == y2}
  
  def calcCoordinates(((x1, y1), (x2, y2)))
      w = x2 < x1 ? x1.downto(x2) : x1.upto(x2)
      h = y2 < y1 ? y1.downto(y2) : y1.upto(y2)
      
      x1 == x2 || y1 == y2 ? [*w].product([*h]) : [*w].zip([*h])
  end
  
# Part 1
part1 = straightLines.flat_map(&method(:calcCoordinates)).tally

puts part1.values.count { |v| v > 1}

# Part 2
part2 = diagonalLines.flat_map(&method(:calcCoordinates)).tally.merge(part1) { |_, a, b| a + b}.values.count { |v| v > 1}

puts part2