//
// Created by grego on 22/05/2023.
//
#include "command.h"
#include "area.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"

Command* create_command(char str[50]) {
    Command* cmd = malloc(sizeof(Command));

    // Initialisation des champs de la commande
    cmd->int_size = 0;
    cmd->str_size = 0;

    // Extraction des mots et affectation aux attributs correspondants
    char* token = strtok(str, " ");

    // Premier mot correspond au nom de la commande
    if (token != NULL) {
        strncpy(cmd->name, token, sizeof(cmd->name) - 1);
        cmd->name[sizeof(cmd->name) - 1] = '\0';  // Assurer la terminaison de la chaîne
        token = strtok(NULL, " ");  // Passer au mot suivant
    }

    int int_index = 0;
    int str_index = 0;

    while (token != NULL) {
        if (isdigit(token[0])) {
            // Conversion de la chaîne en entier et affectation à int_params
            int value = atoi(token);
            if (int_index < 10) {
                cmd->int_params[int_index++] = value;
                cmd->int_size++;
            }
        } else {
            // Allocation dynamique de la mémoire pour la chaîne et affectation à str_params
            char* str_param = strdup(token);
            if (str_param != NULL) {
                if (str_index < 10) {
                    cmd->str_params[str_index++] = str_param;
                    cmd->str_size++;
                } else {
                    free(str_param);  // Libérer la mémoire en cas de dépassement de la limite
                }
            }
        }

        token = strtok(NULL, " ");
    }

    // Eneleve le retour a la ligne a la fin de cmd->name
    cmd->name[strcspn(cmd->name, "\n")] = 0;

    return cmd;
}

void free_command(Command* cmd) {
    // Libérer la commande elle-même
    free(cmd);
}

int read_exec_command(Command* cmd, int *state, Area* area) {

    char drawPattern = '#';
    char* pDrawPattern = &drawPattern;

    if (strcmp(cmd->name, "help") == 0) {

        // L'utilisateur tape la commande help
        printf("- clear : effacer l'ecran\n");
        printf("- exit : quitter le programme\n");
        printf("- char c : change le caractere d'affichage\n");
        printf("- point x y : ajouter un point\n");
        printf("- resize width height : redimenssione la zone de dessin \n");
        printf("- line x1 y1 x2 y2 : ajouter un segment reliant deux points (x1, y1) et (x2, y2)\n");
        printf("- circle x y radius : ajouter un cercle de centre (x, y) et de rayon radius\n");
        printf("- square x y length : ajouter un carre dont le coin superieur gauche est (x, y) et de coteh length.\n");
        printf("- rectangle x y width height : ajouter un rectangle dont le coin superieur gauche est (x, y), de largeur width et de longueur height\n");
        printf("- polygon x1 y1 x2 y2 x3 y3 ... ... : ajouter un polygone avec la liste des points donnes\n");
        printf("- plot : rafraichir l'ecran pour afficher toutes les formes geometriques de l'image (en fonction des regles d'affichage\n");
        printf("- list : afficher la liste de l'ensemble des formes geometriques qui composent l'image ainsi que toutes leurs informations\n");
        printf("- delete id : supprimer une forme a partir de son identifiant id.\n");
        printf("- erase : supprimer toutes les formes d’une image.\n");
        printf("- help : afficher la liste des commandes ainsi qu'un mini mode d'emploi permettant a l'utilisateur d'utiliser les commandes correctement\n");

    } else if(strcmp(cmd->name, "plot") == 0) {

        draw_area(area);
        print_area(area, *pDrawPattern);

    } else if(strcmp(cmd->name, "erase") == 0) {

        erase_area(area);

    } else if(strcmp(cmd->name, "char") == 0) {

        char elem = cmd->str_params[0][0];
        *pDrawPattern = elem;

    } else if(strcmp(cmd->name, "delete") == 0) {

        int id = cmd->int_params[0];
        area->nb_shape--;

        for (int i = 0; i < area->nb_shape; ++i) {
            if (area->shape[i]->id == id) {
                delete_shape(area->shape[i]);
                // Décalage des éléments suivants vers la gauche
                for (int j = i; j < area->nb_shape; ++j) {
                    area->shape[j] = area->shape[j + 1];
                }
                break;
            }
        }

    } else if(strcmp(cmd->name, "exit") == 0) {

        *state = 0;

    } else if(strcmp(cmd->name, "resize") == 0) {

        int width, height;
        width = cmd->int_params[0];
        height = cmd->int_params[0];

        Shape** tmp = area->shape;
        int tmpSize = area->nb_shape;

        *area = *create_area(width, height);

        for(int i = 0; i < tmpSize; i++) {
            add_shape_to_area(area, tmp[i]);
        }

    } else if(strcmp(cmd->name, "list") == 0) {

        for(int i = 0; i < area->nb_shape; i++) {
            printf("(ID=%d)", area->shape[i]->id);
            print_shape(area->shape[i]);
            printf("\n");
        }

    } else if(strcmp(cmd->name, "point") == 0) {

            int x = cmd->int_params[0];
            int y = cmd->int_params[1];

            Shape *point = create_point_shape(x, y);
            add_shape_to_area(area, point);

    } else if(strcmp(cmd->name, "line") == 0) {

        int x1, x2, y1, y2;
        x1 = cmd->int_params[0];
        y1 = cmd->int_params[1];
        x2 = cmd->int_params[2];
        y2 = cmd->int_params[3];

        Shape *line= create_line_shape(x1, y1, x2, y2);
        add_shape_to_area(area, line);

    } else if(strcmp(cmd->name, "circle") == 0) {

        int x, y, rad;
        x = cmd->int_params[0];
        y = cmd->int_params[1];
        rad = cmd->int_params[2];

        Shape* circle = create_circle_shape(x, y, rad);
        add_shape_to_area(area, circle);

    } else if(strcmp(cmd->name, "square") == 0) {

        int x, y, l;
        x = cmd->int_params[0];
        y = cmd->int_params[1];
        l = cmd->int_params[2];

        Shape* square = create_square_shape(x, y, l);
        add_shape_to_area(area, square);

    } else if(strcmp(cmd->name, "rectangle") == 0) {

        int x, y, w, h;
        x = cmd->int_params[0];
        y = cmd->int_params[1];
        w = cmd->int_params[2];
        h = cmd->int_params[3];

        Shape* rectangke = create_rectangle_shape(x, y, w, h);
        add_shape_to_area(area, rectangke);

    } else {
        printf("Desoler mais cette commande est inconnue, tapez help pour plus d'informations\n");
    }
    return 0;
}