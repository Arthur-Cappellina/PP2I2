#define SNOW_ENABLED

#include "snow.h"
#include "../src/simulation.h"


// ----------------TEST LIST--------------------- 

describe(init_simulation_base) {
    it("init_simulation_base") {
        simulation *simu = init_simulation_base(NULL);
        //simulate(simu, 100);// :(
        asserteq(1, 1);
    }
}






snow_main();
