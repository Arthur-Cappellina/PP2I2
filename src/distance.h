#ifndef __DISTANCE_H__
#define __DISTANCE_H__
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))


typedef struct square{
    double lat_max;
    double lat_min;
    double longi_max;
    double longi_min;
}square;


double heuristic(double lat1, double longi1, double lat12, double longi2);
double distance_entre(double lat1, double longi1, double lat12, double longi2);
square * deli(double lat1, double longi1, double lat2, double longi2);

#endif
