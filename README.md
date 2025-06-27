
# BzzBee - Le Langage des Abeilles 🐝

   ![BzzBee](http://www.image-heberg.fr/files/17510255233353626735.png)

BzzBee est un langage de programmation simple et amusant inspiré de la communication des abeilles! Cette version 2.0 apporte de nombreuses améliorations et nouvelles fonctionnalités.

## Installation et Utilisation

```bash
# Compiler l'interpréteur
make

# Exécuter un fichier .bzz
./main run fichier.bzz

# Mode interactif
./main
```

## Nouvelles Fonctionnalités v2.0

✅ **Calculs mathématiques avancés** avec support des parenthèses, puissance, modulo  
✅ **Conditions étendues** avec SINON et opérateurs de comparaison  
✅ **Boucles POUR** avec variables d'itération  
✅ **Gestion des chaînes** avec guillemets  
✅ **Variables numériques** avec support des décimales  
✅ **Lecture interactive** avec bzz LIRE  
✅ **Gestion d'erreurs améliorée**  

## Syntaxe BzzBee

### Affichage dans la console
```
bzz R console -> "Hello World"
bzz R console -> Message sans guillemets
```

### Affichage avec couleurs
```
bzz R couleur rouge -> "Texte en rouge"
bzz R couleur vert -> "Texte en vert"
bzz R couleur jaune -> "Texte en jaune"
bzz R couleur bleu -> "Texte en bleu"
bzz R couleur magenta -> "Texte en magenta"
bzz R couleur cyan -> "Texte en cyan"
```

### Variables
```
bzz STOCK nom -> "Alice"
bzz STOCK age -> 25
bzz STOCK pi -> 3.14159
bzz MONTRE nom
bzz LIRE nouvelle_variable
```

### Mathématiques Avancées
```
bzz CALCUL 10 + 5 * 2        # Addition et multiplication
bzz CALCUL 2 ^ 3             # Puissance (8)
bzz CALCUL 15 % 4            # Modulo (3)
bzz CALCUL (10 + 5) * 2      # Parenthèses (30)
bzz CALCUL age + 5           # Utilisation de variables
```

### Conditions Étendues
```
bzz SI age > 18 ALORS
bzz R console -> "Majeur"
bzz FIN

bzz SI nom == "Alice" ALORS
bzz R console -> "Bonjour Alice!"
bzz SINON
bzz R console -> "Bonjour inconnu!"
bzz FIN
```

**Opérateurs supportés:** `==`, `!=`, `>`, `<`, `>=`, `<=`

### Boucles
```
bzz POUR i DE 1 A 10
bzz R console -> "Comptage:"
bzz MONTRE i
bzz CALCUL i * 2
bzz SUIVANT
```

### Quiz interactif
```
bzz QUIZ "Quelle est la couleur du miel?" -> "jaune"
bzz QUIZ "Combien font 2 + 2?" -> "4"
```

### Dessins ASCII
```
bzz DESSINE abeille
bzz DESSINE ruche
bzz DESSINE fleur
bzz DESSINE hexagone
```

### Délais et Contrôle
```
bzz DORT 1000          # Pause de 1000ms
bzz BONJOUR           # Message de bienvenue
bzz AU REVOIR         # Quitter le programme
```

### Commentaires
```
# Ceci est un commentaire
bzz R console -> "Code" # Commentaire en fin de ligne
```

## Exemples de Programmes

### Programme de Calcul
```bzz
bzz BONJOUR
bzz LIRE nombre1
bzz LIRE nombre2
bzz CALCUL nombre1 + nombre2
bzz AU REVOIR
```

### Compteur avec Boucle
```bzz
bzz POUR compteur DE 1 A 5
bzz R couleur vert -> "Comptage:"
bzz MONTRE compteur
bzz DORT 500
bzz SUIVANT
```

### Quiz Mathématique
```bzz
bzz R couleur jaune -> "Quiz Mathématique"
bzz QUIZ "Combien font 5 * 3?" -> "15"
bzz QUIZ "Quelle est la racine de 16?" -> "4"
bzz R couleur vert -> "Quiz terminé!"
```

## Extensions de fichier

Les programmes BzzBee utilisent l'extension `.bzz`

## Améliorations v2.0

- **Expressions mathématiques complexes** avec parenthèses
- **Support des nombres décimaux**
- **Conditions avec SINON**
- **Boucles POUR automatiques**
- **Meilleure gestion des erreurs**
- **Variables dans les calculs**
- **Lecture interactive de l'utilisateur**
- **Support des guillemets pour les chaînes**

Bzzzz! Amusez-vous bien avec BzzBee v2.0! 🐝🍯✨
