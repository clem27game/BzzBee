# BzzBee - Le Langage des Abeilles 🐝

   ![BzzBee](http://www.image-heberg.fr/files/17510255233353626735.png)

BzzBee est un langage de programmation simple et amusant inspiré de la communication des abeilles! Cette version 4.0 introduit un système révolutionnaire de packages multi-langages!

## Installation et Utilisation

```bash
# Exécuter un fichier .bzz
./BzzBee/main run fichier.bzz

# Mode interactif
./BzzBee/main
```

## 🚀 NOUVEAU! Système de Packages v4.0

✅ **Packages multi-langages** - Créez des packages en Node.js, Python, Julia, Ruby, C ou BzzBee natif  
✅ **Convention universelle** - Toutes les fonctions utilisent le format `pollen -> paramètres : miel`  
✅ **Intégration transparente** - Combinez packages externes avec fonctionnalités natives  
✅ **Écosystème extensible** - Partagez et réutilisez du code facilement  

## 📦 Création de Packages

### Langages Supportés
- **Node.js** (`js`) - JavaScript côté serveur
- **Python** (`py`) - Langage polyvalent et puissant  
- **Julia** (`jl`) - Calcul scientifique haute performance
- **Ruby** (`rb`/`rub`) - Langage élégant et expressif
- **C** (`c`/`C`) - Performance et contrôle système
- **BzzBee** (`bzz`) - Packages natifs en BzzBee

### Syntaxe de Chargement et d'Utilisation

```bzz
# Charger un package (optionnel avec la syntaxe étendue)
bzz PACKAGE js -> math_package.js
bzz PACKAGE py -> string_package.py  
bzz PACKAGE jl -> science_package.jl
bzz PACKAGE rub -> utils_package.rb
bzz PACKAGE C -> system_package.c
bzz PACKAGE bzz -> art_package.bzz

# Syntaxe 1: Utiliser tous les packages chargés
pollen -> addition 10 5 : miel
pollen -> majuscule "hello world" : miel
pollen -> fibonacci 10 : miel

# Syntaxe 2: Spécifier le langage et fichier explicitement
pollen -> addition 10 5 : miel [js math_package.js]
pollen -> majuscule "hello world" : miel [py string_package.py]
pollen -> fibonacci 10 : miel [rb utils_package.rb]
pollen -> pi : miel [jl science_package.jl]
pollen -> puissance 2 8 : miel [c test_package.c]
```

## 🍯 Convention des Fonctions

Toutes les fonctions de packages doivent respecter le format :
```bzz
pollen -> paramètres_de_la_fonction : miel
```

**Exemples :**
```bzz
# Syntaxe classique (recherche dans tous les packages)
pollen -> addition 15 25 : miel
pollen -> inverse "BzzBee" : miel  
pollen -> couleur rouge "Texte coloré" : miel
pollen -> fibonacci 8 : miel

# Syntaxe étendue (langage et fichier spécifiques)
pollen -> multiplication 8 7 : miel [js math_package.js]
pollen -> voyelles "BzzBee" : miel [py string_package.py]
pollen -> hasard 1 100 : miel [rb utils_package.rb] 
pollen -> sqrt 64 : miel [jl science_package.jl]
pollen -> binaire 42 : miel [c test_package.c]
```

## 📝 Exemples de Packages

### Package Math (Node.js)
```javascript
// math_package.js
const args = process.argv.slice(2);
const operation = args[0];
const a = parseFloat(args[1]) || 0;
const b = parseFloat(args[2]) || 0;

switch(operation) {
    case 'addition':
        console.log(`🍯 Résultat: ${a} + ${b} = ${a + b}`);
        break;
    case 'multiplication':
        console.log(`🍯 Résultat: ${a} * ${b} = ${a * b}`);
        break;
    // ... autres opérations
}
```

### Package String (Python)
```python
# string_package.py
import sys

def process_string(operation, text=""):
    if operation == "majuscule":
        return f"🍯 Résultat: {text.upper()}"
    elif operation == "inverse":
        return f"🍯 Résultat: {text[::-1]}"
    # ... autres opérations

if __name__ == "__main__":
    operation = sys.argv[1] if len(sys.argv) > 1 else ""
    text = sys.argv[2] if len(sys.argv) > 2 else ""
    print(process_string(operation, text))
```

### Package Native (BzzBee)
```bzz
# art_package.bzz
bzz R couleur cyan -> "🎨 Package Art BzzBee"
bzz TOILE INIT
bzz LIGNE 5 5 25 5 =
bzz TEXTE 8 10 "BZZBEE ART"
bzz TOILE MONTRE
bzz DESSINE abeille
```

## 🎯 Exemple Complet d'Utilisation

```bzz
# exemple_packages.bzz
bzz BONJOUR
bzz R couleur jaune -> "=== SYSTÈME DE PACKAGES BZZBEE ==="

# Chargement des packages
bzz PACKAGE js -> math_package.js
bzz PACKAGE py -> string_package.py
bzz PACKAGE rub -> utils_package.rb

# Utilisation des packages
pollen -> addition 10 5 : miel          # Package Node.js
pollen -> majuscule "bzzbee" : miel     # Package Python
pollen -> date : miel                   # Package Ruby

# Combinaison avec BzzBee natif
bzz CALCUL 15 + 25                      # Fonction native
bzz DESSINE abeille                     # Fonction native
bzz R couleur vert -> "Parfait!"        # Fonction native

bzz AU REVOIR
```

## 🆕 Fonctionnalités v4.0

- **🎨 Canvas graphique** pour créer des dessins ASCII
- **🎵 Système musical** avec support des notes
- **📊 Tableaux** pour manipuler des listes de données
- **🔢 Fonctions mathématiques** avancées (trigonométrie)
- **🎲 Générateur aléatoire** pour les jeux
- **📦 NOUVEAU! Système de packages** multi-langages
- **🔗 NOUVEAU! Convention universelle** pollen/miel
- **🚀 NOUVEAU! Écosystème extensible** pour développeurs

## 🛠️ Guide de Développement de Packages

### 1. Créer le fichier source
Écrivez votre code dans le langage de votre choix parmi ceux supportés.

### 2. Respecter la convention
Vos fonctions doivent accepter des paramètres et répondre au format pollen/miel.

### 3. Tester l'intégration
```bzz
bzz PACKAGE votre_langage -> votre_fichier.ext
pollen -> test_function param1 param2 : miel
```

### 4. Partager avec la communauté
Les packages peuvent être facilement partagés et réutilisés!

## 🌟 Avantages du Système de Packages

- **Polyvalence** : Utilisez la puissance de plusieurs langages
- **Réutilisabilité** : Partagez et réutilisez du code facilement
- **Performance** : Choisissez le meilleur langage pour chaque tâche
- **Communauté** : Construisez un écosystème riche et collaboratif
- **Simplicité** : Convention claire et uniforme

Bzzzz! Explorez toutes les possibilités créatives de BzzBee v4.0 et son système de packages révolutionnaire! 🐝📦🎨🎵✨

---
*Créé avec 💛 pour la communauté des développeurs créatifs!*