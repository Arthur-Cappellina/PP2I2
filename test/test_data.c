#define SNOW_ENABLED

#include "snow.h"
#include "../src/data.h"

describe(load_nodes) {
    it("load nodes test") {
        nodes * n = load_nodes("../data/stations_test.csv",1,1);
        station ** s = n->stations;
        asserteq(s[0]->id,0);
        char * name = " name0 ";
        asserteq(s[0]->name, name);
    }
}


describe(find_lat_by_id) {
    it("find latitude by id test") {
        nodes * n = load_nodes("../data/stations_test.csv",1,1);
        double lat = 1.3;
        asserteq(find_lat_by_id(3, n), lat);
    }
}

describe(find_lon_by_id) {
    it("find longitude by id test") {
        nodes * n = load_nodes("../data/stations_test.csv",1,1);
        double lon = 3.3;
        asserteq(find_lon_by_id(3, n), lon);
    }
}


describe(find_id_by_name_annexe) {
    it("find id by name test") {
        nodes * n = load_nodes("../data/stations_test.csv",1,1);
        int id = 3;
        asserteq(find_id_by_name_annexe(" name3 ", n), id);
    }
}

describe(find_station_by_name) {
    it("find station by name test") {
        nodes * n = load_nodes("../data/stations_test.csv",1,1);
        int id = 3;
        station * s = n->stations[id];
        asserteq(find_station_by_name(" name3 ", n)->name, s->name);
    }
}


describe(find_id_by_lat_annexe) {
    it("find id by lat annexe test") {
        nodes * n = load_nodes("../data/stations_test.csv",1,1);
        int id = 6;
        asserteq(find_id_by_lat_annexe(3.6, n), id);
    }
}

describe(find_station_by_lat) {
    it("find station by lat test") {
        nodes * n = load_nodes("../data/stations_test.csv",1,1);
        int id = 6;
        station * s = n->stations[id];
        asserteq(find_station_by_lat(3.6, n)->name, s->name);
    }
}







snow_main();
