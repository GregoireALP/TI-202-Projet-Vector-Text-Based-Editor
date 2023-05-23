# Vector Text-based Editor

Projet "Vector Text-based Editor" , module TI-202, Groupe E

Le Vector Text-based Editor est un logiciel de dessin vectoriel en mode textuel, avec ce mode pour dessiner il faut rentrer des commandes utilisateurs

## Authors

- [@GregoireALP](https://github.com/GregoireALP) (Grégoire Alperovitch)
- [@benjilol](https://github.com/benjilol) (Benjamin Jaegle)

## Installation

Le repository du projet est disponible ici:
https://github.com/GregoireALP/TI-101-Projet-Vector-Text-Based-Editor.git

Le jeu requiere l'installation d'un compilateur C

## Utilisation 

Menu : "commande à appliquée" puis touche entrée pour effectuer la commande

Apparition de la forme sur la grille de dessin

Si besoin de la liste de commande faire "help"

Voici la liste : 

clear : effacer la grille
exit : quiiter le programme
help : afficher les commandes
plot : draw dcreen

point px py : dessiner un point aux coordonnées (px, py)
line x1 y1 x2 x2 : dessiner une ligne des coordonnées (x1, y1) à (x2, y2)
square x1 y1 l : dessiner un carré (x1, y1) taille
rectangle x1 y1 w h : dessiner un rectangle (x1, y1) largeur longueur
circle x y r : dessiner un cercle de cene (x, y) rayon r
polygon x1 y1 x2 y2 ... : dessiner un polygon
curve x1 y1 x2 y2 x3 y3 x4 y4 : dessiner la courbe de Bezier

==== Draw manager ====
        list {layers, arias, shapes}
        select {aria, layer} {id}
        delete {aria, layer, shape} {id}
        new {aria, layer}
        ==== Set ====
        set char {border, background} ascii_code
        set layer {visible, unvisible} {id}
