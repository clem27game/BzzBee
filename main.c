
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>

#define MAX_LINE_LENGTH 1000
#define MAX_VARIABLES 100
#define MAX_VAR_NAME 50
#define MAX_VAR_VALUE 200
#define MAX_LOOPS 10
#define MAX_CONDITIONS 10

// Structure pour les variables
typedef struct {
    char name[MAX_VAR_NAME];
    char value[MAX_VAR_VALUE];
    double num_value;
    int is_number;
} Variable;

// Structure pour les boucles
typedef struct {
    int start_line;
    int current_iteration;
    int max_iterations;
    char condition[MAX_LINE_LENGTH];
    int is_active;
} Loop;

// Variables globales
Variable variables[MAX_VARIABLES];
Loop loops[MAX_LOOPS];
int var_count = 0;
int loop_count = 0;
int current_line = 0;
char program_lines[1000][MAX_LINE_LENGTH];
int total_lines = 0;
int skip_until_end = 0;

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
    } else {
        printf("\033[0m"); // Reset si couleur inconnue
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

// Fonction pour enlever les guillemets
char* remove_quotes(char* str) {
    str = trim(str);
    if (str[0] == '"' && str[strlen(str)-1] == '"') {
        str[strlen(str)-1] = '\0';
        return str + 1;
    }
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
    
    strcpy(var->value, remove_quotes((char*)value));
    var->num_value = atof(var->value);
    var->is_number = (var->num_value != 0.0 || strcmp(var->value, "0") == 0 || strcmp(var->value, "0.0") == 0);
}

// Fonction pour évaluer une expression mathématique avancée
double evaluate_expression(const char* expr) {
    char* expr_copy = strdup(expr);
    char* saveptr;
    char* token;
    double result = 0;
    char operation = '+';
    int first = 1;
    
    // Support des parenthèses simple
    if (strchr(expr_copy, '(')) {
        // Traitement basique des parenthèses
        char* start = strchr(expr_copy, '(');
        char* end = strchr(expr_copy, ')');
        if (start && end && end > start) {
            *end = '\0';
            double sub_result = evaluate_expression(start + 1);
            char temp[100];
            sprintf(temp, "%.2f", sub_result);
            strcpy(start, temp);
            memmove(start + strlen(temp), end + 1, strlen(end + 1) + 1);
        }
    }
    
    token = strtok_r(expr_copy, " ", &saveptr);
    while (token != NULL) {
        if (strcmp(token, "+") == 0) {
            operation = '+';
        } else if (strcmp(token, "-") == 0) {
            operation = '-';
        } else if (strcmp(token, "*") == 0) {
            operation = '*';
        } else if (strcmp(token, "/") == 0) {
            operation = '/';
        } else if (strcmp(token, "^") == 0 || strcmp(token, "**") == 0) {
            operation = '^';
        } else if (strcmp(token, "%") == 0) {
            operation = '%';
        } else {
            double value;
            // Vérifier si c'est une variable
            Variable* var = find_variable(token);
            if (var && var->is_number) {
                value = var->num_value;
            } else {
                value = atof(token);
            }
            
            if (first) {
                result = value;
                first = 0;
            } else {
                switch (operation) {
                    case '+': result += value; break;
                    case '-': result -= value; break;
                    case '*': result *= value; break;
                    case '/': 
                        if (value != 0) result /= value;
                        else printf("Erreur: Division par zéro!\n");
                        break;
                    case '^': result = pow(result, value); break;
                    case '%': result = fmod(result, value); break;
                }
            }
        }
        token = strtok_r(NULL, " ", &saveptr);
    }
    
    free(expr_copy);
    return result;
}

// Fonction pour évaluer une condition
int evaluate_condition(const char* condition) {
    char* cond_copy = strdup(condition);
    char* var_name = strtok(cond_copy, " ");
    char* operator = strtok(NULL, " ");
    char* value = strtok(NULL, " ");
    
    if (!var_name || !operator || !value) {
        free(cond_copy);
        return 0;
    }
    
    Variable* var = find_variable(var_name);
    if (!var) {
        free(cond_copy);
        return 0;
    }
    
    int result = 0;
    if (strcmp(operator, "==") == 0) {
        result = (strcmp(var->value, value) == 0);
    } else if (strcmp(operator, "!=") == 0) {
        result = (strcmp(var->value, value) != 0);
    } else if (strcmp(operator, ">") == 0 && var->is_number) {
        result = (var->num_value > atof(value));
    } else if (strcmp(operator, "<") == 0 && var->is_number) {
        result = (var->num_value < atof(value));
    } else if (strcmp(operator, ">=") == 0 && var->is_number) {
        result = (var->num_value >= atof(value));
    } else if (strcmp(operator, "<=") == 0 && var->is_number) {
        result = (var->num_value <= atof(value));
    }
    
    free(cond_copy);
    return result;
}

// Fonction pour dessiner des formes ASCII
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
    } else if (strcmp(shape, "hexagone") == 0) {
        printf("   ___\n");
        printf("  /   \\\n");
        printf(" |     |\n");
        printf(" |     |\n");
        printf("  \\___/\n");
    } else {
        printf("Forme '%s' non reconnue. Formes disponibles: abeille, ruche, fleur, hexagone\n", shape);
    }
}

// Fonction pour interpréter une ligne
int interpret_line(char* line) {
    line = trim(line);
    
    // Ignorer les lignes vides et les commentaires
    if (strlen(line) == 0 || line[0] == '#') {
        return 0;
    }
    
    // bzz R console -> message
    if (strncmp(line, "bzz R console ->", 16) == 0) {
        char* message = line + 16;
        message = trim(message);
        printf("%s\n", remove_quotes(message));
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
            printf("%s\n", remove_quotes(text));
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
            printf("Variable %s = %s stockée dans la ruche!\n", var_name, remove_quotes(value));
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
        double result = evaluate_expression(expr);
        if (result == (int)result) {
            printf("%.0f\n", result);
        } else {
            printf("%.2f\n", result);
        }
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
            if (evaluate_condition(condition)) {
                printf("Condition vraie! Bzzzz!\n");
                skip_until_end = 0;
            } else {
                printf("Condition fausse! Bzzzz...\n");
                skip_until_end = 1;
            }
        }
    }
    
    // bzz SINON
    else if (strcmp(line, "bzz SINON") == 0) {
        skip_until_end = !skip_until_end;
        if (!skip_until_end) {
            printf("Branche SINON exécutée! Bzzzz!\n");
        }
    }
    
    // bzz FIN
    else if (strcmp(line, "bzz FIN") == 0) {
        skip_until_end = 0;
    }
    
    // bzz POUR variable DE valeur A valeur
    else if (strncmp(line, "bzz POUR", 8) == 0) {
        char* rest = line + 8;
        char* var_name = strtok(rest, " ");
        char* de = strtok(NULL, " ");
        char* start_val = strtok(NULL, " ");
        char* a = strtok(NULL, " ");
        char* end_val = strtok(NULL, " ");
        
        if (var_name && de && start_val && a && end_val && 
            strcmp(de, "DE") == 0 && strcmp(a, "A") == 0) {
            int start = atoi(start_val);
            int end = atoi(end_val);
            
            if (loop_count < MAX_LOOPS) {
                loops[loop_count].start_line = current_line;
                loops[loop_count].current_iteration = start;
                loops[loop_count].max_iterations = end;
                strcpy(loops[loop_count].condition, var_name);
                loops[loop_count].is_active = 1;
                
                // Initialiser la variable de boucle
                char val_str[20];
                sprintf(val_str, "%d", start);
                set_variable(var_name, val_str);
                
                loop_count++;
                printf("Début de boucle POUR %s de %d à %d\n", var_name, start, end);
            }
        }
    }
    
    // bzz SUIVANT
    else if (strcmp(line, "bzz SUIVANT") == 0) {
        if (loop_count > 0) {
            Loop* current_loop = &loops[loop_count - 1];
            current_loop->current_iteration++;
            
            if (current_loop->current_iteration <= current_loop->max_iterations) {
                // Mettre à jour la variable de boucle
                char val_str[20];
                sprintf(val_str, "%d", current_loop->current_iteration);
                set_variable(current_loop->condition, val_str);
                
                // Retourner au début de la boucle
                current_line = current_loop->start_line;
                return 1; // Indique qu'il faut continuer la boucle
            } else {
                // Fin de boucle
                printf("Fin de boucle POUR\n");
                loop_count--;
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
            printf("Question: %s\n", remove_quotes(question));
            printf("Votre réponse: ");
            char user_answer[100];
            if (fgets(user_answer, sizeof(user_answer), stdin)) {
                user_answer[strcspn(user_answer, "\n")] = 0;
                
                if (strcmp(trim(user_answer), remove_quotes(answer)) == 0) {
                    printf("Bzzzz! Bonne réponse!\n");
                } else {
                    printf("Bzzzz... Mauvaise réponse. La bonne réponse était: %s\n", remove_quotes(answer));
                }
            }
        }
    }
    
    // bzz LIRE variable
    else if (strncmp(line, "bzz LIRE", 8) == 0) {
        char* var_name = trim(line + 8);
        printf("Entrez une valeur pour %s: ", var_name);
        char input[MAX_VAR_VALUE];
        if (fgets(input, sizeof(input), stdin)) {
            input[strcspn(input, "\n")] = 0;
            set_variable(var_name, input);
        }
    }
    
    // bzz BONJOUR
    else if (strcmp(line, "bzz BONJOUR") == 0) {
        printf("Bzzzz! Bonjour de la ruche! 🐝\n");
    }
    
    // bzz AU REVOIR
    else if (strcmp(line, "bzz AU REVOIR") == 0) {
        printf("Bzzzz! Au revoir de la ruche! 🐝🍯\n");
        return -1; // Signal pour quitter
    }
    
    else if (!skip_until_end) {
        printf("Commande non reconnue: %s\n", line);
    }
    
    return 0;
}

int main(int argc, char* argv[]) {
    printf("🐝 BzzBee Interpreter v2.0 - Langage des abeilles! 🐝\n");
    printf("Utilisez 'bzzbee run fichier.bzz' pour exécuter un fichier\n");
    printf("Ou tapez des commandes directement:\n\n");
    
    if (argc == 3 && strcmp(argv[1], "run") == 0) {
        // Exécuter un fichier .bzz
        FILE* file = fopen(argv[2], "r");
        if (!file) {
            printf("❌ Erreur: Impossible d'ouvrir le fichier %s\n", argv[2]);
            return 1;
        }
        
        // Charger tout le programme en mémoire
        char line[MAX_LINE_LENGTH];
        total_lines = 0;
        while (fgets(line, sizeof(line), file) && total_lines < 1000) {
            line[strcspn(line, "\n")] = 0;
            strcpy(program_lines[total_lines], line);
            total_lines++;
        }
        fclose(file);
        
        // Exécuter le programme ligne par ligne
        current_line = 0;
        while (current_line < total_lines) {
            if (!skip_until_end || strncmp(program_lines[current_line], "bzz FIN", 7) == 0 || 
                strncmp(program_lines[current_line], "bzz SINON", 9) == 0) {
                int result = interpret_line(program_lines[current_line]);
                if (result == -1) break; // AU REVOIR
                if (result == 1) continue; // Boucle, ne pas incrémenter
            }
            current_line++;
        }
        
    } else {
        // Mode interactif
        char line[MAX_LINE_LENGTH];
        printf("bzz> ");
        while (fgets(line, sizeof(line), stdin)) {
            line[strcspn(line, "\n")] = 0;
            
            if (strcmp(line, "exit") == 0 || strcmp(line, "quit") == 0) {
                printf("Bzzzz! Au revoir! 🐝\n");
                break;
            }
            
            if (interpret_line(line) == -1) break;
            printf("bzz> ");
        }
    }
    
    return 0;
}
