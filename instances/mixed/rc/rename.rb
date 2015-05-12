#!/usr/bin/env ruby -wKU

files = #.select {|f| f != "." && f != ".." && !f.end_with?('.yaml') && '}

Dir.new('.').to_a.each do |file|
  if file =~ /\Astm/
    new_file = file.gsub(/\Astm/, 'rc')
    `mv #{file} #{new_file}`
  end
end
