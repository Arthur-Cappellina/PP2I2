#include "data.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int main(){
    nodes *n = load_nodes_by_lat();
    station *s = find_station_by_lat(43.220969, n);
    if(s == NULL){
        printf("NULL");
    } else {
        printf("%d %s %s %f %f", s->id, s->name, s->addr, s->lon, s->lat);
    }
    free_nodes(n);
    return 0;
}
