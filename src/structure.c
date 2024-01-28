#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "data.h"
#include "a_etoile.h"
#include <string.h>


//int fonction_hash(station* station_s){
//    int hash = 0;
//    for(int i = 0; i<strlen(station_s->name);i++){
//        hash +=station_s->name[i];
//    }
//    return hash;
//}

//int fonction_hash2(station* station_s,int mod){
//    int hash = fonction_hash(station_s);
//    return 1+ hash%(mod-2);
//}

table_h* crea_table(int size){
    table_h* tableau = malloc(sizeof(table_h));
    tableau ->size = size;
    tableau->count = 0;
    tableau->table = malloc(sizeof(couple)*size);
    for(int i =0;i<tableau->size;i++){
        tableau->table[i]=NULL;
    }
    return tableau;

}

bool destroy_table(table_h* table_hash){
    for(int i = 0; i<table_hash->size;i++){
        if(table_hash->table[i] != NULL){
            // free(table_hash->table[i]->station_s->addr);
            // free(table_hash->table[i]->station_s->name);
            free(table_hash->table[i]);
        }
    }
    free(table_hash->table);
    free(table_hash);
    return true;
}

void insert(table_h* table_hash,station* station_s1,int poids_d){
    int index = station_s1->id;
    couple* new_element = malloc(sizeof(couple));
    new_element->poids = poids_d;
    new_element->station_s = station_s1;
    table_hash->table[index] = new_element;
    table_hash->count++;
}

int find(table_h* table_hash, station* station_s1){
    int index = station_s1->id;
    return table_hash->table[index]->poids;
}

void print_table(table_h* table_hash){
    for(int i = 0;i<table_hash->size;i++){
        if(table_hash->table[i]!=NULL){
            printf("%s : %d",table_hash->table[i]->station_s->name,table_hash->table[i]->poids);   
        }
    }
}

table_ch* crea_came_f(int size){
    table_ch* tableau = malloc(sizeof(table_ch));
    tableau ->size = size;
    tableau->table = malloc(sizeof(came_from)*size);
    for(int i =0;i<tableau->size;i++){
        tableau->table[i]=NULL;
    }
    return tableau;
}

bool destroy_table_ch(table_ch* table){
    for(int i = 0; i<table->size;i++){
        if(table->table[i] != NULL){
            // free(table->table[i]->prece->addr);
            // free(table->table[i]->prece->name);
            // free(table->table[i]->suivant->addr);
            // free(table->table[i]->suivant->name);
            free(table->table[i]);
        }
    }
    free(table->table);
    free(table);
    return true;
}

void insert_came(table_ch* table, station* next, station* prece){
    int index = next->id;
    came_from* new = malloc(sizeof(came_from));
    new->prece = prece;
    new->suivant = next;
    table->table[index] = new; 
}

station* find_ch(table_ch* table, station* suivant){
    int index = suivant->id;
    return table->table[index]->prece;
}








