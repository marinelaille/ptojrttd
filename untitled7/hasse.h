#ifndef __HASSE_H__
#define __HASSE_H__

#include "structure.h"
#include "tarjan.h"
#include <stdio.h>



typedef struct s_link{
    int start; // index de la classe source (ex: 0 pour C1)
    int end; // index de la classe destination (ex: 1 pour C2)
} t_link;

typedef struct s_link_array{
    t_link *liens;
    int taille;
    int capacite;
} t_link_array;

t_link_array *initLinkArray();

void addLink(t_link_array *, int , int );
int *creerTableSommetClasse(t_partition *, int );
t_link_array *creerLiens(liste_adjacence , t_partition *);
void exporterDiagrammeHasse(FILE *, t_partition *, t_link_array *);

#endif