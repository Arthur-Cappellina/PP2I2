#define SNOW_ENABLED

#include "snow.h"
#include "../src/a_etoile.h"


// ----------------TEST LIST--------------------- 

describe(list_create) {
    it("list create test") {
        list_t * list = list_create();
        asserteq(list->premier,NULL);
        asserteq((list != NULL),1);
        asserteq(list_is_empty(list),1);
        bool res = list_destroy(list);
        asserteq(res,true);
    }
}


describe(list_append) {
    it("list append test") {
        list_t * list = list_create();
        list_append(list, 1);
        list_append(list, 2);
        asserteq(list->premier->id_station,1);
        asserteq(list->premier->suivant->id_station,2);
        list_destroy(list);
    }
}


describe(list_contains) {
    it("list contains test") {
        list_t * list = list_create();
        list_append(list, 1);
        list_append(list, 2);
        asserteq(list_contains(list,2),1);
        list_destroy(list);
    }
}

describe(remove_first) {
    it("list remove first test") {
        list_t * list = list_create();
        list_append(list, 1);
        list_append(list, 2);
        remove_first(list);
        asserteq(list->premier->id_station,2);
        asserteq(list->premier->suivant,NULL);
        list_destroy(list);
    }
}

describe(remove_last) {
    it("list remove last test") {
        list_t * list = list_create();
        list_append(list, 1);
        list_append(list, 2);
        remove_last(list);
        asserteq(list->premier->id_station,1);
        asserteq(list->premier->suivant,NULL);
        list_destroy(list);
    }
}


// ------------A_etoile_v1 TEST-------------------


describe(A_etoile_v1) {
    it("list A_etoile_v1 test 1") {
        double lat_depart = 0.0;
        //double lon_depart = 0.0;
        double lat_arrivee = 3.7;
        //double lon_arrivee = 3.7;

        nodes *n = load_nodes("../data/stations_test.csv",1,1);
        station* start = find_station_by_lat(lat_depart, n);
        station* end = find_station_by_lat(lat_arrivee, n);
        int autonomy = 200;
        list_t * chemin = A_etoile_v1(n, start->id, end->id,autonomy);

        asserteq(1,1);
    }

        it("list A_etoile_v1 test 2") {
        double lat_depart = -22.2461;
        double lon_depart = 166.462;
        double lat_arrivee = -22.1962;
        double lon_arrivee = 166.4454;

        nodes *n = load_nodes_by_lat(1,1);
        station* start = find_station_by_lat(lat_depart, n);
        station* end = find_station_by_lat(lat_arrivee, n);
        int autonomy = 200;
        list_t * chemin = A_etoile_v1(n, start->id, end->id,autonomy);

        asserteq(1,1);
    }


    it("list A_etoile_v1 test 3 liste vide trop loin") {

        nodes *n = load_nodes_by_lat(1,1);

        station * lat_depart = find_station_by_id(0,n);
        station * lat_arrivee = find_station_by_id(17173,n);
        int autonomy = 200;
        list_t * chemin = A_etoile_v1(n, lat_depart->id, lat_arrivee->id,autonomy);
        list_print(chemin);
        asserteq(chemin,NULL);
    }
}


// describe(A_etoile) {
//     it("list A_etoile_v2 test 1") {
//         double lat_depart = 0.0;
//         double lon_depart = 0.0;
//         double lat_arrivee = 3.7;
//         double lon_arrivee = 3.7;

//         nodes *n = load_nodes("../data/stations_test.csv");
//         station* start = find_station_by_lat(lat_depart, n);
//         station* end = find_station_by_lat(lat_arrivee, n);
//         //int autonomy = 200;
//         list_t * chemin = A_etoile(n, start->id, end->id);

//         asserteq(1,1);
//     }

//         it("list A_etoile_v2 test 2") {
//         double lat_depart = -22.2461;
//         double lon_depart = 166.462;
//         double lat_arrivee = -22.1962;
//         double lon_arrivee = 166.4454;

//         nodes *n = load_nodes_by_lat();
//         station* start = find_station_by_lat(lat_depart, n);
//         station* end = find_station_by_lat(lat_arrivee, n);
//         //int autonomy = 200;
//         list_t * chemin = A_etoile(n, start->id, end->id);

//         asserteq(1,1);
//     }
// }





snow_main();
