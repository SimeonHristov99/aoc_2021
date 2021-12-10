inputData = File.read("input.txt").split

# Part 1
$horizontal = 0
$depth = 0

inputData.each_slice(2) {|a, b| a == "forward" ? $horizontal += b.to_i : a == "up" ? $depth -= b.to_i : $depth += b.to_i}

puts $horizontal * $depth

# Part 2
$horizontal = 0
$depth = 0
$aim = 0

def add(num)
    $horizontal += num
    $depth += $aim * num
end

inputData.each_slice(2) {|a, b| a == "forward" ? add(b.to_i) : a == "up" ? $aim -= b.to_i : $aim += b.to_i}

puts $horizontal * $depth