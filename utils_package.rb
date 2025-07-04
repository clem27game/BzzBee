
#!/usr/bin/env ruby
# Package utilitaires en Ruby pour BzzBee
# Convention: pollen -> paramètres : miel

def process_command(command, *args)
  case command
  when "date"
    puts "🍯 Date actuelle: #{Time.now.strftime('%Y-%m-%d %H:%M:%S')}"
  when "hasard"
    min = (args[0] || 1).to_i
    max = (args[1] || 100).to_i
    puts "🍯 Nombre aléatoire entre #{min} et #{max}: #{rand(min..max)}"
  when "couleur"
    color = args[0] || "blanc"
    text = args[1] || "Texte coloré"
    color_codes = {
      "rouge" => "\033[31m",
      "vert" => "\033[32m", 
      "jaune" => "\033[33m",
      "bleu" => "\033[34m",
      "reset" => "\033[0m"
    }
    puts "#{color_codes[color] || ''}#{text}#{color_codes['reset']}"
  when "fibonacci"
    n = (args[0] || 10).to_i
    a, b = 0, 1
    sequence = [a, b]
    (2...n).each { sequence << sequence[-1] + sequence[-2] }
    puts "🍯 Fibonacci(#{n}): #{sequence[0, n].join(', ')}"
  else
    puts """🐝 Package Utils BzzBee - Commandes disponibles:
- date
- hasard [min] [max]
- couleur [couleur] [texte]
- fibonacci [n]"""
  end
end

if ARGV.length > 0
  process_command(*ARGV)
else
  puts "🍯 Package Utils BzzBee chargé! Utilisez: pollen -> commande paramètres : miel"
end
