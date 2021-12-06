require './inputReader'

inputData = InputReader.read.reject!(&:empty?)

numbers = inputData.shift.split(',').map(&:to_i)
cards = []
inputData.each_slice(5) do |el|
    cards.push(el.map(&:split).flatten.map(&:to_i))
end

scores = []
winning_cards = []

numbers.each do |number|
    cards.each_with_index do |card, i|
        next if winning_cards.include?(i)
        
        num_index = card.find_index number
        cards[i][num_index] = nil unless num_index.nil?
        
        card_row_col = card.each_slice(5).to_a
        if card_row_col.any? {|row| row.compact.empty?} || card_row_col.transpose.any? {|col| col.compact.empty?}
            scores.push(cards[i].compact.sum * number)
            winning_cards.push(i)
        end
    end
end

puts scores[0]
puts scores[-1]