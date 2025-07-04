
#!/usr/bin/env python3
# Package pour manipulation de chaînes en Python pour BzzBee
# Convention: pollen -> paramètres : miel

import sys

def process_string(operation, text="", *args):
    if operation == "majuscule":
        return f"🍯 Résultat: {text.upper()}"
    elif operation == "minuscule":
        return f"🍯 Résultat: {text.lower()}"
    elif operation == "inverse":
        return f"🍯 Résultat: {text[::-1]}"
    elif operation == "longueur":
        return f"🍯 Longueur: {len(text)} caractères"
    elif operation == "remplacer":
        ancien = args[0] if args else ""
        nouveau = args[1] if len(args) > 1 else ""
        return f"🍯 Résultat: {text.replace(ancien, nouveau)}"
    elif operation == "compter":
        char = args[0] if args else ""
        return f"🍯 Occurences de '{char}': {text.count(char)}"
    else:
        return """🐝 Package String BzzBee - Opérations disponibles:
- majuscule
- minuscule
- inverse
- longueur
- remplacer
- compter"""

if __name__ == "__main__":
    if len(sys.argv) > 1:
        operation = sys.argv[1]
        text = sys.argv[2] if len(sys.argv) > 2 else ""
        autres_args = sys.argv[3:] if len(sys.argv) > 3 else []
        
        result = process_string(operation, text, *autres_args)
        print(result)
    else:
        print("🍯 Package String BzzBee chargé! Utilisez: pollen -> operation texte : miel")
