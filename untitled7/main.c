#include <stdio.h>
#include <stdlib.h>
#include"structure.h"
#include "tarjan.h"
#include"hasse.h"

int main() {
    printf("Exemple 1 :\n");
    const char *cheminFichier1 = "data/exemple1.txt";
    liste_adjacence L1 = readGraph(cheminFichier1);
    displayListeAdj(L1);
    Markov(L1);
    displaypartition( L1);
    FILE *f1 = fopen("graphe_markov1.txt", "w");
    exporterGrapheMarkov(f1, L1);
    fclose(f1);

    printf("\nExemple 2 :\n");
    const char *cheminFichier2 = "data/exemple4_2check.txt";
    liste_adjacence L2 = readGraph(cheminFichier2);
    displayListeAdj(L2);
    Markov(L2);

    printf("\nExemple 3 :\n");
    const char *cheminFichier3 = "data/exemple_valid_step3.txt";
    liste_adjacence L3 = readGraph(cheminFichier3);
    displayListeAdj(L3);
    Markov(L3);
    displaypartition( L3);
    FILE *f2 = fopen("graphe_markov2.txt", "w");
    exporterGrapheMarkov(f2, L3);
    t_partition *part = tarjan(L3);
    t_link_array *links = creerLiens(L3, part);

    FILE *f = fopen("diagramme_hasse.txt", "w");
    exporterDiagrammeHasse(f, part, links);
    fclose(f);

    fclose(f2);
    return 0;
}

/*
Sommet 1 : -> (3, 0.01) -> (2, 0.04) -> (1, 0.95)
Sommet 2 : -> (4, 0.05) -> (3, 0.05) -> (2, 0.90)
Sommet 3 : -> (4, 0.20) -> (3, 0.80)
Sommet 4 : -> (1, 1.00)
Le graphe est un graphe de Markov
Sommet 1 : -> (4, 0.46) -> (4, 0.36) -> (2, 0.18)
Sommet 2 : -> (3, 0.33) -> (3, 0.67)
Sommet 3 : -> (4, 1.00)
Sommet 4 : -> (5, 0.49) -> (1, 0.25) -> (1, 0.26)
Sommet 5 : -> (6, 1.00)
Sommet 6 : -> (7, 1.00)
Sommet 7 : -> (5, 0.59) -> (8, 0.08) -> (8, 0.33)
Sommet 8 : -> (9, 0.24) -> (7, 0.21) -> (7, 0.33) -> (5, 0.22)
Sommet 9 : -> (11, 0.43) -> (11, 0.48) -> (10, 0.10)
Sommet 10 : -> (11, 1.00)
Sommet 11 : -> (12, 0.22) -> (10, 0.36) -> (9, 0.42)
Sommet 12 : -> (14, 0.34) -> (13, 0.66)
Sommet 13 : -> (15, 0.14) -> (14, 0.86)
Sommet 14 : -> (15, 0.32) -> (13, 0.47) -> (15, 0.20)
Sommet 15 : -> (12, 0.79)
Le graphe n est pas un graphe de Markov : la somme des probabilites du sommet 15 est 0.79
*/