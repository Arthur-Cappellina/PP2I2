#define SNOW_ENABLED

#include "snow.h"
#include "../src/file.h"


// ----------------TEST LIST--------------------- 

describe(crea_file) {
    it("file create test") {
        struct file * file = crea_file(10);
        asserteq(is_empty(file),true);
    }
}

describe(crea_voiture) {
    it("voitu create test") {
        struct voiture * voitu = crea_voiture(10);
        asserteq(voitu->capacite_batterie,0);
    }
}


describe(add_element_file) {
    it("add file test") {
        file * file = crea_file(10);
        voiture * voitu = crea_voiture(10);

        add_element_file(file,voitu);
        asserteq(is_empty(file),false);
        struct voiture * res = first_file(file);
        asserteq(res->numero_usager,voitu->numero_usager);
    }

}

// describe(supprime_first){
//     it("supprime first test"){
//         file * file = crea_file(10);
//         voiture * voitu = crea_voiture(10);
//         add_file(file,voitu,10);
//         supprime_first(file);
//         asserteq(is_empty(file),true);
//     }
// }

describe(taille){
    it("taille test"){
        file * file = crea_file(10);
        voiture * voitu = crea_voiture(10);
        add_element_file(file,voitu);
        asserteq(taille(file),1);
    }

    it("taille test 2"){
        file * file = crea_file(10);
        voiture * voitu = crea_voiture(10);
        add_element_file(file,voitu);
        remove_element_file(file,file->first);
        asserteq(taille(file),0);
    }
}

describe(remove_element_file){
    it("test remove element file"){
        file * file = crea_file(10);
        voiture * voitu = crea_voiture(10);
        add_element_file(file,voitu);
        remove_element_file(file,file->first);
        asserteq(is_empty(file),true);
    }
}





snow_main();
