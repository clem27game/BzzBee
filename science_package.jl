
#!/usr/bin/env julia
# Package scientifique en Julia pour BzzBee
# Convention: pollen -> paramètres : miel

function process_scientific(operation, params...)
    if operation == "pi"
        println("🍯 Résultat: π = ", π)
    elseif operation == "e"
        println("🍯 Résultat: e = ", ℯ)
    elseif operation == "factorielle" && length(params) >= 1
        n = parse(Int, params[1])
        if n >= 0 && n <= 20
            result = factorial(n)
            println("🍯 Résultat: ", n, "! = ", result)
        else
            println("❌ Factorielle supportée pour 0-20 seulement!")
        end
    elseif operation == "fibonacci" && length(params) >= 1
        n = parse(Int, params[1])
        if n > 0 && n <= 50
            fib_seq = [1, 1]
            for i in 3:n
                push!(fib_seq, fib_seq[i-1] + fib_seq[i-2])
            end
            println("🍯 Résultat: Fibonacci(", n, ") = ", fib_seq[n])
        else
            println("❌ Fibonacci supporté pour 1-50 seulement!")
        end
    elseif operation == "prime" && length(params) >= 1
        n = parse(Int, params[1])
        is_prime = n > 1 && all(n % i != 0 for i in 2:isqrt(n))
        println("🍯 Résultat: ", n, is_prime ? " est un nombre premier" : " n'est pas un nombre premier")
    elseif operation == "sqrt" && length(params) >= 1
        x = parse(Float64, params[1])
        if x >= 0
            println("🍯 Résultat: √", x, " = ", sqrt(x))
        else
            println("❌ Racine carrée d'un nombre négatif impossible!")
        end
    elseif operation == "log" && length(params) >= 1
        x = parse(Float64, params[1])
        if x > 0
            println("🍯 Résultat: ln(", x, ") = ", log(x))
        else
            println("❌ Logarithme d'un nombre négatif ou nul impossible!")
        end
    elseif operation == "test"
        println("🍯 Package Julia BzzBee testé avec succès!")
    else
        println("""🐝 Package Science Julia BzzBee - Fonctions disponibles:
- pi
- e  
- factorielle [n]
- fibonacci [n]
- prime [n]
- sqrt [x]
- log [x]
- test""")
    end
end

if length(ARGS) > 0
    process_scientific(ARGS...)
else
    println("🍯 Package Science Julia chargé! Utilisez: pollen -> commande params : miel [jl science_package.jl]")
end
