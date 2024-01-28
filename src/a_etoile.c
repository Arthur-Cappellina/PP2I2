#include "a_etoile.h"
#include <stdlib.h>
#include <stdio.h>

list_t* list_create(){
    list_t *list = malloc(sizeof(list_t));
    list->premier = NULL;
    return list;
}

void remove_first(list_t *one_list){
    cellule_t *c = one_list->premier;
    one_list->premier = one_list->premier->suivant;
    free(c);
}

void remove_last(list_t *one_list){
    if (list_is_empty(one_list)) return;
    if (one_list->premier->suivant == NULL){
        remove_first(one_list);
        return;
    }
    cellule_t *cursor = one_list->premier;
    while(cursor->suivant->suivant != NULL) cursor = cursor->suivant;
    free(cursor->suivant);
    cursor->suivant = NULL;
}


bool list_destroy(list_t *one_list){
    if (one_list == NULL){
        free(one_list);
        return true;
    } 
    while (0 == list_is_empty(one_list)) remove_first(one_list);
    free(one_list); 
    return true;
}

bool list_is_empty(list_t *one_list){
    if (one_list->premier == NULL) return 1;
    return 0;
}

void list_append(list_t *one_list, int id){
    cellule_t *c = malloc(sizeof(*c));
    c->id_station = id;
    c->suivant = NULL;
    if (list_is_empty(one_list)){
        one_list->premier = c;
        return;
    }
    cellule_t *cursor = one_list->premier;
    while(cursor->suivant != NULL) cursor = cursor->suivant;
    cursor->suivant = c;
}

bool list_contains(list_t* one_list, int id){
    cellule_t *cursor = one_list->premier;
    while( cursor != NULL){
        if (cursor->id_station == id) return 1;
        cursor = cursor->suivant; 
    }
    return 0;
}

void list_print(list_t* list){
    if (list == NULL) {
        printf("pas de chemin trouvé\n");
        return;
    }
    cellule_t *cursor = list->premier;
    printf("[ ");
    while (cursor != NULL){
        if (cursor->suivant == NULL) printf("%d ",cursor->id_station);
        else printf("%d, ",cursor->id_station);
        cursor = cursor->suivant;
    } 
    printf("]\n");
}

int last(list_t *one_list){
    if (list_is_empty(one_list)) return NULL;
    cellule_t *cursor = one_list->premier;
    while (cursor->suivant != NULL) cursor = cursor->suivant;
    return cursor->id_station;
    
}

// version sans backtracking (doit planter dans certaines situations)
list_t* A_etoile_v1(struct nodes* nodes, int start, int end, int autonomy){
    // Liste qui garde les stations du chemin optimal
    list_t* list_station = list_create();
    // On ajoute le départ 
    list_append(list_station,start);
    // printf("station de depart : ");
    // list_print(list_station);
    // printf("nodes_size : %d\n",nodes->size);
    // La position actuelle est le départ (la meilleure)
    int pos = start;
    int best = start;
    double best_distance;
    // printf("start : %d, end : %d\n",start,end);
    // Coordonées début et fin du parcours
    double lat_pos = find_lat_by_id(pos, nodes);
    double lon_pos = find_lon_by_id(pos, nodes);
    double lat_end = find_lat_by_id(end, nodes);
    double lon_end = find_lon_by_id(end, nodes);
    // printf("lat start : %f, lon start : %f, lat end : %f lon end : %f\n",lat_pos,lon_pos,lat_end,lon_end);

    // Tant que la position actuelle n'est pas la fin
    while (pos != end){
        best_distance = 1000000;

        // Parcours de chaque station
        for (int i=0;i<nodes->size;i++){
            double lat_i = find_lat_by_id(i, nodes);
            double lon_i = find_lon_by_id(i, nodes);
            double distance_courante = distance_entre(lat_pos,lon_pos,lat_i,lon_i) + distance_entre(lat_end,lon_end,lat_i,lon_i);
            // On cherche la station la plus proche accessible
            // if (i<5) printf("i : %d\ndistance courante : %f\nbest distance : %f\n\n",i,distance_courante,best_distance);
            if ((best_distance > distance_courante) && distance_entre(lat_pos,lon_pos,lat_i,lon_i)!=0 && (distance_entre(lat_pos,lon_pos,lat_i,lon_i) < autonomy)){
                best = i;
                best_distance = distance_courante;
            }
        }
        // On ajoute la station la plus proche à la liste
    //    printf("distance pos / new pos : %f\n",distance_entre(lat_pos,lon_pos,find_lat_by_id(best, nodes),find_lon_by_id(best, nodes)));
      //  printf("distance new pos / end : %f\n",distance_entre(lat_end,lon_end,find_lat_by_id(best, nodes),find_lon_by_id(best, nodes)));
        pos = best;
        lat_pos = find_lat_by_id(best, nodes);
        lon_pos = find_lon_by_id(best, nodes);
        if (list_contains(list_station,best)) {
            list_destroy(list_station);
            return NULL;
        }
        if (distance_entre(lat_end,lon_end,lat_pos,lon_pos)<1) pos = end;
        list_append(list_station,best);
        //list_print(list_station);
   //     printf("best_distance : %f\n",best_distance);
    }
    return list_station;
}

list_t* A_etoile(struct nodes* nodes, int start, int end){
    // Tableau de liste chainé pour stocker les chemins testés 
    struct list_t* backtracking[nodes->size];
    // Liste chainé contenant le chemin optimal 
    list_t* list_station = list_create();    
    list_append(list_station,start);
    backtracking[0] = list_create();

    // Initialisation du tableau de liste chainé
    for (int i=1;i<nodes->size;i++) backtracking[i] = NULL;
    list_append(backtracking[0],start); 
    int best;
    int best_distance;
    int pos = start;
    double lat_pos = find_lat_by_id(pos, nodes);
    double lon_pos = find_lon_by_id(pos, nodes);
    double lat_end = find_lat_by_id(end, nodes);
    double lon_end = find_lon_by_id(end, nodes);
    int compteur = 1;
    while(pos != end){
        best = NULL;
        best_distance = NULL;
        for (int i=0;i<nodes->size;i++){
            double lat_i = find_lat_by_id(i, nodes);
            double lon_i = find_lon_by_id(i, nodes);
            double distance_courante = distance_entre(lat_pos,lon_pos,lat_i,lon_i)+distance_entre(lat_end,lon_end,lat_i,lon_i);
            if ((best_distance == NULL || best_distance>(distance_courante)) && distance_entre(lat_pos,lon_pos,lat_i,lon_i) < CAPACITE_VOITURE && list_contains(list_station,i)==0 && list_contains(backtracking[compteur],i)==0){
                best = i;
                best_distance = distance_courante;
            }
        }
        // Si la station est "validée"
        if (best != NULL){
            if (backtracking[compteur]==NULL) {
                backtracking[compteur] = list_create();
            }
            list_append(list_station,best);
            list_append(backtracking[compteur],best);
            pos = best;
            compteur ++;
        }
        // Si aucun chemin convient 
        else if (list_station->premier->suivant == NULL) { 
            list_destroy(backtracking[1]);
            list_destroy(backtracking[0]);
            list_destroy(list_station);
            return NULL;  
        } 
        // cas où on revient en arrière pour trouver un chemin
        else {
            list_destroy(backtracking[compteur]);
            backtracking[compteur]=NULL;
            remove_last(list_station);
            pos = last(list_station);
            compteur --;
        }
        // double lat_pos = find_lat_by_id(pos, nodes); unused
        // double lon_pos = find_lon_by_id(pos, nodes); unused
    }
    for (int i=0;i<(compteur-1);i++) list_destroy(backtracking[i]);
    return list_station;
}   

