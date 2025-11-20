//
// Created by marin on 06/11/2025.
//

#ifndef UNTITLED7_STRUCTURE_H
#define UNTITLED7_STRUCTURE_H

#include <stdio.h>

typedef struct s_cell {
    int sommet_arrivee;
    float proba;
    struct s_cell *next;
} t_cell;

// Une liste représente l’ensemble des arêtes sortantes d’un sommet
typedef struct s_list{
    t_cell *head;
} t_list;

// Une liste d’adjacence : tableau de listes
typedef struct {
    int taille;
    t_list *tab;
} liste_adjacence;

t_cell *createCell(int, float);
t_list createList();
void AddCell(t_list *, int, float);
liste_adjacence createListeAdj(int);
void displayList(t_list);
void displayListeAdj(liste_adjacence);

liste_adjacence readGraph(const char *);

void Markov(liste_adjacence );

void exporterGrapheMarkov(FILE *f, liste_adjacence L);



#endif //UNTITLED7_STRUCTURE_H