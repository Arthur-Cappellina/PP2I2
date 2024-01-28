#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "data.h"
#include "a_etoile.h"
#include "structure.h"
#include "distance.h"


int main(int argc, char **argv) {

    // Le cas où les paramètres sont des noms de stations et qu'il n'y a pas d'options
    if(argc == 3){
        // on assert que les 2 paramètres 
        traitement_nom(argv[1], argv[2], NULL);
    }

    // Le cas où les paramètres sont des coordonnées et qu'il y a des options
    if(argc == 4){
        options *opt = traitement_options(argc, argv);
        return 1;
    }

    // Le cas où les paramètres sont des coordonnées et qu'il n'y a pas d'options
    if(argc == 5){
        traitement_coordonnees(atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), NULL);
        return 1;
    }

    // Le cas où les paramètres sont des noms de stations et qu'il y a des options
    if(argc == 6){
        options *opt = traitement_options(argc, argv);
        traitement_nom(argv[1], argv[2], opt);
        return 1;
    }

    return 0;
}

void traitement_nom(char* nom1, char* nom2, options* opt){
    // récupération de tous les noeuds
    nodes *n;
    if(opt != NULL){
        n = load_nodes_by_name(opt->min_pdc, opt->deux_roues);
    } else {
        n = load_nodes_by_name(-1, -1);
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
        n = load_nodes_by_lat(opt->min_pdc, opt->deux_roues);
    } else {
        n = load_nodes_by_lat(-1, -1);
    }

    assert(n != NULL);

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

options* traitement_options(int argc, char **argv){
    options *opt = malloc(sizeof(options));
    opt->batterie = -1;
    opt->min_pdc = -1;
    opt->deux_roues = -1;
    opt->autonomie = -1;
    bool not_finished = true;
    int i = 2;
    while (not_finished)
    {
        printf("1) Lancer le programme\n");
        if(opt->batterie == -1){
            printf("%d) Choisir le pourcentage minimal batterie\n", i);
            i += 1;
        }
        if(opt->min_pdc == -1){
            printf("%d) Choisir le nombre de points de charge disponibles\n", i);
            i += 1;
        }    
        if(opt->deux_roues == -1){
            printf("%d) Choisir le type de véhicule\n", i);
            i += 1;
        }      
        if(opt->autonomie == -1){
            printf("%d) Choisir l'autonomie du véhicule\n", i);
            i += 1;
        }
        printf("%d) Quitter le programme\n", i);
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
        i = 2; 
    }
    
    return opt;
}