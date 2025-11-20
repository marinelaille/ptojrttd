#include <stdlib.h>
#include <stdio.h>
#include "hasse.h"
#include "tarjan.h"
#include "structure.h"


t_link_array *initLinkArray() {
    t_link_array *arr = malloc(sizeof(t_link_array));
    arr->taille = 0;
    arr->capacite = 8;
    arr->liens = malloc(arr->capacite * sizeof(t_link));
    return arr;
}

void addLink(t_link_array *arr, int depart, int arrivee) {
    // éviter les doublons
    for (int i = 0; i < arr->taille; i++) {
        if (arr->liens[i].start == depart && arr->liens[i].end == arrivee)
            return;
    }
    if (arr->taille >= arr->capacite) {
        arr->capacite *= 2;
        arr->liens = realloc(arr->liens, arr->capacite * sizeof(t_link));
    }
    arr->liens[arr->taille].start = depart;
    arr->liens[arr->taille].end = arrivee;
    arr->taille++;
}

int *creerTableSommetClasse(t_partition *part, int nbSommets) {
    int *classeDe = malloc((nbSommets + 1) * sizeof(int)); // +1 car sommets numérotés dès 1
    for (int i = 0; i < part->taille; i++) {
        t_classe *c = part->classes[i];
        for (int j = 0; j < c->taille; j++) {
            int id = c->sommets[j].id;
            classeDe[id] = i; // i = indice de la classe
        }
    }
    return classeDe;
}

t_link_array *creerLiens(liste_adjacence L, t_partition *part) {
    int *classeDe = creerTableSommetClasse(part, L.taille);
    t_link_array *links = initLinkArray();

    for (int i = 0; i < L.taille; i++) {
        int Ci = classeDe[i + 1]; // sommets numérotés dès 1
        t_cell *curr = L.tab[i].head;
        while (curr != NULL) {
            int Cj = classeDe[curr->sommet_arrivee];
            if (Ci != Cj) {
                addLink(links, Ci, Cj);
            }
            curr = curr->next;
        }
    }
    free(classeDe);
    return links;
}

void exporterDiagrammeHasse(FILE *f, t_partition *part, t_link_array *links) {
    fprintf(f, "---\nconfig:\n    layout: elk\n    theme: base\n---\nflowchart TD\n");

    // Affichage des classes (nœuds)
    for (int i = 0; i < part->taille; i++) {
        fprintf(f, "C%d[%s]\n", i + 1, part->classes[i]->nom);
    }

    // Affichage des liens entre classes
    for (int i = 0; i < links->taille; i++) {
        fprintf(f, "C%d --> C%d\n", links->liens[i].start + 1, links->liens[i].end + 1);
    }
}
