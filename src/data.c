#include "data.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "a_etoile.h"
#include <string.h>
#include <ctype.h> 

station *find_station_by_name(char *name, struct nodes* nodes){
    int id = find_id_by_name_annexe(name, nodes);
    if(id == -1){
        return NULL;
    }
    return nodes->stations[id];
}

station *find_station_by_lat(double lat, struct nodes* nodes){
    // printf("lat : %lf\n", lat);
    int id = find_id_by_lat_annexe(lat, nodes);
    // printf("id : %d\n", id);
    if(id == -1){
        return NULL;
    }
    return nodes->stations[id];
}

int find_id_by_lat_annexe(double lat, struct nodes* nodes) {
    int gauche = 0;
    int droite = nodes->size - 1;
    // printf("0:%lf", nodes->stations[0]->lat);
    while(gauche <= droite) {
        int milieu = (gauche + droite) / 2;
        // printf("    lat courante: %lf, milieu : %d\n", nodes->stations[milieu]->lat, milieu);
        if(nodes->stations[milieu]->lat == lat) {
            return nodes->stations[milieu]->id;
        } else if(nodes->stations[milieu]->lat > lat) {
            droite = milieu - 1;
        } else {
            gauche = milieu + 1;
        }
    }
    
    return -1;
}

char* strlwr(const char* str) {
    size_t len = strlen(str);
    char* result = malloc(len + 1); // +1 for the null terminator
    if (result == NULL) {
        // Handle allocation failure
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        result[i] = tolower((unsigned char)str[i]);
    }
    result[len] = '\0'; // Add null terminator

    return result;
}

void remove_first_character(char* str) {
    size_t len = strlen(str);
    if (len > 0) {
        memmove(str, str + 1, len);  // Shift the string one position to the left
    }
}

int find_id_by_name_annexe(char *name, struct nodes* nodes) {
    int gauche = 0;
    int droite = nodes->size - 1;
    while(gauche <= droite) {
        int milieu = (gauche + droite) / 2;
        char *lowercase_name = strlwr(name); 

        char *lowercase_station_name = strlwr(nodes->stations[milieu]->name);
        remove_first_character(lowercase_station_name);
        
        if(strcasecmp(lowercase_name, lowercase_station_name) == 0) {
            free(lowercase_name);
            free(lowercase_station_name);
            return nodes->stations[milieu]->id;
        } else if(strcasecmp(lowercase_name, lowercase_station_name) < 0) {
            droite = milieu - 1;
        } else {
            gauche = milieu + 1;
        }
        free(lowercase_name);
        free(lowercase_station_name);
    }
    
    return -1;
}

void display_name_with_chemin(list_t *chemin, struct nodes* nodes){
    cellule_t *tmp = chemin->premier;
    while (tmp != NULL)
    {
        printf("%s\n", nodes->stations[tmp->id_station]->name);
        tmp = tmp->suivant;
    }
    
}




station * find_station_by_id(int id, struct nodes* nodes){
    return nodes->stations[id];
}

double find_lat_by_id(int id, struct nodes* nodes){
    return nodes->stations[id]->lat;
}

double find_lon_by_id(int id, struct nodes* nodes){
    return nodes->stations[id]->lon;
}

nodes *load_nodes_by_name(int pdc, int deux_roues){
    return load_nodes("../data/stations.csv", pdc, deux_roues);
}

nodes *load_nodes_by_lat(int pdc, int deux_roues){
    return load_nodes("../data/stations_lat.csv", pdc, deux_roues);
}


nodes *load_nodes(char *filename, int pdc, int deux_roues){
    FILE *f = fopen(filename,"r");
    if (f == NULL){
        printf("Error opening file");
        exit(1);
    }
    nodes *n = malloc(sizeof(nodes));
    n->size = 0;
    n->capacity = 20000;
    n->stations = malloc(sizeof(station) * n->capacity);
    char *line = NULL;
    size_t len = 0;
    size_t read;
    char *temp;
    while ((read = getline(&line, &len, f)) != -1){
        if(line[0] == 'i'){
            continue;
        }
        if(n->size == n->capacity){
            n->capacity += 5000;
            n->stations = realloc(n->stations, sizeof(station) * n->capacity);
        }
        //----------------------
        temp = strtok(line, ",");
        int id = atoi(temp);

        temp = strtok(NULL, ",");
        char * name = strdup(temp);

        temp = strtok(NULL, ",");
        char * addr = strdup(temp);

        temp = strtok(NULL, ",");
        double lat = strtod(temp, NULL);
        
        temp = strtok(NULL, ",");
        double lon  = strtod(temp, NULL);

        temp = strtok(NULL, ",");
        bool roues_2 = atoi(temp);

        temp = strtok(NULL, ",");
        int Pdc = atoi(temp);

        temp = strtok(NULL, ",");
        int puissance = atoi(temp);

        if((pdc != Pdc && pdc != -1) || (deux_roues == roues_2 && deux_roues != -1)){
            continue;
        }
        station * s = crea_station(id,name,addr,lon,lat,roues_2,Pdc,puissance);
        //----------------------
        n->stations[id] = s;
        n->size++;
    }
    free(line);
    fclose(f);
    return n;
}


station * crea_station(int id, char * name, char * addr, double lon, double lat, bool roues_2, int pdc, int puissance){
    station* s = malloc(sizeof(station));
    s->id = id;
    s->name = name;
    s->addr = addr;
    s->lat = lat;
    s->lon = lon;
    s->autorise_2_roues = roues_2;
    s->pdc = pdc;
    s->puissance_nominale = puissance;
    s->file_attente = NULL;
    return s;
}

void display_nodes(nodes *n){
    for(int i = 0; i < n->size; i++){
        printf("id: %d, name: %s, addr: %s, lon: %lf, lat: %lf\n", n->stations[i]->id, n->stations[i]->name, n->stations[i]->addr, n->stations[i]->lon, n->stations[i]->lat);
    }
}

void free_nodes(nodes *n){
    for(int i = 0; i < n->size; i++){
        free(n->stations[i]->name);
        free(n->stations[i]->addr);
        free(n->stations[i]);
    }
    free(n->stations);
    free(n);
}

void free_station(station *s){
    free(s->name);
    free(s->addr);
    free_file(s->file_attente);
    free(s);
}
