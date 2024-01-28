#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data.h"
#include "a_etoile.h"
#include "structure.h"
#include "distance.h"
#include "simulation.h"

typedef struct options options;

struct options{
    int batterie;
    int min_pdc;
    int deux_roues; // 0 si faux, 1 si vrai, -1 si non renseigné
    int autonomie; 
};

typedef struct rdn_data rdn_data;

struct rdn_data{
    int nb_steps;
    int nb_cars; // 0 si faux, 1 si vrai, -1 si non renseigné
};

void traitement_nom(char* nom1, char* nom2, options* opt);
void traitement_coordonnees(double lat1, double lon1, double lat2, double lon2, options* opt);
options* traitement_options();
rdn_data* traitement_random();
void simulate(simulation *simu, int nb_steps);

int main(int argc, char const *argv[])
{
    // On gère le cas où l'on lance la simulation de base 
    if(argc == 1){
        simulation *simu = init_simulation_base(NULL);
        simulate(simu, 100);
    }
    if(argc == 2){
        simulation *simu;
        if(strcmp(argv[1], "options") == 0){
            options *opt = traitement_options();
            simulation *simu = init_simulation_base(opt);
        } else {
            rdn_data *rd = traitement_random();
            simulation *simu = init_simulation_random(rd->nb_cars, rd->nb_steps);
        }
        simulate(simu, atoi(argv[1]));
    }
    if(argc == 3){
        options *opt = traitement_options();
        rdn_data *rd = traitement_random();
        simulation *simu = init_simulation_random(rd->nb_cars, rd->nb_steps, opt);
        simulate(simu, atoi(argv[2]));
    }
    return 0;
}


void simulate(simulation *simu, int nb_steps){
    display_simulation(simu);
    for(int i = 0; i < nb_steps; i++){
        run_next_step(simu->stations, simu);
        scanf("%*c");
        display_simulation(simu);
    }
    free_simulation(simu);
}

void traitement_nom(char* nom1, char* nom2, options* opt){
    // récupération de tous les noeuds
    nodes *n;
    if(opt != NULL){
        nodes *n = load_nodes_by_name(opt->min_pdc, opt->deux_roues);
    } else {
        nodes *n = load_nodes_by_name(-1, -1);
    }

    // récupération des stations correspondant aux noms passés en paramètre
    station* start = find_station_by_name(nom1, n);
    station* end = find_station_by_name(nom2, n);

    //autonomie de la voiture
    int autonomy = 500;
    if(opt != NULL && opt->autonomie != -1){
        autonomy = opt->autonomie;
    }
    if(opt != NULL && opt->batterie != -1){
        autonomy = ((100 - opt->batterie) / 100) * autonomy;
    }
    // trouver un chemin optimal entre les 2
    list_t *chemin = A_etoile_v1(n, start->id, end->id, autonomy);
    display_name_with_chemin(chemin, n);
    free_nodes(n);
    // free_station(station_depart);
    // free_station(station_arrivee);
    list_destroy(chemin);
}

void traitement_coordonnees(double lat1, double lon1, double lat2, double lon2, options* opt){
       // récupération de tous les noeuds
    nodes *n;
    if(opt != NULL){
        nodes *n = load_nodes_by_lat(opt->min_pdc, opt->deux_roues);
    } else {
        nodes *n = load_nodes_by_lat(-1, -1);
    }

    // récupération des stations correspondant aux noms passés en paramètre
    station* start = find_station_by_lat(lat1, n);
    station* end = find_station_by_lat(lat2, n);

    //autonomie de la voiture
    int autonomy = 500;
    if(opt != NULL && opt->autonomie != -1){
        autonomy = opt->autonomie;
    }
    if(opt != NULL && opt->batterie != -1){
        autonomy = ((100 - opt->batterie) / 100) * autonomy;
    }
    // trouver un chemin optimal entre les 2
    list_t *chemin = A_etoile_v1(n, start->id, end->id, autonomy);
    display_name_with_chemin(chemin, n);

    free_nodes(n);
    // free_station(station_depart);
    // free_station(station_arrivee);
    list_destroy(chemin);
}

options* traitement_options(){
    options *opt = malloc(sizeof(options));
    opt->batterie = -1;
    opt->min_pdc = -1;
    opt->deux_roues = -1;
    opt->autonomie = -1;
    bool not_finished = true;
    int i = 2;
    while (not_finished)
    {
        printf("1) Lancer le programme");
        if(opt->batterie == -1){
            printf("%d) Choisir le pourcentage minimal batterie", i);
            i += 1;
        }
        if(opt->min_pdc == -1){
            printf("%d) Choisir le nombre de points de charge disponibles", i);
            i += 1;
        }    
        if(opt->deux_roues == -1){
            printf("%d) Choisir le type de véhicule", i);
            i += 1;
        }      
        if(opt->autonomie == -1){
            printf("%d) Choisir l'autonomie du véhicule", i);
            i += 1;
        }
        printf("%d) Quitter le programme", i);
        int choix;
        scanf("%d", &choix);
        switch (choix)
        {
            case 1:
                return opt;
                break;
            case 2:
                if(opt->batterie == -1) {
                    printf("Entrez la nouvelle autonomie de la batterie : ");
                    scanf("%d", &opt->batterie);
                }
                else if(opt->min_pdc == -1) {
                    printf("Entrez le nouveau nombre de points de charge disponibles : ");
                    scanf("%d", &opt->min_pdc);
                }
                else if(opt->deux_roues == -1){
                    printf("Entrez le nouveau type de véhicule (2 pour autorisé uniquement les 2 roues, 4 pour les interdire): ");
                    int decision;
                    scanf("%d", &decision);
                    if(decision == 2){
                        opt->deux_roues = true;
                    }
                    else if(decision == 4){
                        opt->deux_roues = false;
                    }
                }
                else if(opt->autonomie == -1){
                    printf("Entrez la nouvelle autonomie du véhicule : ");
                    scanf("%d", &opt->autonomie);
                } else {
                    exit(0);
                }
                break;
            case 3:
                if(opt->min_pdc == -1) {
                    printf("Entrez le nouveau nombre de points de charge disponibles : ");
                    scanf("%d", &opt->min_pdc);
                }
                else if(opt->deux_roues == -1){
                    printf("Entrez le nouveau type de véhicule (2 pour autorisé uniquement les 2 roues, 4 pour les interdire): ");
                    int decision;
                    scanf("%d", &decision);
                    if(decision == 2){
                        opt->deux_roues = true;
                    }
                    else if(decision == 4){
                        opt->deux_roues = false;
                    }
                } else if(opt->autonomie == -1){
                    printf("Entrez la nouvelle autonomie du véhicule : ");
                    scanf("%d", &opt->autonomie);
                } 
                else {
                    exit(0);
                }
                break;
            case 4:
                if(opt->deux_roues == -1){
                    printf("Entrez le nouveau type de véhicule (2 pour autorisé uniquement les 2 roues, 4 pour les interdire): ");
                    int decision;
                    scanf("%d", &decision);
                    if(decision == 2){
                        opt->deux_roues = true;
                    }
                    else if(decision == 4){
                        opt->deux_roues = false;
                    }
                } else if(opt->autonomie == -1){
                    printf("Entrez la nouvelle autonomie du véhicule : ");
                    scanf("%d", &opt->autonomie);
                } 
                else {
                    exit(0);
                }
                break;
            case 5:
                if(opt->autonomie == -1){
                    printf("Entrez la nouvelle autonomie du véhicule : ");
                    scanf("%d", &opt->autonomie);
                } 
                else {
                    exit(0);
                }
                break;
            default:
                exit(0);
                break;
        }
    }
    
    return opt;
}

rdn_data *traitement_random(){
    rdn_data *rnd = malloc(sizeof(rdn_data));
    rnd->nb_cars = -1;
    rnd->nb_steps = -1;
    bool not_finished = true;
    int i = 2;
    while (not_finished)
    {
        printf("1) Lancer le programme");
        if(rnd->nb_cars == -1){
            printf("%d) Choisir le nombre de véhicules autorisés", i);
            i += 1;
        }      
        if(rnd->nb_steps == -1){
            printf("%d) Choisir le nombre d'étapes", i);
            i += 1;
        }
        printf("%d) Quitter le programme", i);
        int choix;
        scanf("%d", &choix);
        switch (choix)
        {
            case 1:
                return rnd;
                break;
            case 2:
                if(rnd->nb_cars == -1) {
                    printf("Entrez le nombre de véhicules autorisés : ");
                    scanf("%d", &rnd->nb_steps);
                }
                else if(rnd->nb_steps == -1) {
                    printf("Entrez le nombre d'étapes : ");
                    scanf("%d", &rnd->nb_steps);
                } else {
                    exit(0);
                }
                break;
            case 3:
                if(rnd->nb_steps == -1) {
                    printf("Entrez le nombre d'étapes : ");
                    scanf("%d", &rnd->nb_steps);
                } else {
                    exit(0);
                }
            default:
                exit(0);
                break;
        }
    }
    
    return rnd;
}