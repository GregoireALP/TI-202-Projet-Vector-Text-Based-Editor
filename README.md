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
exit : quitter le programme
help : afficher les commandes
resize widht height : redimensionner l'aire en largeur longueur
char c : choisir le caractère avec lequel on souhaite dessiner

point px py : dessiner un point aux coordonnées (px, py)
line x1 y1 x2 x2 : dessiner une ligne des coordonnées (x1, y1) à (x2, y2)
square x1 y1 l : dessiner un carré (x1, y1) taille
rectangle x1 y1 w h : dessiner un rectangle (x1, y1) largeur longueur
circle x y r : dessiner un cercle de cene (x, y) rayon r
polygon x1 y1 x2 y2 ... : dessiner un polygon avec x1 y1 x2 y2 pour chaque segment du polygon




## Exemple

Je lance le programme : 

Je souhaite redimensionner l'aire en 40 par 30, j'écris dans le terminal :
resize 40 30

Ensuite je souhaite que lorsque je dessine, mon dessin est fait à base de caractère '$', j'écris dans le terminal :
char $

Je souhaite ajouter un cercle de rayon 5 qui a pour centre le point de coordonnées x=20 et y=15, j'écris :
circle 20 15 5

Maintenant je souhaite effacer la grille mais je ne me souviens plus de la commande, j'écris :
help

Pour effacer la grille je sais donc que c'est :
clear

Enfin pour quitter le programme j'ecris :
exit








