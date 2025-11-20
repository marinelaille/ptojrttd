//
// Created by marin on 06/11/2025.
//

#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

// ##########################       Etape 1       ###############################

// fonction pour créer une « cellule » :

t_cell *createCell(int sommet, float proba) {
    t_cell *new = (t_cell *)malloc(sizeof(t_cell));
    if (!new) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    new->sommet_arrivee = sommet;
    new->proba = proba;
    new->next = NULL;
    return new;
}

// fonction pour créer une « liste » vide :

t_list createList() {
    t_list L;
    L.head = NULL;
    return L;
}

//  fonction pour ajouter une cellule à une liste :

void AddCell(t_list *L, int sommet_arrivee, float proba) {
    t_cell *cell = createCell(sommet_arrivee, proba);
    if (L->head == NULL) {
        L->head = cell;
        return;
    }
    t_cell *p = L->head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = cell;
}

//  fonction pour afficher une liste :

void displayList(t_list l) {
    t_cell *temp = l.head;
    while (temp != NULL) {
        printf("-> (%d, %.2f) ", temp->sommet_arrivee, temp->proba);
        temp = temp->next;
    }
    printf("\n");
}

// fonction pour créer une liste d’adjacence ‘vide’ à partir d'une taille de donnnée :

liste_adjacence createListeAdj(int taille) {
    liste_adjacence L;
    L.taille = taille;
    L.tab = (t_list *)malloc(taille * sizeof(t_list));
    for (int i = 0; i < taille; i++) {
        L.tab[i] = createList();
    }
    return L;
}

// fonction pour aAicher une liste d’adjacence :

void displayListeAdj(liste_adjacence L) {
    for (int i = 0; i < L.taille; i++) {
        printf("Sommet %d : ", i + 1);
        displayList(L.tab[i]);
    }
}

// fonction pour créer un graphe :

liste_adjacence readGraph(const char *filename) {
    FILE *file = fopen(filename, "rt");

    int nbvert, depart, arrivee;
    float proba;

    if (file == NULL) {
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &nbvert); // lis la première ligne (le nombre de sommet)

    liste_adjacence L_adj = createListeAdj(nbvert); // initialisation d'une liste d'adjacence
    while (fscanf(file, "%d %d %f", &depart, &arrivee, &proba) == 3) {
        AddCell(&L_adj.tab[depart - 1], arrivee, proba); // ajout dans la liste d'adjacence le sommet
    }

    fclose(file);
    return L_adj;
}

// ##########################       Etape 2       ###############################

void Markov(liste_adjacence L) {
    int isMarkov = 1;
    for (int i = 0; i < L.taille; i++) { // parcours des sommets du graphe
        float somme = 0.0;
        t_cell *curr = L.tab[i].head;

        while (curr != NULL) {
            float p = curr->proba;
            if (p <= 0.0 || p > 1.0) { // condition : chaque arête a une proba strictement positive et égale ou inférieur à 1
                printf("Sommet %d : probabilite invalide %.2f\n", i + 1, p);
                isMarkov = 0;
            }
            somme += p;
            curr = curr->next; // parcours de la liste d'arête du sommet
        }
        if (fabs(somme - 1.0) > 0.01) { // la somme des probas = 1
            printf("Le graphe n est pas un graphe de Markov : la somme des probabilites du sommet %d est %.2f\n", i + 1, somme);
            isMarkov = 0;
        }
    }

    if (isMarkov) {
        printf("Le graphe est un graphe de Markov\n");
    }
}

// ##########################       Etape 3       ###############################

void exporterGrapheMarkov(FILE *f, liste_adjacence L) {
    fprintf(f, "---\nconfig:\n    layout: elk\n    theme: neo\n    look: neo\n---\nflowchart LR\n");

    for (int i = 0; i < L.taille; i++) { // écris tous les sommets dans le fichier, on associe leur nombre à une lettre
        fprintf(f, "%s((%d))\n", getID(i + 1), i + 1);
    }

    for (int i = 0; i < L.taille; i++) { // parcours du graphe
        t_cell *curr = L.tab[i].head;
        while (curr != NULL) { // parcours des sommets du graphe
            fprintf(f, "%s -->|%.2f|",
                    getID(i+1),
                    curr->proba);
            fprintf(f, "%s\n", getID(curr->sommet_arrivee));
            curr = curr->next;
        }
    }
}