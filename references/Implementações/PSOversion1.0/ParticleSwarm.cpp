#include<iostream>
#include<stdlib.h>
#include"Avaliation_Function.h"
#include"ParticleSwarm.h"
#include<time.h>
#define NUMFUNC 1

typedef struct particle{
    double *position;
    double *best_position;
    double *velocity;
    double fitness;
    double best_fitness;
}Particle;

double* ParticleSwarm(int dimension, int number_particles, double criterion_stop){
    srand(0);

    Particle *population = new Particle[number_particles];
    int i, j;

    //velocity parameters
    double inertia_factor = 1.0;
    double cognition_parameter = 1.0;
    double social_parameter = 1.0;
    double **omega1 = new double*[number_particles], **omega2=new double*[number_particles];

    for(i=0; i<number_particles; i++){
        omega1[i] = new double[dimension];
        omega2[i] = new double[dimension];
        for(j=0; j<dimension; j++){
            omega1[i][j] = rand()*0.1;
            omega2[i][j] = rand()*0.1;
        }
    }

    //initialize a population of particles with random positions and velocities
    for(i = 0; i<number_particles; i++){
        population[i].position = new double[dimension];
        population[i].velocity = new double[dimension];
        population[i].best_position = new double[dimension];
        for(j=0; j<dimension; j++){
            population[i].position[j] = rand();
            population[i].best_position[j] = population[i].position[j];
            population[i].velocity[j] = 0.0;
            population[i].fitness = Compute_Function(population[i].position, dimension, NUMFUNC);
            population[i].best_fitness = population[i].fitness;
        }
    }
    //population intialized

    //find the best fitness
    double fitness_global = population[0].fitness;
    double *position_global = new double[dimension];
    for(j=0; j<dimension; j++){ position_global[j] = population[0].position[j]; }
    for(i=1; i<number_particles; i++){
        if(population[i].fitness < fitness_global){
            fitness_global = population[i].fitness;
            for(j=0; j<dimension; j++){ position_global[j] = population[i].position[j]; }
        }
    }

    double stop = 1;
    while(stop > criterion_stop){
        for(i=0; i<number_particles; i++){
            for(j=0; j<dimension; j++){
                population[i].velocity[j] = inertia_factor*population[i].velocity[j] + cognition_parameter*omega1[i][j]*(population[i].best_position[j] -
                                            population[i].position[j]) + social_parameter*omega2[i][j]*(position_global[j] - population[i].position[j]);
                population[i].position[j] = population[i].position[j] + population[i].velocity[j];
            }

            population[i].fitness = Compute_Function(population[i].position, dimension, NUMFUNC);
            if(population[i].fitness < population[i].best_fitness){
                population[i].best_fitness = population[i].fitness;
                for(j=0; j<dimension; j++){
                    population[i].best_position[j] = population[i].position[j];
                }
            }

            if(population[i].fitness < fitness_global){
                fitness_global = population[i].fitness;
                for(j=0; j<dimension; j++){
                    position_global[j] = population[i].position[j];
                }
            }else{ stop = stop*0.5;}
        }
    }

    for(i=0; i<number_particles; i++){
        for(j=0; j<dimension; j++){
            delete []population[i].position;
            delete []population[i].best_position;
            delete []population[i].velocity;
            delete []omega1[j];
            delete []omega2[j];
        }
    }
    delete []population;
    delete []omega1;
    delete []omega2;

    return position_global;
}
