
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1000
#define MAX_VARIABLES 100
#define MAX_VAR_NAME 50
#define MAX_VAR_VALUE 200

// Structure pour les variables
typedef struct {
    char name[MAX_VAR_NAME];
    char value[MAX_VAR_VALUE];
    int int_value;
    int is_number;
} Variable;

// Variables globales
Variable variables[MAX_VARIABLES];
int var_count = 0;

// Couleurs ANSI
void set_color(const char* color) {
    if (strcmp(color, "rouge") == 0 || strcmp(color, "red") == 0) {
        printf("\033[31m");
    } else if (strcmp(color, "vert") == 0 || strcmp(color, "green") == 0) {
        printf("\033[32m");
    } else if (strcmp(color, "jaune") == 0 || strcmp(color, "yellow") == 0) {
        printf("\033[33m");
    } else if (strcmp(color, "bleu") == 0 || strcmp(color, "blue") == 0) {
        printf("\033[34m");
    } else if (strcmp(color, "magenta") == 0) {
        printf("\033[35m");
    } else if (strcmp(color, "cyan") == 0) {
        printf("\033[36m");
    } else if (strcmp(color, "blanc") == 0 || strcmp(color, "white") == 0) {
        printf("\033[37m");
    }
}

void reset_color() {
    printf("\033[0m");
}

// Fonction pour enlever les espaces en début et fin
char* trim(char* str) {
    char* end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0) return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return str;
}

// Fonction pour trouver une variable
Variable* find_variable(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return &variables[i];
        }
    }
    return NULL;
}

// Fonction pour créer ou modifier une variable
void set_variable(const char* name, const char* value) {
    Variable* var = find_variable(name);
    if (var == NULL) {
        if (var_count < MAX_VARIABLES) {
            var = &variables[var_count++];
            strcpy(var->name, name);
        } else {
            printf("Erreur: Trop de variables!\n");
            return;
        }
    }
    
    strcpy(var->value, value);
    var->int_value = atoi(value);
    var->is_number = (var->int_value != 0 || strcmp(value, "0") == 0);
}

// Fonction pour évaluer une expression mathématique simple
int evaluate_math(const char* expr) {
    char* expr_copy = strdup(expr);
    char* token;
    int result = 0;
    char operation = '+';
    
    token = strtok(expr_copy, " ");
    while (token != NULL) {
        if (strcmp(token, "+") == 0) {
            operation = '+';
        } else if (strcmp(token, "-") == 0) {
            operation = '-';
        } else if (strcmp(token, "*") == 0) {
            operation = '*';
        } else if (strcmp(token, "/") == 0) {
            operation = '/';
        } else {
            int value = atoi(token);
            if (operation == '+') result += value;
            else if (operation == '-') result -= value;
            else if (operation == '*') result *= value;
            else if (operation == '/') result /= value;
        }
        token = strtok(NULL, " ");
    }
    
    free(expr_copy);
    return result;
}

// Fonction pour dessiner des formes ASCII simples
void draw_ascii(const char* shape) {
    if (strcmp(shape, "abeille") == 0) {
        printf("     ___\n");
        printf("   /     \\\n");
        printf("  | () () |\n");
        printf("   \\  ^  /\n");
        printf("    ||||||\n");
        printf("    ||||||\n");
        printf("   /_____\\\n");
    } else if (strcmp(shape, "ruche") == 0) {
        printf("    /\\_/\\_/\\\n");
        printf("   /       \\\n");
        printf("  |  RUCHE  |\n");
        printf("  |_________|\n");
        printf("   \\_______/\n");
    } else if (strcmp(shape, "fleur") == 0) {
        printf("   .-'~~~'-.\n");
        printf("  /         \\\n");
        printf(" |  () () () |\n");
        printf("  \\    ^    /\n");
        printf("   |   |   |\n");
        printf("   |   |   |\n");
    }
}

// Fonction principale d'interprétation
void interpret_line(char* line) {
    line = trim(line);
    
    // Ignorer les lignes vides et les commentaires
    if (strlen(line) == 0 || line[0] == '#') {
        return;
    }
    
    // bzz R console -> message
    if (strncmp(line, "bzz R console ->", 16) == 0) {
        char* message = line + 16;
        message = trim(message);
        printf("%s\n", message);
    }
    
    // bzz R couleur -> texte
    else if (strncmp(line, "bzz R couleur", 13) == 0) {
        char* rest = line + 13;
        char* arrow = strstr(rest, "->");
        if (arrow) {
            *arrow = '\0';
            char* color = trim(rest);
            char* text = trim(arrow + 2);
            set_color(color);
            printf("%s\n", text);
            reset_color();
        }
    }
    
    // bzz STOCK variable -> valeur
    else if (strncmp(line, "bzz STOCK", 9) == 0) {
        char* rest = line + 9;
        char* arrow = strstr(rest, "->");
        if (arrow) {
            *arrow = '\0';
            char* var_name = trim(rest);
            char* value = trim(arrow + 2);
            set_variable(var_name, value);
            printf("Variable %s = %s stockée dans la ruche!\n", var_name, value);
        }
    }
    
    // bzz MONTRE variable
    else if (strncmp(line, "bzz MONTRE", 10) == 0) {
        char* var_name = trim(line + 10);
        Variable* var = find_variable(var_name);
        if (var) {
            printf("%s\n", var->value);
        } else {
            printf("Variable %s non trouvée dans la ruche!\n", var_name);
        }
    }
    
    // bzz CALCUL expression
    else if (strncmp(line, "bzz CALCUL", 10) == 0) {
        char* expr = trim(line + 10);
        int result = evaluate_math(expr);
        printf("%d\n", result);
    }
    
    // bzz DESSINE forme
    else if (strncmp(line, "bzz DESSINE", 11) == 0) {
        char* shape = trim(line + 11);
        draw_ascii(shape);
    }
    
    // bzz DORT millisecondes
    else if (strncmp(line, "bzz DORT", 8) == 0) {
        char* time_str = trim(line + 8);
        int milliseconds = atoi(time_str);
        usleep(milliseconds * 1000);
        printf("L'abeille a dormi %d ms... Bzzzz\n", milliseconds);
    }
    
    // bzz SI condition ALORS
    else if (strncmp(line, "bzz SI", 6) == 0) {
        char* condition = line + 6;
        char* alors = strstr(condition, "ALORS");
        if (alors) {
            *alors = '\0';
            condition = trim(condition);
            // Simple condition: variable == valeur
            char* equals = strstr(condition, "==");
            if (equals) {
                *equals = '\0';
                char* var_name = trim(condition);
                char* expected = trim(equals + 2);
                Variable* var = find_variable(var_name);
                if (var && strcmp(var->value, expected) == 0) {
                    printf("Condition vraie! Bzzzz!\n");
                } else {
                    printf("Condition fausse! Bzzzz...\n");
                }
            }
        }
    }
    
    // bzz QUIZ question -> reponse
    else if (strncmp(line, "bzz QUIZ", 8) == 0) {
        char* rest = line + 8;
        char* arrow = strstr(rest, "->");
        if (arrow) {
            *arrow = '\0';
            char* question = trim(rest);
            char* answer = trim(arrow + 2);
            printf("Question: %s\n", question);
            printf("Votre réponse: ");
            char user_answer[100];
            fgets(user_answer, sizeof(user_answer), stdin);
            user_answer[strcspn(user_answer, "\n")] = 0;
            
            if (strcmp(trim(user_answer), answer) == 0) {
                printf("Bzzzz! Bonne réponse!\n");
            } else {
                printf("Bzzzz... Mauvaise réponse. La bonne réponse était: %s\n", answer);
            }
        }
    }
    
    // bzz BONJOUR
    else if (strcmp(line, "bzz BONJOUR") == 0) {
        printf("Bzzzz! Bonjour de la ruche!\n");
    }
    
    // bzz AU REVOIR
    else if (strcmp(line, "bzz AU REVOIR") == 0) {
        printf("Bzzzz! Au revoir de la ruche!\n");
        exit(0);
    }
    
    else {
        printf("Commande non reconnue: %s\n", line);
    }
}

int main(int argc, char* argv[]) {
    printf("BzzBee Interpreter v1.0 - Langage des abeilles!\n");
    printf("Utilisez 'bzzbee run fichier.bzz' pour exécuter un fichier\n");
    printf("Ou tapez des commandes directement:\n\n");
    
    if (argc == 3 && strcmp(argv[1], "run") == 0) {
        // Exécuter un fichier .bzz
        FILE* file = fopen(argv[2], "r");
        if (!file) {
            printf("Erreur: Impossible d'ouvrir le fichier %s\n", argv[2]);
            return 1;
        }
        
        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = 0; // Enlever le \n
            interpret_line(line);
        }
        
        fclose(file);
    } else {
        // Mode interactif
        char line[MAX_LINE_LENGTH];
        printf("bzz> ");
        while (fgets(line, sizeof(line), stdin)) {
            line[strcspn(line, "\n")] = 0;
            
            if (strcmp(line, "exit") == 0 || strcmp(line, "quit") == 0) {
                printf("Bzzzz! Au revoir!\n");
                break;
            }
            
            interpret_line(line);
            printf("bzz> ");
        }
    }
    
    return 0;
}
