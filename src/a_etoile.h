#ifndef __A_ETOILE_H__
#define __A_ETOILE_H__

#define CAPACITE_VOITURE 200

#include "data.h"
#include "structure.h"
#include "distance.h"
#include <stdbool.h>

typedef struct cellule_t cellule_t;
struct cellule_t{
    int id_station;
    cellule_t* suivant;
};

typedef struct list_t
{
    cellule_t* premier;
} list_t;


list_t *list_create();

bool list_destroy(list_t *list_t);

void remove_first(list_t *one_list);

void remove_last(list_t *one_list);

bool list_is_empty(list_t *list_t);

void list_append(list_t *list_t, int id);

bool list_contains(list_t* one_list, int id);

void list_print(list_t *list_t);

int last(list_t *one_list);

list_t* A_etoile_v1(struct nodes* nodes, int start, int end, int autonomy);

list_t* A_etoile(nodes* nodes, int start, int end);

#endif
