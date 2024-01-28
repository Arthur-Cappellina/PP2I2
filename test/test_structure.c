#define SNOW_ENABLED

#include "snow.h"
#include "../src/structure.h"
#include "../src/data.h"


describe(crea_table) {
    it("creation table test") {
        table_h * table = crea_table(5);
        bool destroy = destroy_table(table);
        asserteq(1, destroy);
    }
}


describe(insert) {
    it("insert test") {
        table_h * table = crea_table(5);
        station * station1 = crea_station(1,"station1", "0001 rue de TN", 0, 0,true,1,1);
        station * station2 = crea_station(2,"station2", "0010 rue de TN", 1, 1,true,1,1);
        station * station3 = crea_station(3,"station3", "0011 rue de TN", 2, 2,true,1,1);
        station * station4 = crea_station(4,"station4", "0100 rue de TN", 3, 3,true,1,1);

        int poids = 1;

        insert(table, station1, poids);
        int res = find(table, station1);
        asserteq(res,1);
        free(station1);
        free(station2);
        free(station3);
        free(station4);
        destroy_table(table);
    }
}


// test table came

describe(crea_came_f) {
    it("creation table came test") {
        table_ch * table = crea_came_f(5);
        bool destroy = destroy_table_ch(table);
        asserteq(1, destroy);
    }
}

describe(insert_came){
    it("insert came test"){
        table_ch * table = crea_came_f(5);
        station * station1 = crea_station(1,"station1", "0001 rue de TN", 0, 0,true,1,1);
        station * station2 = crea_station(2,"station2", "0010 rue de TN", 1, 1,true,1,1);
        station * station3 = crea_station(3,"station3", "0011 rue de TN", 2, 2,true,1,1);
        station * station4 = crea_station(4,"station4", "0100 rue de TN", 3, 3,true,1,1);
        insert_came(table, station1, station2);
        insert_came(table, station2, station3);
        insert_came(table, station3, station4);
        asserteq(station2->id, find_ch(table, station1)->id);
        asserteq(station3->id, find_ch(table, station2)->id);
        asserteq(station4->id, find_ch(table, station3)->id);
        destroy_table_ch(table);
    }
}




snow_main();
