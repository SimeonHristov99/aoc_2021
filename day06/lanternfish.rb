initialFish = File.read('input.txt').split(',').map(&:to_i)
@countMap = initialFish.each_with_object(Hash.new(0)){|key,hash| hash[key] += 1}

def breed(n)
    n.times {
        temp = @countMap[0]
        
          (0..7).each { |i| @countMap[i] = @countMap[i + 1] }
          @countMap[8] = temp
          @countMap[6] += temp
    }
     @countMap.values.sum
end

# p breed(80)
p breed(256)