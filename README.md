
# BzzBee - Le Langage des Abeilles 🐝

BzzBee est un langage de programmation simple et amusant inspiré de la communication des abeilles!

## Installation et Utilisation

```bash
# Compiler l'interpréteur
make

# Exécuter un fichier .bzz
./main run fichier.bzz

# Mode interactif
./main
```

## Syntaxe BzzBee

### Affichage dans la console
```
bzz R console -> Hello World
```

### Affichage avec couleurs
```
bzz R couleur rouge -> Texte en rouge
bzz R couleur vert -> Texte en vert
bzz R couleur jaune -> Texte en jaune
bzz R couleur bleu -> Texte en bleu
```

### Variables
```
bzz STOCK nom -> Alice
bzz STOCK age -> 25
bzz MONTRE nom
```

### Mathématiques
```
bzz CALCUL 10 + 5 * 2
bzz CALCUL 20 - 3
```

### Conditions
```
bzz SI nom == Alice ALORS
```

### Quiz interactif
```
bzz QUIZ Quelle est la couleur du miel? -> jaune
```

### Dessins ASCII
```
bzz DESSINE abeille
bzz DESSINE ruche
bzz DESSINE fleur
```

### Délais
```
bzz DORT 1000    # Pause de 1000ms
```

### Salutations
```
bzz BONJOUR      # Message de bienvenue
bzz AU REVOIR    # Quitter le programme
```

## Exemples

Voir le fichier `exemple.bzz` pour un programme complet!

## Extensions de fichier

Les programmes BzzBee utilisent l'extension `.bzz`

Bzzzz! Amusez-vous bien avec BzzBee! 🐝🍯
