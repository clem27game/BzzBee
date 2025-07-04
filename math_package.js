
// Package mathématique en Node.js pour BzzBee
// Convention: pollen -> paramètres : miel

const args = process.argv.slice(2);

if (args.length > 0) {
    const operation = args[0];
    const a = parseFloat(args[1]) || 0;
    const b = parseFloat(args[2]) || 0;
    
    switch(operation) {
        case 'addition':
            console.log(`🍯 Résultat: ${a} + ${b} = ${a + b}`);
            break;
        case 'soustraction':
            console.log(`🍯 Résultat: ${a} - ${b} = ${a - b}`);
            break;
        case 'multiplication':
            console.log(`🍯 Résultat: ${a} * ${b} = ${a * b}`);
            break;
        case 'division':
            if (b !== 0) {
                console.log(`🍯 Résultat: ${a} / ${b} = ${a / b}`);
            } else {
                console.log('❌ Division par zéro!');
            }
            break;
        case 'factorielle':
            let fact = 1;
            for (let i = 1; i <= a; i++) {
                fact *= i;
            }
            console.log(`🍯 Factorielle de ${a} = ${fact}`);
            break;
        default:
            console.log('🐝 Package Math BzzBee - Opérations disponibles:');
            console.log('- addition');
            console.log('- soustraction');
            console.log('- multiplication');
            console.log('- division');
            console.log('- factorielle');
    }
} else {
    console.log('🍯 Package Math BzzBee chargé! Utilisez: pollen -> operation nombre1 nombre2 : miel');
}
