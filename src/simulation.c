#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "data.h"
#include "a_etoile.h"
#include "structure.h"
#include "distance.h"
#include "simulation.h"

// Méthode initialisant une simulation de base avec les données dans base.csv
simulation *init_simulation_base(options *opt){
    simulation *sim = malloc(sizeof(simulation));
    sim->nbcars = 0;
    sim->capacity = 500;
    sim->voiture = malloc(sizeof(voiture) * sim->capacity);
    if (opt != NULL)
    {
        sim->stations = load_nodes_by_lat(opt->min_pdc, opt->deux_roues);
    } else {
        sim->stations = load_nodes_by_lat(-1, -1);
    }
    FILE *f = fopen("../data/base.csv","r");
    if (f == NULL){
        printf("Error opening file");
        exit(1);
    }
    size_t len = 0;
    size_t read;
    char *temp; 
    char *line = NULL;
    while ((read = getline(&line, &len, f)) != -1){
        if(line[0] == 'i'){
            continue;
        }
        if(sim->nbcars == sim->capacity){
            sim->capacity += 5000;
            sim->stations = realloc(sim->stations, sizeof(station) * sim->capacity);
        }
        //----------------------
        temp = strtok(line, ",");
        int id_dep = (int)strtol(temp, NULL, 10);

        temp = strtok(NULL, ",");
        int id_arr = (int)strtol(temp, NULL, 10);

        temp = strtok(NULL, ",");
        int puissance = (int)strtol(temp, NULL, 10);


        station* depart = find_station_by_id((int)id_dep, sim->stations);
        station* arrivee = find_station_by_id((int)id_arr, sim->stations);
        if(opt != NULL && opt->autonomie != -1){
            sim->capacity = opt->autonomie;
        }
        list_t *chemin = A_etoile_v1(sim->stations, depart->id, arrivee->id, 200);
        if(chemin != NULL){
            station *next = find_station_by_id(chemin->premier->id_station, sim->stations);
            voiture *s = crea_voiture_param(depart, arrivee, next, puissance, sim->nbcars, 1);
            printf("Voiture %d : %s -> %s, autonomie : %d\n", sim->nbcars, depart->name, arrivee->name, puissance);
            sim->voiture[sim->nbcars] = s;
            sim->nbcars++;
        } else {
            printf("Pas de chemin trouvé pour la voiture %d\n", sim->nbcars);
        }
    }
    fclose(f);
    return sim;
}

void run_next_step(nodes *stations, simulation *simulation){
    for (int i=0;i<simulation->nbcars;i++){
        evolue_voiture(simulation->voiture[i],simulation);
    }
    for (int i=0;i<stations->size;i++){
        if (stations->stations[i]->file_attente!=NULL) evolue_file(stations->stations[i]->file_attente,stations);
    }
        
}


void evolue_voiture(voiture *voiture, nodes *stations){
    if (!(voiture->is_on_file && voiture->next_station!=NULL)){ 
        voiture->step_for_station--;
        if (voiture->step_for_station==0){
            if (voiture->next_station==voiture->arrivee){
                voiture->next_station == NULL;
            }
            else if (voiture->next_station->file_attente==NULL){
                voiture->next_station->file_attente = crea_file();
                voiture->next_station->file_attente->nb_voiture = voiture->next_station->pdc;
                voiture->next_station->file_attente->puissance = voiture->next_station->puissance_nominale;
                add_element_file(voiture->next_station->file_attente,voiture);
                voiture->is_on_file=true; 
            }
            else {
                add_element_file(voiture->next_station->file_attente,voiture);
                voiture->is_on_file=true ;
            }

        }
    }
}

void voiture_out_of_file(voiture* voiture, nodes *stations){
    double a_lat = find_lat_by_id(voiture->chemin->premier,stations);
    double a_lon = find_lon_by_id(voiture->chemin->premier,stations);
    double b_lat = find_lat_by_id(voiture->chemin->premier->suivant,stations);
    double b_lon = find_lon_by_id(voiture->chemin->premier->suivant,stations);
    voiture->step_for_station = (int)(round(distance_entre(a_lat,a_lon,b_lat,b_lon)/10));
    remove_first(voiture->chemin);
    voiture->next_station=voiture->chemin->premier;
    voiture->is_on_file=false;
    
}

void evolue_file(file *file, nodes *stations){
    element_file* cursor = file->first;
    while (cursor!=NULL){
        if (cursor->rang==0){
            cursor->voiture->step_for_file--;
            if (cursor->voiture->step_for_file==0){
                element_file* element_a_remove = cursor;
                cursor = cursor->next;
                voiture_out_of_file(element_a_remove->voiture,stations);
                remove_element_file(file,element_a_remove); 
            }
            else cursor=cursor->next;
        }
        else cursor=cursor->next;
    }
    if (is_empty(file)){
        free_file(file);
        return;
    }
    cursor = file->last;
    int compteur = 1-(file->nb_voiture);
    int decalage = 0;
    while (cursor!=NULL){
        if (cursor->rang!=0){
            if (compteur<=0){
                cursor->rang=0;
                cursor->voiture->step_for_file=cursor->voiture->capacite_batterie*10/file->puissance;
                decalage++;
            }
            else {
                cursor->rang=cursor->rang-decalage;
            }
        }
        cursor=cursor->next;
        compteur++;
    }
}

void display_simulation(simulation *simulation){
    printf("Nombre de voitures : %d\n", simulation->nbcars);
    for(int i = 0; i < simulation->nbcars; i++){
        if(simulation->voiture[i] == NULL){
            continue;
        }
        printf("- Voiture %d : \n", simulation->voiture[i]->numero_usager);
        display_voiture(simulation->voiture[i]);
    }
}

void display_voiture(voiture *voiture){
    printf("    Autonomie : %d\n", voiture->autonomie);
    printf("    Depart : %s\n", voiture->depart->name);
    printf("    Arrivee : %s\n", voiture->arrivee->name);
        if (voiture->next_station != NULL) {
        printf("    Prochaine station : %s\n", voiture->next_station->name);
    }
    else {
        printf("    Prochaine station : N/A\n");
    }
    if(voiture->time_to_charge > 0){
        printf("    Etat : en charge");
    } else if(voiture->step_for_station > 0){
        printf("    Etat : encore %d étapes avant la prochaine station", voiture->step_for_station);
    } else if(voiture->is_on_file){
        printf("    Etat : en attente");
    } else if (voiture->next_station == NULL){
        printf("    Etat : arrivé");
    } else {
        printf("    Etat : en route");
    }
}

void free_simulation(simulation *simulation){
    for(int i = 0; i < simulation->nbcars; i++){
        free_voiture(simulation->voiture[i]);
    }
    free(simulation->voiture);
    free(simulation);
}