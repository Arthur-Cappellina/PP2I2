#include <stdbool.h>
#include "file.h"
#include "a_etoile.h"
#ifndef __DATA_H__
#define __DATA_H__

// structure représentant une station
typedef struct station {
    int id;
    char* name; 
    char* addr;
    double lon;
    double  lat;
    bool autorise_2_roues;
    int pdc;
    int puissance_nominale;
    struct file * file_attente;
} station;

typedef struct nodes {
    struct station** stations;
    int size;
    int capacity;
} nodes;

typedef struct options options;

struct options{
    int batterie;
    int min_pdc;
    int deux_roues; // 0 si faux, 1 si vrai, -1 si non renseigné
    int autonomie; 
};

void traitement_nom(char* nom1, char* nom2, options* opt);
void traitement_coordonnees(double lat1, double lon1, double lat2, double lon2, options* opt);
options* traitement_options(int argc, char **argv);


// Les méthodes pour trouver une station
station *find_station_by_name(char *name, struct nodes* nodes);
int find_id_by_name_annexe(char *name, struct nodes* nodes);
station *n(double lat, struct nodes* nodes);
int find_id_by_lat_annexe(double lat, struct nodes* nodes);
double find_lat_by_id(int id, struct nodes* nodes);
double find_lon_by_id(int id, struct nodes* nodes);
station *find_station_by_lat(double lat, struct nodes* nodes);
station * find_station_by_id(int id, struct nodes* nodes);

// Les méthodes pour générer les stations
nodes *load_nodes(char *filename, int pdc, int deux_roues);
nodes *load_nodes_by_lat(int pdc, int deux_roues);
nodes *load_nodes_by_name(int pdc, int deux_roues);

typedef struct list_t list_t;

void display_name_with_chemin(list_t *chemin, struct nodes* nodes);

// Afficher les stations
void display_nodes(nodes *n);


//La méthode pour créer une station
station * crea_station(int id, char * name, char * addr, double lon, double lat, bool roues_2, int pdc, int puissance);

// La méthode pour libérer la mémoire
void free_nodes(nodes *n);
void free_station(station *s);

#endif
