
# BzzBee - Le Langage des Abeilles 🐝

   ![BzzBee](http://www.image-heberg.fr/files/17510255233353626735.png)

BzzBee est un langage de programmation généraliste simple, amusant et puissant inspiré de la communication des abeilles! Cette version 5.0 introduit des fonctionnalités avancées pour en faire un véritable langage généraliste!

## 🚀 Nouvelles Fonctionnalités v5.0

✅ **Structures de données avancées** - Listes et dictionnaires natifs  
✅ **Gestion de fichiers** - Lecture/écriture native  
✅ **Entrées utilisateur typées** - Lecture spécialisée  
✅ **Fonctions temporelles étendues** - Date et heure  
✅ **Console et ASCII art avancés** - 20+ nouvelles fonctionnalités visuelles  
✅ **Gestion d'erreurs** - Blocs ESSAI/CAPTURE  
✅ **Animations et effets** - Contenu interactif  
✅ **Système de packages** multi-langages  

## Installation et Utilisation

```bash
# Compiler BzzBee
make

# Exécuter un fichier .bzz
./main run fichier.bzz

# Mode interactif
./main

# Tester les nouvelles fonctionnalités
./main run exemple_avance.bzz
```

## 📊 Gestion des Structures de Données

### Listes Avancées
```bzz
# Créer et manipuler des listes
bzz LISTE AJOUTER ma_liste "élément1"
bzz LISTE AJOUTER ma_liste "élément2"
bzz LISTE AFFICHER ma_liste
bzz LISTE TAILLE ma_liste
bzz LISTE TRIER ma_liste
bzz LISTE RETIRER ma_liste "élément1"
```

### Dictionnaires (NECTAR)
```bzz
# Système clé-valeur pour données complexes
bzz NECTAR AJOUTER config "nom" "BzzBee"
bzz NECTAR AJOUTER config "version" "5.0"
bzz NECTAR LIRE config "nom"
bzz NECTAR AFFICHER config
bzz NECTAR SUPPRIMER config "version"
```

## 📁 Gestion de Fichiers Native

```bzz
# Opérations sur fichiers
bzz FICHIER ÉCRIRE "data.txt" "Contenu du fichier"
bzz FICHIER LIRE "data.txt"
bzz FICHIER EXISTE "data.txt"
bzz FICHIER SUPPRIMER "data.txt"
```

## 🎯 Entrées Utilisateur Avancées

```bzz
# Lectures typées et spécialisées
bzz RUCHE LIRE NOMBRE        # Lecture de nombre
bzz RUCHE LIRE OUI_NON       # Confirmation oui/non
bzz RUCHE LIRE CARACTERE     # Lecture d'un caractère
```

## ⏰ Fonctions Temporelles

```bzz
# Gestion du temps
bzz TEMPS                    # Temps complet
bzz TEMPS HEURE_ACTUELLE     # Heure actuelle
bzz TEMPS DATE_ACTUELLE      # Date actuelle
```

## 🎨 Console et ASCII Art Avancés

### Positionnement et Effets
```bzz
bzz CURSEUR 10 5            # Positionner le curseur
bzz CONSOLE EFFACER         # Effacer l'écran
bzz FLASH "Message important!" # Effet clignotant
bzz GRADIENT "Texte coloré"    # Texte arc-en-ciel
```

### Éléments Visuels
```bzz
bzz CADRE "Message"         # Encadrer du texte
bzz BANNIERE "Titre"        # Bannière décorative  
bzz SEPARATEUR              # Ligne de séparation
bzz TITRE "Section"         # Titre avec soulignement
bzz ENCADRER "Texte"        # Encadrement simple
```

### Barres de Progression
```bzz
bzz BARRE_PROGRESSION 75 100 40   # current total width
```

### Scènes Thématiques (20+ nouvelles!)
```bzz
bzz JARDIN          # Scène de jardin avec fleurs
bzz OCEAN           # Scène océanique  
bzz FORET           # Forêt avec animaux
bzz CONSTELLATION   # Étoiles dispersées
bzz GALAXIE         # Formation galactique
bzz CHATEAU         # Château fantastique
bzz LABORATOIRE     # Laboratoire scientifique
bzz VAISSEAU        # Vaisseau spatial
bzz MONTAGNE        # Paysage montagneux
bzz CITE_FUTUR      # Ville futuriste
bzz PIRATES         # Thème pirate
bzz MAGIE           # Éléments magiques
bzz FESTIVAL        # Ambiance festive
```

### Animations et Effets Sonores
```bzz
bzz ANIMATION "pluie"        # Animation de pluie
bzz ANIMATION "feu"          # Animation de feu
bzz SON "explosion"          # Effet sonore explosion
bzz SON "applaudissement"    # Applaudissements
bzz SON "vent"              # Bruit de vent
```

## 🛡️ Gestion d'Erreurs

```bzz
bzz ESSAI
    bzz FICHIER LIRE "fichier_inexistant.txt"
    bzz CALCUL 10 / 0
bzz CAPTURE
    bzz R couleur rouge -> "Erreur détectée et gérée!"
bzz FIN_ESSAI
```

## 📦 Système de Packages Multi-Langages

### Langages Supportés
- **Node.js** (`js`) - JavaScript côté serveur
- **Python** (`py`) - Langage polyvalent et puissant  
- **Julia** (`jl`) - Calcul scientifique haute performance
- **Ruby** (`rb`/`rub`) - Langage élégant et expressif
- **C** (`c`/`C`) - Performance et contrôle système
- **BzzBee** (`bzz`) - Packages natifs en BzzBee

### Syntaxe de Packages

```bzz
# Chargement de packages
bzz PACKAGE js -> math_package.js
bzz PACKAGE py -> string_package.py  
bzz PACKAGE jl -> science_package.jl

# Utilisation - Syntaxe classique
pollen -> addition 10 5 : miel
pollen -> majuscule "hello world" : miel

# Utilisation - Syntaxe étendue (spécifique)
pollen -> multiplication 8 7 : miel [js math_package.js]
pollen -> voyelles "BzzBee" : miel [py string_package.py]
pollen -> fibonacci 10 : miel [rb utils_package.rb]
```

## 🆕 Fonctionnalités Natives Complètes

### Mathématiques
```bzz
bzz CALCUL 15 + 25              # Calculs de base
bzz CALCUL sin(45)              # Fonctions trigonométriques
bzz CALCUL sqrt(16)             # Racine carrée
bzz CALCUL 2 ^ 8                # Puissances
```

### Variables et Stockage
```bzz
bzz STOCK nombre -> 42          # Stocker une valeur
bzz MONTRE nombre               # Afficher une variable
```

### Tableaux Simples
```bzz
bzz TABLEAU notes -> "15,18,12,16"
bzz MONTRE notes
```

### Contrôle de Flux
```bzz
bzz SI nombre > 10 ALORS
    bzz R console -> "Grand nombre!"
bzz SINON  
    bzz R console -> "Petit nombre!"
bzz FIN

bzz POUR i DE 1 A 5
    bzz MONTRE i
bzz SUIVANT
```

### Interactivité
```bzz
bzz QUIZ "2+2=?" -> "4"         # Question-réponse
bzz LIRE nom                    # Lecture simple
```

### Génération Aléatoire
```bzz
bzz HASARD 1 100                # Nombre aléatoire
```

### Canvas et Dessin
```bzz
bzz TOILE INIT                  # Initialiser canvas
bzz PIXEL 5 5 *                 # Dessiner pixel
bzz LIGNE 0 0 10 10 -          # Dessiner ligne
bzz TEXTE 2 2 "Hello"          # Écrire texte
bzz TOILE MONTRE               # Afficher canvas
```

### Formes ASCII Intégrées
```bzz
bzz DESSINE soleil              # Soleil ASCII
bzz DESSINE nuage               # Nuage ASCII
bzz DESSINE coeur               # Cœur ASCII
bzz DESSINE abeille             # Abeille ASCII
bzz DESSINE fleur               # Fleur ASCII
bzz DESSINE ruche               # Ruche ASCII
```

### Musique
```bzz
bzz MUSIQUE do 500              # Jouer note
bzz MUSIQUE re 300              # Durée en ms
```

### Affichage Coloré
```bzz
bzz R couleur rouge -> "Texte rouge"
bzz R couleur vert -> "Texte vert"
bzz R couleur bleu -> "Texte bleu"
bzz R couleur jaune -> "Texte jaune"
bzz R couleur cyan -> "Texte cyan"
bzz R couleur magenta -> "Texte magenta"
bzz R console -> "Texte normal"
```

## 🎯 Exemple Complet d'Application

```bzz
# Application complète de gestion de données
bzz BONJOUR
bzz BANNIERE "GESTIONNAIRE DE TÂCHES BZZBEE"

# Configuration avec dictionnaire
bzz NECTAR AJOUTER config "nom_app" "TaskBee"
bzz NECTAR AJOUTER config "version" "1.0"

# Liste de tâches
bzz LISTE AJOUTER taches "Apprendre BzzBee"
bzz LISTE AJOUTER taches "Créer un projet"
bzz LISTE AJOUTER taches "Partager avec la communauté"

# Affichage
bzz TITRE "Configuration"
bzz NECTAR AFFICHER config

bzz TITRE "Mes Tâches"
bzz LISTE AFFICHER taches
bzz LISTE TAILLE taches

# Sauvegarde
bzz FICHIER ÉCRIRE "taches.txt" "Tâches sauvegardées"

# Intégration avec packages externes
bzz PACKAGE js -> math_package.js
pollen -> addition 100 50 : miel

# Effets visuels
bzz BARRE_PROGRESSION 100 100 30
bzz FESTIVAL

bzz R couleur vert -> "Application terminée avec succès!"
bzz AU REVOIR
```

## 🌟 Avantages de BzzBee v5.0

- **Langage Généraliste** : Capable de gérer des projets variés
- **Structures de Données** : Listes et dictionnaires natifs
- **Manipulation de Fichiers** : I/O intégré 
- **Gestion d'Erreurs** : Programmes robustes
- **Polyvalence** : Packages multi-langages
- **Créativité** : ASCII art et animations étendues
- **Simplicité** : Syntaxe claire inspirée des abeilles
- **Extensibilité** : Écosystème de packages
- **Interactivité** : Entrées utilisateur avancées

## 🛠️ Applications Possibles

Avec BzzBee v5.0, vous pouvez créer :

- **Applications Web** (avec packages Node.js)
- **Scripts d'automatisation** (gestion de fichiers)
- **Jeux textuels** (entrées utilisateur + ASCII art)
- **Outils de données** (listes + dictionnaires)
- **Applications scientifiques** (packages Julia/Python)
- **Utilitaires système** (packages C)
- **Interfaces console** (positionnement + effets visuels)
- **Contenu interactif** (animations + sons)

## 📚 Guide de Développement

### 1. Projet Simple
```bzz
# Calculatrice interactive
bzz BANNIERE "CALCULATRICE BZZBEE"
bzz RUCHE LIRE NOMBRE 
pollen -> addition 10 20 : miel [js math_package.js]
bzz BARRE_PROGRESSION 100 100 40
```

### 2. Gestion de Données
```bzz
# Base de données simple
bzz NECTAR AJOUTER users "alice" "admin"
bzz NECTAR AJOUTER users "bob" "user"
bzz LISTE AJOUTER logs "login alice"
bzz FICHIER ÉCRIRE "backup.txt" "Données sauvegardées"
```

### 3. Interface Visuelle
```bzz
# Menu interactif
bzz CONSOLE EFFACER
bzz CADRE "MENU PRINCIPAL"
bzz CURSEUR 5 10
bzz GRADIENT "Options disponibles"
bzz SEPARATEUR
```

Bzzzz! Explorez toutes les possibilités créatives de BzzBee v5.0 - maintenant un véritable langage de programmation généraliste! 🐝🚀📊🎨✨

---
*Créé avec 💛 pour la communauté des développeurs créatifs!*
