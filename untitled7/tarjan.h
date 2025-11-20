//
// Created by marin on 07/11/2025.
//

#ifndef UNTITLED7_TARJAN_H
#define UNTITLED7_TARJAN_H


// ##########################       Etape 1       ###############################

typedef struct s_tarjan_vertex {
    int id;
    int num;
    int acces;
    int in_stack;
}t_tarjan_vertex;

typedef struct {
    char nom[32];
    t_tarjan_vertex *sommets; // tableau des sommets
    int taille; // nombre actuel de sommets
    int capacite;
} t_classe;

typedef struct {
    t_classe **classes; // tableau de classes
    int taille; // nombre actuel de classes
    int capacite; // taille allouée
} t_partition;

t_tarjan_vertex initTarjan(int);
t_classe *initClasse(const char *);
void ajouterSommetClasse(t_classe *, t_tarjan_vertex) ;
t_partition *initPartition(int);
void addClasse(t_partition *, t_classe *);

// ##########################       Etape 2       ###############################

typedef struct {
    int *data;
    int top;
    int capacite;
} Stack;

// ##########################       Etape 2       ###############################

Stack* createStack(void);
void push(Stack *p, int valeur);
int pop(Stack *);
t_partition *tarjan(liste_adjacence );

void parcours(int v, liste_adjacence , t_tarjan_vertex *, Stack *, int *, t_partition *);
void displaypartition(liste_adjacence );

#endif //UNTITLED7_TARJAN_H