//
// Created by marin on 07/11/2025.
//

#include "tarjan.h"
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "math.h"

// ##########################       Etape 1       ###############################


t_classe *initClasse(const char *nom) {
    t_classe *c = malloc(sizeof(t_classe));
    strncpy(c->nom, nom, sizeof(c->nom) - 1);
    c->nom[sizeof(c->nom) - 1] = '\0';
    c->capacite = 8;
    c->sommets = malloc(c->capacite * sizeof(t_tarjan_vertex));
    c->taille = 0;
    return c;
}

void ajouterSommetClasse(t_classe *c, t_tarjan_vertex s) {
    if (c->taille >= c->capacite) {
        c->capacite *= 2;
        c->sommets = realloc(c->sommets, c->capacite * sizeof(t_tarjan_vertex));
    }
    c->sommets[c->taille++] = s;
}

t_partition *initPartition(int taille) {
    t_partition *p = malloc(sizeof(t_partition));
    p->capacite = 8;
    p->classes = malloc(p->capacite * sizeof(t_classe*));
    p->taille = 0;
    return p;
}

void addClasse(t_partition *p, t_classe *c) {
    if (p->taille >= p->capacite) {
        p->capacite *= 2;
        p->classes = realloc(p->classes, p->capacite * sizeof(t_classe*));
    }
    p->classes[p->taille++] = c;
}

// ##########################       Etape 2       ###############################

t_tarjan_vertex* initTarjanVertices(liste_adjacence L) {
    t_tarjan_vertex *tab = malloc(L.taille * sizeof(t_tarjan_vertex));
    for (int i = 0; i < L.taille; i++) {
        tab[i].id = i + 1;
        tab[i].num = -1;
        tab[i].acces = -1;
        tab[i].in_stack = 0;
    }
    return tab;
}

// ##########################       Etape 3       ###############################

Stack* createStack() {
    Stack *stack = malloc(sizeof(Stack));
    stack -> top = -1;
    stack->capacite = 8;
    stack->data = malloc(stack->capacite * sizeof(int));
    return stack;
}


void push(Stack *p, int valeur) {
    if (p->top + 1 >= p->capacite) {
        p->capacite *= 2;
        p->data = realloc(p->data, p->capacite * sizeof(int));
    }
    p->data[++p->top] = valeur;
}
int pop(Stack *p) {
    if (p->top == -1) return -1; // pile vide
    return p->data[p->top--];
}


void parcours(int v, liste_adjacence L, t_tarjan_vertex *S, Stack *p, int *index, t_partition *part) {
    // Initialisation du sommet v
    S[v].num = *index;
    S[v].acces = *index;
    (*index)++;
    push(p, v); // on met le sommet dans la pile
    S[v].in_stack = 1;

    // 2. Parcours des successeurs
    t_cell *adj = L.tab[v].head;
    while (adj != NULL) { // on parcours les sommet accessible par v
        int w = adj->sommet_arrivee - 1; // -1 car les indices commencent à 0

        if (S[w].num == -1) {// Si w n’a pas encore été visité, appel récursif sur w
            parcours(w, L, S, p, index, part);
            if (S[w].acces < S[v].acces) S[v].acces = S[w].acces; // si w a plus de lien que v
        }
        else if (S[w].in_stack) { // si le sommet est deja dans la pile, c'est un lien arrière
            if(S[w].num < S[v].acces) S[v].acces = S[w].num; // veut dire que v peut remonter jusqu'à plus ancien
        }
        adj = adj->next;
    }

    // Si v est une racine
    if (S[v].acces == S[v].num) {
        char nomClasse[10];
        sprintf(nomClasse, "C%d", part->taille + 1);
        t_classe *c = initClasse(nomClasse);
        int w;
        do {
            w = pop(p);
            S[w].in_stack = 0;
            ajouterSommetClasse(c, S[w]);
        } while (w != v);
        addClasse(part, c); // on ajoute la classe à la partition
    }
}


t_partition *tarjan(liste_adjacence L) {
    t_partition *part = initPartition(L.taille); // partition vide
    t_tarjan_vertex *S = initTarjanVertices(L); // initialisation des sommets
    Stack *p = createStack(); // pile vide
    int index = 0;
    for (int i = 0; i < L.taille; i++) {
        if (S[i].num == -1) {
            parcours(i, L, S, p, &index, part);
        }
    }
    if (p != NULL) {
        free(p->data);
        free(p);
    }

    free(S);
    return part;
}

void displaypartition(liste_adjacence L) {
    t_partition *part = tarjan(L);
    for (int i = 0; i < part->taille; i++) {
        printf("Composante C%d: {", i + 1);
        t_classe *c = part->classes[i];
        for (int j = 0; j < c->taille; j++) {
            printf("%d", c->sommets[j].id);
            if (j < c->taille - 1) printf(",");
        }
        printf("}\n");
    }
    for (int i = 0; i < part->taille; i++) {
        free(part->classes[i]->sommets);
        free(part->classes[i]);
    }
    free(part->classes);
    free(part);

}



