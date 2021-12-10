inputData = File.read("input.txt").split

gamma = ''
epsilon = ''

# Part 1

inputData[0].length.times do |i|
  col = inputData.each.map { |str| str[i] }
  if col.count('0') > col.count('1')
        gamma += '0'
        epsilon += '1'
    else
        gamma += '1'
        epsilon += '0'
    end
end

puts gamma.to_i(2) * epsilon.to_i(2)

# Part 2

i = 0
while inputData.length > 1
   col = inputData.each.map { |str| str[i] }
   
  if col.count('0') > col.count('1')
        inputData = inputData.each.select { |str| str[i] === '0'}
    else
        inputData = inputData.each.select { |str| str[i] === '1'}
    end
    
    i += 1
end

O2 = inputData[0]

inputData = File.read("input.txt").split

i = 0
while inputData.length > 1
   col = inputData.each.map { |str| str[i] }
   
  if col.count('0') > col.count('1')
        inputData = inputData.each.select { |str| str[i] === '1'}
    else
        inputData = inputData.each.select { |str| str[i] === '0'}
    end
    
    i += 1
end

CO2 = inputData[0]

puts O2.to_i(2) * CO2.to_i(2)