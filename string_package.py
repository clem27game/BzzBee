
#!/usr/bin/env python3
# Package de manipulation de chaînes en Python pour BzzBee
# Convention: pollen -> paramètres : miel

import sys
import re

def process_string(operation, text="", extra=""):
    """Traite les opérations sur les chaînes de caractères"""
    
    if operation == "majuscule":
        return f"🍯 Résultat: '{text}' -> '{text.upper()}'"
    
    elif operation == "minuscule":
        return f"🍯 Résultat: '{text}' -> '{text.lower()}'"
    
    elif operation == "inverse":
        return f"🍯 Résultat: '{text}' -> '{text[::-1]}'"
    
    elif operation == "longueur":
        return f"🍯 Résultat: Longueur de '{text}' = {len(text)}"
    
    elif operation == "mots":
        words = text.split()
        return f"🍯 Résultat: '{text}' contient {len(words)} mots"
    
    elif operation == "remplacer":
        if not extra:
            return "❌ Paramètre manquant pour remplacer!"
        result = text.replace(extra, "★")
        return f"🍯 Résultat: '{text}' -> '{result}' ('{extra}' remplacé par ★)"
    
    elif operation == "palindrome":
        clean_text = re.sub(r'[^a-zA-Z0-9]', '', text.lower())
        is_palindrome = clean_text == clean_text[::-1]
        return f"🍯 Résultat: '{text}' {'est' if is_palindrome else 'n\\'est pas'} un palindrome"
    
    elif operation == "voyelles":
        vowels = "aeiouAEIOU"
        count = sum(1 for char in text if char in vowels)
        return f"🍯 Résultat: '{text}' contient {count} voyelles"
    
    elif operation == "test":
        return "🍯 Package String Python testé avec succès!"
    
    else:
        return f"""🐝 Package String BzzBee - Opérations disponibles:
- majuscule [texte]
- minuscule [texte] 
- inverse [texte]
- longueur [texte]
- mots [texte]
- remplacer [texte] [ancien]
- palindrome [texte]
- voyelles [texte]"""

if __name__ == "__main__":
    if len(sys.argv) == 1:
        print(process_string("help"))
    else:
        operation = sys.argv[1] if len(sys.argv) > 1 else ""
        text = sys.argv[2] if len(sys.argv) > 2 else ""
        extra = sys.argv[3] if len(sys.argv) > 3 else ""
        print(process_string(operation, text, extra))
