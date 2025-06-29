
# BzzBee - Le Langage des Abeilles 🐝

   ![BzzBee](http://www.image-heberg.fr/files/17510255233353626735.png)

BzzBee est un langage de programmation simple et amusant inspiré de la communication des abeilles! Cette version 3.0 apporte de nombreuses nouvelles fonctionnalités créatives et techniques.

## Installation et Utilisation

```bash
# Compiler l'interpréteur
make

# Exécuter un fichier .bzz
./main run fichier.bzz

# Mode interactif
./main
```

## 🆕 Nouvelles Fonctionnalités v3.0

✅ **Tableaux et listes** pour stocker plusieurs valeurs  
✅ **Fonctions mathématiques avancées** (sin, cos, sqrt)  
✅ **Génération de nombres aléatoires**  
✅ **Système de musique** avec notes et mélodies  
✅ **Canvas graphique** pour dessiner en ASCII  
✅ **Nouvelles formes ASCII** (soleil, nuage, cœur)  
✅ **Utilitaires système** (temps, effacement d'écran)  
✅ **Expressions mathématiques complexes**  

## Syntaxe BzzBee Complète

### Affichage et Couleurs
```bzz
bzz R console -> "Hello World"
bzz R couleur rouge -> "Texte en rouge"
bzz R couleur vert -> "Texte en vert"
bzz R couleur jaune -> "Texte en jaune"
bzz R couleur bleu -> "Texte en bleu"
bzz R couleur magenta -> "Texte en magenta"
bzz R couleur cyan -> "Texte en cyan"
```

### Variables et Tableaux
```bzz
# Variables simples
bzz STOCK nom -> "Alice"
bzz STOCK age -> 25
bzz STOCK pi -> 3.14159

# Tableaux
bzz TABLEAU nombres -> "1,2,3,4,5"
bzz TABLEAU notes -> "7.5,8.2,9.1,6.8"
bzz TABLEAU noms -> "Alice,Bob,Charlie"

# Affichage
bzz MONTRE nom
bzz MONTRE nombres
```

### Mathématiques Avancées
```bzz
# Opérations de base
bzz CALCUL 10 + 5 * 2
bzz CALCUL 2 ^ 3
bzz CALCUL 15 % 4
bzz CALCUL (10 + 5) * 2

# Fonctions trigonométriques (en degrés)
bzz CALCUL sin(30)          # Résultat: 0.5
bzz CALCUL cos(60)          # Résultat: 0.5
bzz CALCUL sin(90)          # Résultat: 1.0

# Racine carrée
bzz CALCUL sqrt(16)         # Résultat: 4
bzz CALCUL sqrt(25)         # Résultat: 5

# Utilisation de variables
bzz STOCK angle -> 45
bzz CALCUL sin(angle)
```

### Génération Aléatoire
```bzz
bzz HASARD 1 100           # Nombre entre 1 et 100
bzz HASARD 1 6             # Simuler un dé
bzz HASARD 10 50           # Nombre entre 10 et 50
```

### Système Musical 🎵
```bzz
# Notes individuelles (durée en millisecondes)
bzz MUSIQUE do 500
bzz MUSIQUE re 500
bzz MUSIQUE mi 500
bzz MUSIQUE fa 500
bzz MUSIQUE sol 500
bzz MUSIQUE la 500
bzz MUSIQUE si 500

# Mélodie simple
bzz MUSIQUE do 300
bzz MUSIQUE mi 300
bzz MUSIQUE sol 300
bzz MUSIQUE do 600
```

### Canvas et Dessin 🎨
```bzz
# Initialiser le canvas
bzz TOILE INIT

# Dessiner des pixels
bzz PIXEL 5 5 *            # Pixel à (5,5) avec caractère '*'
bzz PIXEL 10 10 @          # Pixel à (10,10) avec caractère '@'

# Écrire du texte
bzz TEXTE 2 2 "HELLO"      # Texte à la position (2,2)

# Dessiner des lignes
bzz LIGNE 0 0 20 10 -      # Ligne de (0,0) à (20,10) avec '-'
bzz LIGNE 0 10 20 0 +      # Ligne de (0,10) à (20,0) avec '+'

# Afficher le canvas
bzz TOILE MONTRE
```

### Formes ASCII Étendues
```bzz
bzz DESSINE abeille        # Abeille classique
bzz DESSINE ruche          # Ruche d'abeilles
bzz DESSINE fleur          # Belle fleur
bzz DESSINE hexagone       # Forme hexagonale
bzz DESSINE soleil         # ☀️ Soleil brillant
bzz DESSINE nuage          # ☁️ Nuage moelleux
bzz DESSINE coeur          # ❤️ Cœur d'amour
```

### Conditions Avancées
```bzz
bzz SI age > 18 ALORS
bzz R console -> "Majeur"
bzz SINON
bzz R console -> "Mineur"
bzz FIN

# Comparaisons disponibles: ==, !=, >, <, >=, <=
```

### Boucles
```bzz
bzz POUR compteur DE 1 A 10
bzz R console -> "Comptage:"
bzz MONTRE compteur
bzz CALCUL compteur * 2
bzz HASARD 1 10
bzz SUIVANT
```

### Interactions et Saisie
```bzz
bzz LIRE nom               # Lire une valeur
bzz QUIZ "Question?" -> "Réponse"
```

### Utilitaires Système
```bzz
bzz TEMPS                  # Afficher l'heure actuelle
bzz EFFACE                 # Effacer l'écran
bzz DORT 1000              # Pause de 1000ms
```

### Contrôle de Programme
```bzz
bzz BONJOUR               # Message de bienvenue
bzz AU REVOIR             # Quitter le programme
```

## Exemples de Programmes Avancés

### 🎮 Mini-Jeu de Devinette
```bzz
bzz BONJOUR
bzz R couleur jaune -> "=== JEU DE DEVINETTE ==="
bzz HASARD 1 10
bzz STOCK nombre_secret -> ?
bzz R console -> "Devinez le nombre entre 1 et 10!"
bzz LIRE guess
bzz SI guess == nombre_secret ALORS
bzz R couleur vert -> "BRAVO! Vous avez trouvé!"
bzz SINON
bzz R couleur rouge -> "Dommage! Réessayez!"
bzz FIN
bzz AU REVOIR
```

### 🎨 Art ASCII Animé
```bzz
bzz TOILE INIT
bzz POUR frame DE 1 A 5
bzz TOILE INIT
bzz PIXEL frame frame *
bzz PIXEL frame+5 frame+2 @
bzz TEXTE 10 5 "ANIMATION"
bzz TOILE MONTRE
bzz DORT 500
bzz SUIVANT
```

### 🎵 Composition Musicale
```bzz
bzz R couleur cyan -> "=== Mélodie des Abeilles ==="
bzz TABLEAU melodie -> "do,re,mi,fa,sol,fa,mi,re,do"
bzz POUR note DE 1 A 9
bzz MUSIQUE do 300    # Simplification pour l'exemple
bzz DORT 100
bzz SUIVANT
```

### 📊 Calculatrice Scientifique
```bzz
bzz R couleur magenta -> "=== Calculatrice BzzBee ==="
bzz LIRE angle
bzz R console -> "Sinus:"
bzz CALCUL sin(angle)
bzz R console -> "Cosinus:"
bzz CALCUL cos(angle)
bzz R console -> "Racine carrée:"
bzz CALCUL sqrt(angle)
```

### 🎯 Système de Quiz Interactif
```bzz
bzz R couleur jaune -> "=== QUIZ MATHÉMATIQUE ==="
bzz HASARD 1 10
bzz STOCK a -> ?
bzz HASARD 1 10
bzz STOCK b -> ?
bzz CALCUL a + b
bzz STOCK resultat -> ?
bzz QUIZ "Combien font {a} + {b}?" -> resultat
```

## Extensions et Personnalisation

Les programmes BzzBee utilisent l'extension `.bzz` et peuvent être étendus avec de nouvelles fonctionnalités selon vos besoins créatifs!

## Nouveautés v3.0

- **🎨 Canvas graphique** pour créer des dessins ASCII
- **🎵 Système musical** avec support des notes
- **📊 Tableaux** pour manipuler des listes de données
- **🔢 Fonctions mathématiques** avancées (trigonométrie)
- **🎲 Générateur aléatoire** pour les jeux
- **⏰ Utilitaires système** (temps, effacement)
- **🎭 Nouvelles formes ASCII** créatives
- **🚀 Performance améliorée** et gestion d'erreurs

Bzzzz! Explorez toutes les possibilités créatives de BzzBee v3.0! 🐝🎨🎵✨

---
*Créé avec 💛 pour la communauté des développeurs créatifs!*
