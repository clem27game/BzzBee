
#!/usr/bin/env node
// Package mathématique en JavaScript pour BzzBee
// Convention: pollen -> paramètres : miel

const args = process.argv.slice(2);

if (args.length === 0) {
    console.log("🍯 Package Math BzzBee chargé! Fonctions disponibles:");
    console.log("- addition [a] [b]");
    console.log("- soustraction [a] [b]");
    console.log("- multiplication [a] [b]");
    console.log("- division [a] [b]");
    console.log("- modulo [a] [b]");
    console.log("- factorielle [n]");
    process.exit(0);
}

const operation = args[0];gsfunction calculate(op, a, b) {
    const numA = parseFloat(a) || 0;
    const numB = parseFloat(b) || 0;
    
    switch(op) {
        case 'addition':
            return `🍯 Résultat: ${numA} + ${numB} = ${numA + numB}`;
        case 'soustraction':
            return `🍯 Résultat: ${numA} - ${numB} = ${numA - numB}`;
        case 'multiplication':
            return `🍯 Résultat: ${numA} × ${numB} = ${numA * numB}`;
        case 'division':
            if (numB === 0) return "❌ Division par zéro impossible!";
            return `🍯 Résultat: ${numA} ÷ ${numB} = ${numA / numB}`;
        case 'modulo':
            if (numB === 0) return "❌ Modulo par zéro impossible!";
            return `🍯 Résultat: ${numA} % ${numB} = ${numA % numB}`;
        case 'factorielle':
            if (numA < 0 || !Number.isInteger(numA)) return "❌ Factorielle uniquement pour les entiers positifs!";
            let fact = 1;
            for (let i = 1; i <= numA; i++) fact *= i;
            return `🍯 Résultat: ${numA}! = ${fact}`;
        case 'test':
            return "🍯 Package Math JavaScript testé avec succès!";
        default:
            return `❌ Opération '${op}' non reconnue!`;
    }
}

console.log(calculate(operation, args[1], args[2]));ole.log(calculate(operation, args[1], args[2]));
