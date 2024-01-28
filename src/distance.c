#include "distance.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

const double pi = 3.14159265358979323846;

double distance_entre(double lat1, double longi1, double lat2, double longi2){
    double r = 6378137;
    double lat1_rad = lat1/180 * pi;
    double longi1_rad = longi1/180*pi;
    double lat2_rad = lat2/180*pi;
    double longi2_rad = longi2/180*pi;
    double inte = sin(lat1_rad)*sin(lat2_rad)+cos(lat1_rad)*cos(lat2_rad)*cos(fabs(longi2_rad-longi1_rad));
    double distance = r*acos(inte);
    return distance/1000;

}

double heuristic(double lat1, double longi1, double lat2, double longi2){
    return fabs(longi2-longi1)+ fabs(lat2-lat1);
}

square * deli(double lat1, double longi1, double lat2, double longi2){
    double lat_min = min(lat1,lat2);
    double lat_max = max(longi1,longi2);
    double longi_max = max(longi1,longi2);
    double longi_min = min(longi1,longi2);
    double op_latitude = 50/111.11;
    double op_longitude = 50/60;
    lat_max = lat_max + op_latitude;
    lat_min = lat_min - op_latitude;
    longi_max = longi_max + op_longitude;
    longi_min = longi_min - op_longitude;
    //------------------------
    square * square = calloc(1,sizeof(square));
    square->lat_max = lat_max;
    square->lat_min = lat_min;
    square->longi_max = longi_max;
    square->longi_min = longi_min;
    return square;
}

