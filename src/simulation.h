#include "data.h"
#include "file.h"

#ifndef __SIMULATION_H__
#define __SIMULATION_H__

typedef struct simulation simulation;

struct simulation{
    int nbcars; 
    int capacity;
    int steps_left;
    voiture **voiture; 
    nodes *stations;
};

simulation *init_simulation_random(int nb_cars, int nb_steps, options *opt);
simulation *init_simulation_base(options *opt);

void run_next_step(nodes *stations, simulation *simulation);
void evolue_voiture(voiture *voiture, nodes *stations); 
void voiture_out_of_file(voiture* voiture, nodes *stations);
void evolue_file(file *file, nodes *stations); 

void display_simulation(simulation *simulation);
void display_voiture(voiture *voiture);
void free_simulation();



#endif // __SIMULATION_H__
