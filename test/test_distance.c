#define SNOW_ENABLED

#include "snow.h"
#include "../src/distance.h"

describe(distance_entre) {
    it("distance entre") {
        // distance vol d'oiseau paris nancy
        int distance = distance_entre(48.8, 2.33,48.6,6.18);
        int res = (distance > 280 && distance < 285);
        asserteq(res,1);
    }
}

describe(heuristic) {
    it("heuristic test ") {
        int h1 = heuristic(3,1,6,5);
        int h2 = heuristic(-3,-1,-6,-5);
        asserteq(h1,7);
        asserteq(h2,7);
    }
}




snow_main();
