
// Package de test en C pour BzzBee
// Convention: pollen -> paramètres : miel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("🍯 Package C BzzBee chargé! Fonctions disponibles:\n");
        printf("- puissance base exposant\n");
        printf("- racine nombre\n");
        printf("- premier nombre\n");
        printf("- binaire nombre\n");
        return 0;
    }
    
    char* operation = argv[1];
    
    if (strcmp(operation, "puissance") == 0 && argc >= 4) {
        double base = atof(argv[2]);
        double exposant = atof(argv[3]);
        double resultat = pow(base, exposant);
        printf("🍯 Résultat: %.2f ^ %.2f = %.2f\n", base, exposant, resultat);
    }
    else if (strcmp(operation, "racine") == 0 && argc >= 3) {
        double nombre = atof(argv[2]);
        if (nombre >= 0) {
            double resultat = sqrt(nombre);
            printf("🍯 Résultat: √%.2f = %.2f\n", nombre, resultat);
        } else {
            printf("❌ Impossible de calculer la racine d'un nombre négatif!\n");
        }
    }
    else if (strcmp(operation, "premier") == 0 && argc >= 3) {
        int nombre = atoi(argv[2]);
        int est_premier = 1;
        if (nombre < 2) est_premier = 0;
        for (int i = 2; i * i <= nombre; i++) {
            if (nombre % i == 0) {
                est_premier = 0;
                break;
            }
        }
        printf("🍯 Résultat: %d %s un nombre premier\n", nombre, est_premier ? "est" : "n'est pas");
    }
    else if (strcmp(operation, "binaire") == 0 && argc >= 3) {
        int nombre = atoi(argv[2]);
        if (nombre == 0) {
            printf("🍯 Résultat: 0 en binaire = 0\n");
        } else {
            char binaire[33];
            int index = 0;
            int temp = abs(nombre);
            
            while (temp > 0) {
                binaire[index++] = (temp % 2) + '0';
                temp /= 2;
            }
            
            printf("🍯 Résultat: %d en binaire = ", nombre);
            if (nombre < 0) printf("-");
            for (int i = index - 1; i >= 0; i--) {
                printf("%c", binaire[i]);
            }
            printf("\n");
        }
    }
    else {
        printf("❌ Opération non reconnue: %s\n", operation);
        printf("Fonctions disponibles: puissance, racine, premier, binaire\n");
    }
    
    return 0;
}
nombre = atoi(argv[2]);
        printf("🍯 Résultat: %d en binaire = ", nombre);
        if (nombre == 0) {
            printf("0");
        } else {
            char binaire[33];
            int index = 0;
            while (nombre > 0) {
                binaire[index++] = (nombre % 2) ? '1' : '0';
                nombre /= 2;
            }
            for (int i = index - 1; i >= 0; i--) {
                printf("%c", binaire[i]);
            }
        }
        printf("\n");
    }
    else if (strcmp(operation, "test") == 0) {
        printf("🍯 Package C BzzBee testé avec succès!\n");
    }
    else {
        printf("❌ Opération '%s' non reconnue!\n", operation);
        printf("💡 Opérations disponibles: puissance, racine, premier, binaire\n");
    }
    
    return 0;
}
