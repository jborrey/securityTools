# get results file ready
results = File.open('results.txt', 'w')

# enumerate
File.open('tlds.txt').each do |line|
  unless line.strip[0] == '#'
    tld = line.strip.downcase
    url = "collegiumimmortale.#{tld}"
    dig = `dig #{url}`

    if dig.include?('ANSWER SECTION') && !dig.include?('127.0.53.53')
      results.write(dig)
    end
  end
end

results.close
