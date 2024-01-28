#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "file.h"
#include "structure.h"
#include "distance.h"
#include "a_etoile.h"

voiture* crea_voiture(){
    voiture* usager = malloc(sizeof(voiture));
    usager->depart = NULL;
    usager->arrivee = NULL;
    usager->autonomie = 0;
    usager->capacite_batterie = 0;
    usager ->next_station = NULL;
    usager->is_on_file = false;
    usager->step_for_station = 0;
    usager->step_for_file = 0;
    usager->numero_usager = 0;
    return usager;
}

voiture* crea_voiture_param(struct nodes* noeud,station *depart, station *arrivee, int autonomie,int capacite, int numero){
    voiture* usager = malloc(sizeof(voiture));
    usager->depart = depart;
    usager->arrivee = arrivee;
    usager->autonomie = autonomie;
    usager->capacite_batterie = capacite;
    usager->is_on_file = false;
    usager->step_for_file = 0;
    usager->numero_usager = numero;
    usager->chemin = A_etoile_v1(noeud,depart->id,arrivee->id,autonomie);
    remove_first(usager->chemin);
    usager->next_station = usager->chemin->premier;
    double distance = distance_entre(depart->lat, depart->lon, usager->next_station->lat, usager->next_station->lon);
    usager->step_for_station = (int)(round(distance/10));
    return usager;
}

file* crea_file(){
    file* new_file = malloc(sizeof(file));
    new_file->first=NULL;
    new_file->last=NULL;
    new_file->nb_voiture=0;
    new_file->puissance=0;
    return new_file;
}

void add_element_file(file* file_attente,voiture* vehicule){
    element_file* new_element = malloc(sizeof(element_file));
    new_element->voiture=vehicule;
    new_element->prece=NULL;
    new_element->next=file_attente->first;
    if (file_attente->first!=NULL) {
        file_attente->first->prece=new_element;
        new_element->rang=file_attente->first->rang+1;
    }
    else {
        file_attente->last=new_element;
        new_element->rang=1;
    }
    file_attente->first=new_element;
    file_attente->nb_voiture++;
}

void remove_element_file(file* file_attente,element_file* element){
    if (file_attente->first==file_attente->last){
        file_attente->first=NULL;
        file_attente->last=NULL;
        file_attente->nb_voiture--;
    }
    else if (file_attente->last==element) {
        file_attente->last=file_attente->last->prece;
        file_attente->last->next=NULL;
        file_attente->nb_voiture--;
    }
    else if (file_attente->first==element) {
        file_attente->first=file_attente->first->next;
        file_attente->last->next=NULL;
        file_attente->nb_voiture--;
    }
    else {
        element_file* cursor = file_attente->first;
        while (cursor->next!=element) cursor = cursor->next;
        cursor->next=element->next;
        cursor->next->prece=element->prece;
        file_attente->nb_voiture--;
    }
    free(element);

}


bool is_empty(file* attente){
    return (attente->first == NULL);
}

void free_file(file* file_attente){
    if (is_empty(file_attente)) free(file_attente);
    else {
        remove_element_file(file_attente,file_attente->last);
        free_file(file_attente);
    }
}


 voiture* first_file(file* attente){
    return attente->first->voiture;
}

int taille(file* attente){
    return attente->nb_voiture;
}

// void add_file(file* attente, voiture* usager){
//     if(is_empty(attente)){
//         attente->voiture = usager;
//         attente->nb_voiture  = attente->nb_voiture +1;
//     }
//     else{
//         file* new_prece = malloc(sizeof(file));
//         new_prece->prece = NULL;
//         new_prece->voiture = usager;
//         new_prece ->next = attente;
//         attente->prece = new_prece;
//         attente->nb_voiture = attente->voiture+1;
//     }
// }

// void supprime_first(file* attente){
//     voiture* first = first_file(attente);
//     file* prece;
//     file* temp = attente;
//     while (temp->voiture->numero_usager != first->numero_usager)
//     {
//         prece = temp;
//         temp = temp->next;
//     }
//     prece->next = NULL;
//     attente->nb_voiture  = attente->nb_voiture-1;
//     free(temp);    
// }

// void free_file(file* attente){
//     if(attente == NULL){
//         return;
//     }
//     file* temp = attente;
//     while (temp->next != NULL)
//     {
//         temp = temp->next;
//         supprime_first(temp->prece);
//     }
//     free(temp);
// }

void free_voiture(voiture *voiture){
    if(voiture == NULL){
        return;
    }
    free_station(voiture->depart);
    free_station(voiture->arrivee);
    free_station(voiture->next_station);
    free(voiture);
}