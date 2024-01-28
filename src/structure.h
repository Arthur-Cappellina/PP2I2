#ifndef __STRUCTURE_H__
#define __STRUCTURE_H__
#include "data.h"
#include <stdbool.h>

// Pour faire une sorte de dictionnaire, 
// le plus pratique est de faire une table de hachage dynamique ie pas le problème de recherche dans les listes chainées.
// On a directement accès à l'élément grâce à la clé.
// La clé est le nom de la station.
// J'ai utilisé la méthode du double hachage pour rendre cela possible.
// ie je calcule un index de base. Si la place est déjà prise, tant que j'ai pas trouvé une place dispo dans la table, je calcule un nouvel indice avec une formule qui utilise 2 fonctions de hachages


typedef struct couple
{
    station* station_s;//clé
    int poids;//valeur stockée
}couple;

typedef struct couple_came_f{
    station* suivant;
    station* prece;
}came_from;

typedef struct table_h{
    int size;
    couple** table;
    int count;
} table_h;

typedef struct table_came_h{
    came_from** table;
    int size;
}table_ch;

/// FONCTION A UTILISER POUR COST_SO_FAR et FRONTIER

//fonction création et destruction table de hachage

table_h* crea_table(int size);

bool destroy_table(table_h* table_hash);

//fonction d'insertion,trouver le poids associé

void insert(table_h* table_hash,station* station_s,int poids);

int find(table_h* table_hash,station* station_s);

//fonction d'affichage du dico

void print_table(table_h* table_hash);

/// FONCTION A UTILISER POUR CAME_FROM

table_ch* crea_came_f(int size);//même taille que pour la table avant ie 18000

bool destroy_table_ch(table_ch* table);

void insert_came(table_ch* table_hash,station* next,station* prece);

station* find_ch(table_ch* table,station* suivant);

//void print_chemin(table_ch* table);

#endif
