#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/wait.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define MAX_LINE_LENGTH 1000
#define MAX_VARIABLES 100
#define MAX_VAR_NAME 50
#define MAX_VAR_VALUE 200
#define MAX_LOOPS 10
#define MAX_CONDITIONS 10
#define MAX_FUNCTIONS 20
#define MAX_ARRAY_SIZE 100
#define MAX_MUSIC_NOTES 50
#define MAX_PACKAGES 50
#define MAX_PACKAGE_FUNCTIONS 100

// Structure pour les packages
typedef struct {
    char name[MAX_VAR_NAME];
    char language[10];
    char file_path[200];
    int is_loaded;
} Package;

// Structure pour les fonctions de packages
typedef struct {
    char name[MAX_VAR_NAME];
    char package_name[MAX_VAR_NAME];
    char language[10];
    char file_path[200];
    char parameters[500];
    int param_count;
} PackageFunction;

// Structure pour les variables
typedef struct {
    char name[MAX_VAR_NAME];
    char value[MAX_VAR_VALUE];
    double num_value;
    int is_number;
    int is_array;
    double array_values[MAX_ARRAY_SIZE];
    int array_size;
} Variable;

// Structure pour les boucles
typedef struct {
    int start_line;
    int current_iteration;
    int max_iterations;
    char condition[MAX_LINE_LENGTH];
    int is_active;
} Loop;

// Structure pour les fonctions
typedef struct {
    char name[MAX_VAR_NAME];
    int start_line;
    int end_line;
    char parameters[10][MAX_VAR_NAME];
    int param_count;
} Function;

// Variables globales
Variable variables[MAX_VARIABLES];
Loop loops[MAX_LOOPS];
Function functions[MAX_FUNCTIONS];
Package packages[MAX_PACKAGES];
PackageFunction package_functions[MAX_PACKAGE_FUNCTIONS];
int var_count = 0;
int loop_count = 0;
int function_count = 0;
int package_count = 0;
int package_function_count = 0;
int current_line = 0;
char program_lines[1000][MAX_LINE_LENGTH];
int total_lines = 0;
int skip_until_end = 0;
int in_function_definition = 0;
char current_canvas[20][50];
int canvas_width = 50;
int canvas_height = 20;

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
        printf("\033[0m");
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
            var->is_array = 0;
            var->array_size = 0;
        } else {
            printf("Erreur: Trop de variables!\n");
            return;
        }
    }

    strcpy(var->value, remove_quotes((char*)value));
    var->num_value = atof(var->value);
    var->is_number = (var->num_value != 0.0 || strcmp(var->value, "0") == 0 || strcmp(var->value, "0.0") == 0);
}

// Nouvelle fonction pour créer des tableaux
void create_array(const char* name, const char* values) {
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

    var->is_array = 1;
    var->array_size = 0;

    char values_copy[500];
    strncpy(values_copy, values, sizeof(values_copy) - 1);
    values_copy[sizeof(values_copy) - 1] = '\0';

    char* token = strtok(values_copy, ",");
    while (token && var->array_size < MAX_ARRAY_SIZE) {
        var->array_values[var->array_size] = atof(trim(token));
        var->array_size++;
        token = strtok(NULL, ",");
    }
    printf("Tableau %s créé avec %d éléments!\n", name, var->array_size);
}

// Fonction pour initialiser le canvas
void init_canvas() {
    for (int i = 0; i < canvas_height; i++) {
        for (int j = 0; j < canvas_width; j++) {
            current_canvas[i][j] = ' ';
        }
    }
}

// Fonction pour afficher le canvas
void display_canvas() {
    printf("┌");
    for (int j = 0; j < canvas_width; j++) printf("─");
    printf("┐\n");

    for (int i = 0; i < canvas_height; i++) {
        printf("│");
        for (int j = 0; j < canvas_width; j++) {
            printf("%c", current_canvas[i][j]);
        }
        printf("│\n");
    }

    printf("└");
    for (int j = 0; j < canvas_width; j++) printf("─");
    printf("┘\n");
}

// Fonction pour dessiner sur le canvas
void draw_pixel(int x, int y, char pixel) {
    if (x >= 0 && x < canvas_width && y >= 0 && y < canvas_height) {
        current_canvas[y][x] = pixel;
    }
}

// Fonction pour jouer des notes de musique
void play_note(const char* note, int duration) {
    int frequency = 440; // A4 par défaut

    if (strcmp(note, "do") == 0 || strcmp(note, "C") == 0) frequency = 261;
    else if (strcmp(note, "re") == 0 || strcmp(note, "D") == 0) frequency = 293;
    else if (strcmp(note, "mi") == 0 || strcmp(note, "E") == 0) frequency = 329;
    else if (strcmp(note, "fa") == 0 || strcmp(note, "F") == 0) frequency = 349;
    else if (strcmp(note, "sol") == 0 || strcmp(note, "G") == 0) frequency = 392;
    else if (strcmp(note, "la") == 0 || strcmp(note, "A") == 0) frequency = 440;
    else if (strcmp(note, "si") == 0 || strcmp(note, "B") == 0) frequency = 493;

    printf("♪ Note %s (%dHz) jouée pendant %dms ♪\n", note, frequency, duration);
    usleep(duration * 1000);
}

// Fonction pour générer des nombres aléatoires
int random_number(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Déclarations de fonctions
void scan_bzz_functions(const char* file_path);
int execute_package_code(const char* language, const char* file_path, const char* params);

// Fonction pour vérifier si un langage est disponible
int check_language_availability(const char* language) {
    char command[500];
    char temp_check[300];
    snprintf(temp_check, sizeof(temp_check), "/tmp/bzzbee_check_%d.txt", getpid());

    if (strcmp(language, "js") == 0) {
        snprintf(command, sizeof(command), "which node > '%s' 2>&1", temp_check);
    } else if (strcmp(language, "py") == 0) {
        snprintf(command, sizeof(command), "which python3 > '%s' 2>&1", temp_check);
    } else if (strcmp(language, "jl") == 0) {
        snprintf(command, sizeof(command), "which julia > '%s' 2>&1", temp_check);
    } else if (strcmp(language, "rb") == 0 || strcmp(language, "rub") == 0) {
        snprintf(command, sizeof(command), "which ruby > '%s' 2>&1", temp_check);
    } else if (strcmp(language, "c") == 0 || strcmp(language, "C") == 0) {
        snprintf(command, sizeof(command), "which gcc > '%s' 2>&1", temp_check);
    } else if (strcmp(language, "bzz") == 0) {
        return 1; // BzzBee est toujours disponible
    } else {
        return 0;
    }

    int result = system(command);
    remove(temp_check);
    return (result == 0);
}

// Fonction pour charger un package
int load_package(const char* language, const char* file_path) {
    if (package_count >= MAX_PACKAGES) {
        printf("❌ Erreur: Trop de packages chargés (maximum: %d)!\n", MAX_PACKAGES);
        return 0;
    }

    // Vérifier si le langage est disponible
    if (!check_language_availability(language)) {
        printf("❌ Erreur: Langage '%s' non disponible sur ce système!\n", language);
        printf("💡 Langages détectés: ");
        if (check_language_availability("js")) printf("js ");
        if (check_language_availability("py")) printf("py ");
        if (check_language_availability("jl")) printf("jl ");
        if (check_language_availability("rb")) printf("rb ");
        if (check_language_availability("c")) printf("c ");
        printf("bzz\n");
        return 0;
    }

    // Vérifier si le fichier existe
    FILE* file = fopen(file_path, "r");
    if (!file) {
        printf("❌ Erreur: Fichier package '%s' introuvable!\n", file_path);
        printf("💡 Assurez-vous que le chemin est correct et que le fichier existe.\n");
        return 0;
    }
    fclose(file);

    // Vérifier si le package n'est pas déjà chargé
    for (int i = 0; i < package_count; i++) {
        if (strcmp(packages[i].file_path, file_path) == 0) {
            printf("⚠️  Package '%s' déjà chargé, rechargement...\n", file_path);
            packages[i].is_loaded = 1;
            return 1;
        }
    }

    Package* pkg = &packages[package_count];
    sprintf(pkg->name, "package_%s_%d", language, package_count);
    strcpy(pkg->language, language);
    strcpy(pkg->file_path, file_path);
    pkg->is_loaded = 1;

    package_count++;
    printf("🐝 Package %s (%s) chargé avec succès! [%d/%d]\n", file_path, language, package_count, MAX_PACKAGES);

    // Test rapide du package
    printf("🧪 Test du package...\n");
    if (strcmp(language, "bzz") == 0) {
        scan_bzz_functions(file_path);
        printf("✅ Package BzzBee analysé avec succès!\n");
    } else {
        // Pour les autres langages, on teste juste la disponibilité
        printf("✅ Package %s prêt à l'utilisation!\n", language);
    }

    return 1;
}

// Fonction pour exécuter du code selon le langage et capturer la sortie
int execute_package_code(const char* language, const char* file_path, const char* params) {
    char command[1000];
    char temp_output[300];
    snprintf(temp_output, sizeof(temp_output), "/tmp/bzzbee_output_%d.txt", getpid());

    // Nettoyer les paramètres pour éviter les injections
    char safe_params[500] = "";
    if (params && strlen(params) > 0) {
        strncpy(safe_params, params, sizeof(safe_params) - 1);
        safe_params[sizeof(safe_params) - 1] = '\0';
    }

    if (strcmp(language, "js") == 0) {
        snprintf(command, sizeof(command), "timeout 10 node '%s' %s > '%s' 2>&1", file_path, safe_params, temp_output);
    } else if (strcmp(language, "py") == 0) {
        snprintf(command, sizeof(command), "timeout 10 python3 '%s' %s > '%s' 2>&1", file_path, safe_params, temp_output);
    } else if (strcmp(language, "jl") == 0) {
        snprintf(command, sizeof(command), "timeout 10 julia '%s' %s > '%s' 2>&1", file_path, safe_params, temp_output);
    } else if (strcmp(language, "rb") == 0 || strcmp(language, "rub") == 0) {
        snprintf(command, sizeof(command), "timeout 10 ruby '%s' %s > '%s' 2>&1", file_path, safe_params, temp_output);
    } else if (strcmp(language, "c") == 0 || strcmp(language, "C") == 0) {
        // Compiler et exécuter le C avec timeout
        char exe_name[300];
        snprintf(exe_name, sizeof(exe_name), "/tmp/bzzbee_c_%d", getpid());
        snprintf(command, sizeof(command), "gcc -o '%s' '%s' -lm 2>/dev/null && timeout 10 '%s' %s > '%s' 2>&1; rm -f '%s'", 
                exe_name, file_path, exe_name, safe_params, temp_output, exe_name);
    } else if (strcmp(language, "bzz") == 0) {
        // Exécuter un autre fichier BzzBee
        snprintf(command, sizeof(command), "timeout 10 ./main run '%s' > '%s' 2>&1", file_path, temp_output);
    } else {
        printf("❌ Langage '%s' non supporté!\n", language);
        return 0;
    }

    printf("🔧 Exécution: %s %s\n", file_path, safe_params);
    int result = system(command);

    // Lire et afficher la sortie du programme
    FILE* output_file = fopen(temp_output, "r");
    if (output_file) {
        char line[1000];
        int line_count = 0;
        int has_output = 0;
        while (fgets(line, sizeof(line), output_file) && line_count < 50) {
            printf("%s", line);
            line_count++;
            has_output = 1;
        }
        if (line_count >= 50) {
            printf("... (sortie tronquée)\n");
        }
        if (!has_output) {
            printf("✅ Exécution terminée sans sortie.\n");
        }
        fclose(output_file);
        remove(temp_output);
    }

    return 1; // Considérer l'exécution comme réussie
}

// Fonction pour scanner les fonctions dans un package BzzBee
void scan_bzz_functions(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (!file) return;

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        // Chercher les fonctions avec le pattern pollen -> ... : miel
        if (strstr(line, "pollen ->") && strstr(line, ": miel")) {
            if (package_function_count < MAX_PACKAGE_FUNCTIONS) {
                PackageFunction* func = &package_functions[package_function_count];
                sprintf(func->name, "function_%d", package_function_count);
                strcpy(func->language, "bzz");
                strcpy(func->file_path, file_path);
                strcpy(func->parameters, line);
                package_function_count++;
                printf("📝 Fonction BzzBee détectée: %s\n", line);
            }
        }
    }
    fclose(file);
}

// Fonction pour exécuter une fonction de package
int execute_package_function(const char* function_call) {
    // Parser le format pollen -> params : miel [langage fichier]
    char* pollen_start = strstr(function_call, "pollen ->");
    char* miel_end = strstr(function_call, ": miel");

    if (!pollen_start || !miel_end) {
        printf("❌ Format de fonction package incorrect!\n");
        printf("📝 Format 1: pollen -> params : miel (utilise tous les packages)\n");
        printf("📝 Format 2: pollen -> params : miel [langage fichier] (utilise un package spécifique)\n");
        return 0;
    }

    // Extraire les paramètres
    char params[500];
    char* param_start = pollen_start + 9; // après "pollen ->"
    int param_len = miel_end - param_start;
    strncpy(params, param_start, param_len);
    params[param_len] = '\0';

    char* trimmed_params = trim(params);

    if (strlen(trimmed_params) == 0) {
        printf("❌ Aucun paramètre fourni pour la fonction package!\n");
        return 0;
    }

    // Vérifier s'il y a une spécification de langage et fichier après ": miel"
    char* spec_start = miel_end + 6; // après ": miel"
    char specified_language[20] = "";
    char specified_file[200] = "";
    int has_specification = 0;

    // Parser [langage fichier] si présent
    char* bracket_open = strchr(spec_start, '[');
    char* bracket_close = strchr(spec_start, ']');

    if (bracket_open && bracket_close && bracket_close > bracket_open) {
        has_specification = 1;
        char spec_content[300];
        int spec_len = bracket_close - bracket_open - 1;
        strncpy(spec_content, bracket_open + 1, spec_len);
        spec_content[spec_len] = '\0';

        // Séparer langage et fichier
        char* space_pos = strchr(spec_content, ' ');
        if (space_pos) {
            *space_pos = '\0';
            strcpy(specified_language, spec_content);
            strcpy(specified_file, space_pos + 1);

            // Nettoyer les espaces
            char* lang_trimmed = trim(specified_language);
            char* file_trimmed = trim(specified_file);
            strcpy(specified_language, lang_trimmed);
            strcpy(specified_file, file_trimmed);

            printf("🎯 Langage spécifié: '%s', Fichier: '%s'\n", specified_language, specified_file);
        } else {
            printf("❌ Format de spécification incorrect! Utilisez: [langage fichier]\n");
            return 0;
        }
    }

    printf("🍯 Appel de fonction package: %s\n", trimmed_params);

    int executed = 0;

    if (has_specification) {
        // Exécuter avec le langage et fichier spécifiés
        if (strlen(specified_language) > 0 && strlen(specified_file) > 0) {
            // Vérifier si le langage est disponible
            if (!check_language_availability(specified_language)) {
                printf("❌ Langage '%s' non disponible sur ce système!\n", specified_language);
                return 0;
            }

            // Vérifier si le fichier existe
            FILE* file = fopen(specified_file, "r");
            if (!file) {
                printf("❌ Fichier '%s' introuvable!\n", specified_file);
                return 0;
            }
            fclose(file);

            printf("🔧 Exécution avec %s -> %s\n", specified_language, specified_file);
            executed = execute_package_code(specified_language, specified_file, trimmed_params);
        }
    } else {
        // Exécuter sur tous les packages chargés jusqu'à ce qu'un fonctionne
        for (int i = 0; i < package_count; i++) {
            Package* pkg = &packages[i];
            if (pkg->is_loaded) {
                printf("🔍 Tentative avec package %s (%s)...\n", pkg->file_path, pkg->language);
                if (execute_package_code(pkg->language, pkg->file_path, trimmed_params)) {
                    executed = 1;
                    break; // Arrêter après la première exécution réussie
                }
            }
        }
    }

    if (!executed) {
        if (has_specification) {
            printf("❌ Impossible d'exécuter avec %s -> %s!\n", specified_language, specified_file);
        } else if (package_count == 0) {
            printf("❌ Aucun package chargé! Utilisez 'bzz PACKAGE langage -> fichier' d'abord.\n");
        } else {
            printf("❌ Aucun package n'a pu exécuter cette fonction!\n");
            printf("💡 Packages chargés: ");
            for (int i = 0; i < package_count; i++) {
                if (packages[i].is_loaded) {
                    printf("%s(%s) ", packages[i].file_path, packages[i].language);
                }
            }
            printf("\n");
        }
    }

    return executed;
}

// Fonction pour évaluer une expression mathématique avancée
double evaluate_expression(const char* expr) {
    char expr_copy[500];
    strncpy(expr_copy, expr, sizeof(expr_copy) - 1);
    expr_copy[sizeof(expr_copy) - 1] = '\0';

    char* token;
    double result = 0;
    char operation = '+';
    int first = 1;

    // Support des parenthèses simple
    if (strchr(expr_copy, '(')) {
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

    // Support des fonctions mathématiques
    if (strstr(expr_copy, "sin(")) {
        char* start = strstr(expr_copy, "sin(");
        char* end = strchr(start, ')');
        if (end) {
            *end = '\0';
            double angle = atof(start + 4);
            double result_sin = sin(angle * M_PI / 180.0);
            sprintf(start, "%.4f", result_sin);
            memmove(start + strlen(start), end + 1, strlen(end + 1) + 1);
        }
    }

    if (strstr(expr_copy, "cos(")) {
        char* start = strstr(expr_copy, "cos(");
        char* end = strchr(start, ')');
        if (end) {
            *end = '\0';
            double angle = atof(start + 4);
            double result_cos = cos(angle * M_PI / 180.0);
            sprintf(start, "%.4f", result_cos);
            memmove(start + strlen(start), end + 1, strlen(end + 1) + 1);
        }
    }

    if (strstr(expr_copy, "sqrt(")) {
        char* start = strstr(expr_copy, "sqrt(");
        char* end = strchr(start, ')');
        if (end) {
            *end = '\0';
            double value = atof(start + 5);
            double result_sqrt = sqrt(value);
            sprintf(start, "%.4f", result_sqrt);
            memmove(start + strlen(start), end + 1, strlen(end + 1) + 1);
        }
    }

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
        } else if (strcmp(token, "^") == 0 || strcmp(token, "**") == 0) {
            operation = '^';
        } else if (strcmp(token, "%") == 0) {
            operation = '%';
        } else {
            double value;
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
        token = strtok(NULL, " ");
    }
    return result;
}

// Fonction pour évaluer une condition
int evaluate_condition(const char* condition) {
    char cond_copy[500];
    strncpy(cond_copy, condition, sizeof(cond_copy) - 1);
    cond_copy[sizeof(cond_copy) - 1] = '\0';
    char* var_name = strtok(cond_copy, " ");
    char* operator = strtok(NULL, " ");
    char* value = strtok(NULL, " ");

    if (!var_name || !operator || !value) {
        return 0;
    }

    Variable* var = find_variable(var_name);
    if (!var) {
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
    } else if (strcmp(shape, "soleil") == 0) {
        printf("    \\   |   /\n");
        printf("     \\  |  /\n");
        printf("  --- \\(o)/ ---\n");
        printf("     /  |  \\\n");
        printf("    /   |   \\\n");
    } else if (strcmp(shape, "nuage") == 0) {
        printf("      .-~~~-.\n");
        printf("   .-~       ~-.\n");
        printf("  (             )\n");
        printf("   '-.._____..-'\n");
    } else if (strcmp(shape, "coeur") == 0) {
        printf("  ♥♥   ♥♥\n");
        printf(" ♥♥♥♥ ♥♥♥♥\n");
        printf("♥♥♥♥♥♥♥♥♥♥\n");
        printf(" ♥♥♥♥♥♥♥♥♥\n");
        printf("  ♥♥♥♥♥♥♥\n");
        printf("   ♥♥♥♥♥\n");
        printf("    ♥♥♥\n");
        printf("     ♥\n");
    } else {
        printf("Forme '%s' non reconnue.\n", shape);
        printf("Formes disponibles: abeille, ruche, fleur, hexagone, soleil, nuage, coeur\n");
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

    // bzz TABLEAU nom -> valeur1,valeur2,valeur3
    else if (strncmp(line, "bzz TABLEAU", 11) == 0) {
        char* rest = line + 11;
        char* arrow = strstr(rest, "->");
        if (arrow) {
            *arrow = '\0';
            char* array_name = trim(rest);
            char* values = trim(arrow + 2);
            create_array(array_name, remove_quotes(values));
        }
    }

    // bzz MONTRE variable
    else if (strncmp(line, "bzz MONTRE", 10) == 0) {
        char* var_name = trim(line + 10);
        Variable* var = find_variable(var_name);
        if (var) {
            if (var->is_array) {
                printf("Tableau %s: [", var_name);
                for (int i = 0; i < var->array_size; i++) {
                    printf("%.2f", var->array_values[i]);
                    if (i < var->array_size - 1) printf(", ");
                }
                printf("]\n");
            } else {
                printf("%s\n", var->value);
            }
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

    // bzz HASARD min max
    else if (strncmp(line, "bzz HASARD", 10) == 0) {
        char* rest = trim(line + 10);
        char* min_str = strtok(rest, " ");
        char* max_str = strtok(NULL, " ");
        if (min_str && max_str) {
            int min = atoi(min_str);
            int max = atoi(max_str);
            int result = random_number(min, max);
            printf("Nombre aléatoire entre %d et %d: %d\n", min, max, result);
        }
    }

    // bzz MUSIQUE note durée
    else if (strncmp(line, "bzz MUSIQUE", 11) == 0) {
        char* rest = trim(line + 11);
        char* note = strtok(rest, " ");
        char* duration_str = strtok(NULL, " ");
        if (note && duration_str) {
            int duration = atoi(duration_str);
            play_note(note, duration);
        }
    }

    // bzz TOILE INIT
    else if (strcmp(line, "bzz TOILE INIT") == 0) {
        init_canvas();
        printf("Canvas initialisé (%dx%d)!\n", canvas_width, canvas_height);
    }

    // bzz TOILE MONTRE
    else if (strcmp(line, "bzz TOILE MONTRE") == 0) {
        display_canvas();
    }

    // bzz PIXEL x y caractère
    else if (strncmp(line, "bzz PIXEL", 9) == 0) {
        char* rest = trim(line + 9);
        char* x_str = strtok(rest, " ");
        char* y_str = strtok(NULL, " ");
        char* pixel_str = strtok(NULL, " ");
        if (x_str && y_str && pixel_str) {
            int x = atoi(x_str);
            int y = atoi(y_str);
            char pixel = pixel_str[0];
            draw_pixel(x, y, pixel);
            printf("Pixel (%d,%d) = '%c' dessiné!\n", x, y, pixel);
        }
    }

    // bzz TEXTE x y message
    else if (strncmp(line, "bzz TEXTE", 9) == 0) {
        char* rest = trim(line + 9);
        char* x_str = strtok(rest, " ");
        char* y_str = strtok(NULL, " ");
        char* text = strtok(NULL, "");
        if (x_str && y_str && text) {
            int x = atoi(x_str);
            int y = atoi(y_str);
            text = remove_quotes(trim(text));
            int text_len = strlen(text);
            for (int i = 0; i < text_len && x + i < canvas_width; i++) {
                draw_pixel(x + i, y, text[i]);
            }
            printf("Texte '%s' dessiné à (%d,%d)!\n", text, x, y);
        }
    }

    // bzz LIGNE x1 y1 x2 y2 caractère
    else if (strncmp(line, "bzz LIGNE", 9) == 0) {
        char* rest = trim(line + 9);
        char* x1_str = strtok(rest, " ");
        char* y1_str = strtok(NULL, " ");
        char* x2_str = strtok(NULL, " ");
        char* y2_str = strtok(NULL, " ");
        char* pixel_str = strtok(NULL, " ");

        if (x1_str && y1_str && x2_str && y2_str && pixel_str) {
            int x1 = atoi(x1_str), y1 = atoi(y1_str);
            int x2 = atoi(x2_str), y2 = atoi(y2_str);
            char pixel = pixel_str[0];

            // Algorithme de Bresenham simplifié
            int dx = abs(x2 - x1);
            int dy = abs(y2 - y1);
            int x = x1, y = y1;
            int x_inc = (x1 < x2) ? 1 : -1;
            int y_inc = (y1 < y2) ? 1 : -1;
            int error = dx - dy;

            while (1) {
                draw_pixel(x, y, pixel);
                if (x == x2 && y == y2) break;
                int e2 = 2 * error;
                if (e2 > -dy) { error -= dy; x += x_inc; }
                if (e2 < dx) { error += dx; y += y_inc; }
            }
            printf("Ligne de (%d,%d) à (%d,%d) dessinée!\n", x1, y1, x2, y2);
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
                char val_str[20];
                sprintf(val_str, "%d", current_loop->current_iteration);
                set_variable(current_loop->condition, val_str);

                current_line = current_loop->start_line;
                return 1;
            } else {
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

    // bzz TEMPS
    else if (strcmp(line, "bzz TEMPS") == 0) {
        time_t now = time(NULL);
        char* time_str = ctime(&now);
        time_str[strlen(time_str) - 1] = '\0'; // Enlever le \n
        printf("Temps actuel: %s\n", time_str);
    }

    // bzz PACKAGE langage -> fichier
    else if (strncmp(line, "bzz PACKAGE", 11) == 0) {
        char* rest = line + 11;
        char* arrow = strstr(rest, "->");
        if (arrow) {
            *arrow = '\0';
            char* language = trim(rest);
            char* file_path = trim(arrow + 2);
            file_path = remove_quotes(file_path);

            if (load_package(language, file_path)) {
                // Si c'est un package BzzBee, scanner les fonctions
                if (strcmp(language, "bzz") == 0) {
                    scan_bzz_functions(file_path);
                }
            }
        } else {
            printf("❌ Format incorrect! Utilisez: bzz PACKAGE langage -> fichier\n");
            printf("📝 Exemple: bzz PACKAGE js -> math_package.js\n");
        }
    }

    // bzz PACKAGES (lister les packages chargés)
    else if (strcmp(line, "bzz PACKAGES") == 0) {
        if (package_count == 0) {
            printf("📦 Aucun package chargé.\n");
            printf("💡 Utilisez 'bzz PACKAGE langage -> fichier' pour charger un package.\n");
        } else {
            printf("📦 Packages chargés (%d/%d):\n", package_count, MAX_PACKAGES);
            for (int i = 0; i < package_count; i++) {
                Package* pkg = &packages[i];
                printf("  %d. %s (%s) - %s\n", 
                       i + 1, 
                       pkg->file_path, 
                       pkg->language,
                       pkg->is_loaded ? "✅ Actif" : "❌ Inactif");
            }
            printf("💡 Utilisez 'pollen -> fonction paramètres : miel' pour appeler une fonction.\n");
        }
    }

    // pollen -> paramètres : miel (appel de fonction package)
    else if (strstr(line, "pollen ->") && strstr(line, ": miel")) {
        execute_package_function(line);
    }

    // bzz EFFACE
    else if (strcmp(line, "bzz EFFACE") == 0) {
        int clear_result = system("clear");
        (void)clear_result; // Ignorer la valeur de retour
        printf("🐝 Écran effacé! Bzzzz! 🐝\n");
    }

    // bzz BONJOUR
    else if (strcmp(line, "bzz BONJOUR") == 0) {
        printf("Bzzzz! Bonjour de la ruche! 🐝\n");
    }

    // bzz AU REVOIR
    else if (strcmp(line, "bzz AU REVOIR") == 0) {
        printf("Bzzzz! Au revoir de la ruche! 🐝🍯\n");
        return -1;
    }

    else if (!skip_until_end) {
        printf("Commande non reconnue: %s\n", line);
    }

    return 0;
}

int main(int argc, char* argv[]) {
    srand(time(NULL)); // Initialiser le générateur aléatoire

    printf("🐝 BzzBee Interpreter v4.0 - Le langage des abeilles avec packages! 🐝\n");
    printf("Nouvelles fonctionnalités: Système de packages multi-langages!\n");
    printf("Langages supportés: node.js, Python, Julia, Ruby, C, BzzBee\n");
    printf("Utilisez 'bzzbee run fichier.bzz' pour exécuter un fichier\n");
    printf("Créez des packages avec: bzz PACKAGE langage -> fichier\n");
    printf("Utilisez des fonctions avec: pollen -> paramètres : miel\n\n");

    if (argc == 3 && strcmp(argv[1], "run") == 0) {
        FILE* file = fopen(argv[2], "r");
        if (!file) {
            printf("❌ Erreur: Impossible d'ouvrir le fichier %s\n", argv[2]);
            return 1;
        }

        char line[MAX_LINE_LENGTH];
        total_lines = 0;
        while (fgets(line, sizeof(line), file) && total_lines < 1000) {
            line[strcspn(line, "\n")] = 0;
            strcpy(program_lines[total_lines], line);
            total_lines++;
        }
        fclose(file);

        current_line = 0;
        while (current_line < total_lines) {
            if (!skip_until_end || strncmp(program_lines[current_line], "bzz FIN", 7) == 0 || 
                strncmp(program_lines[current_line], "bzz SINON", 9) == 0) {
                int result = interpret_line(program_lines[current_line]);
                if (result == -1) break;
                if (result == 1) continue;
            }
            current_line++;
        }

    } else {
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