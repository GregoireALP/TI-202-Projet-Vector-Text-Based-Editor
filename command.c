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

    if (strcmp(cmd->name, "help") == 0) {

        // L'utilisateur tape la commande help
        printf("- clear : effacer l’écran\n");
        printf("- exit : quitter le programme\n");
        printf("- point x y : ajouter un point\n");
        printf("- line x1 y1 x2 y2 : ajouter un segment reliant deux points (x1, y1) et (x2, y2)\n");
        printf("- circle x y radius : ajouter un cercle de centre (x, y) et de rayon radius\n");
        printf("- square x y length : ajouter un carré dont le coin supérieur gauche est (x, y) et de côté length.\n");
        printf("- rectangle x y width height : ajouter un rectangle dont le coin supérieur gauche est (x, y), de largeur width et de longueur height\n");
        printf("- polygon x1 y1 x2 y2 x3 y3 ... ... : ajouter un polygone avec la liste des points donnés\n");
        printf("- plot : rafraîchir l’écran pour afficher toutes les formes géométriques de l’image (en fonction des règles d’affichage\n");
        printf("- list : afficher la liste de l’ensemble des formes géométriques qui composent l’image ainsi que toutes leurs informations\n");
        printf("- delete id : supprimer une forme à partir de son identifiant id.\n");
        printf("- erase : supprimer toutes les formes d’une image.\n");
        printf("- help : afficher la liste des commandes ainsi qu’un mini mode d’emploi permettant à l’utilisateur d’utiliser les commandes correctement\n");

    } else if(strcmp(cmd->name, "point") == 0) {

        int x = cmd->int_params[0];
        int y = cmd->int_params[1];

        Shape *point = create_point_shape(x, y);
        add_shape_to_area(area, point);

    } else if(strcmp(cmd->name, "plot") == 0) {
        printf("ici");
        draw_area(area);
        print_area(area);
    }

    return 0;
}