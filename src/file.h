#ifndef __FILE_H__
#define __FILE_H__
#include <stdbool.h> 
#include "data.h"
#include "a_etoile.h"


typedef struct voiture voiture;

struct voiture{
    station* depart;
    station* arrivee;
    station* next_station;
    struct list_t * chemin;
    int autonomie;
    int capacite_batterie;
    int step_for_station;
    int step_for_file;
    bool is_on_file;
    int time_to_charge;
    int numero_usager; 
};





typedef struct element_file{
    struct element_file* prece;
    struct element_file* next;
    voiture* voiture;
    int rang;
} element_file;

typedef struct file file;
struct file{
    element_file* first;
    element_file* last;
    int nb_voiture;
    int puissance;
};





voiture* crea_voiture();
voiture* crea_voiture_param(struct nodes* noeud,station *depart, station *arrivee, int autonomie,int capacite, int numero);

file* crea_file();

void add_element_file(file* file_attente,voiture* vehicule);

void remove_element_file(file* file_attente,element_file* element);

bool is_empty(file* attente);

void free_file(file* file_attente);

voiture* first_file(file* attente);

int taille(file* attente);

// void supprime_first(file* attente);

// void free_file(file* attente);

void free_voiture(voiture *voiture);

#endif
