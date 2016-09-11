#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include "Estrategias.h"
#include "Individuo.h"
#include <time.h>
#include <string.h>
#include <fstream>
#include <cmath>

#define INF 1E+21

using namespace std;

int func_eval=0;
double delta;
int success_direction = -1;

double random_generate(){
    return ((rand())/(RAND_MAX+1.0));
}

double EvolucaoDiferencial(double (*objfun)(double*), double fator_ponderacao, double cr, int dimension, int num_individuos, int seed, double *lb, double *ub){

    func_eval=0;
    srand(seed);

    Individuo **pop = new Individuo*[num_individuos];
    Individuo *best = new Individuo(dimension);

    for(int i=0; i<num_individuos; i++){
        pop[i] = new Individuo(dimension);

        for(int j=0; j<dimension; j++){
            if(lb && ub){
                pop[i]->posicao[j] = (ub[j]-lb[j])*random_generate() + lb[j];
            }
            else{
                pop[i]->posicao[j] = random_generate();
            }
        }
    }

    for(int i=0; i<num_individuos; i++){
        pop[i]->valor = objfun(pop[i]->posicao);
        func_eval++;
    }

    int ibest = 0;
    best->valor = pop[0]->valor;
    for(int i=0; i<dimension; i++){
        best->posicao[i] = pop[0]->posicao[i];
    }
    for(int i=1; i<num_individuos; i++){
        if(best->valor > pop[i]->valor){
            ibest = i;
            best->valor = pop[i]->valor;
        }
    }
    for(int i=0; i<dimension; i++){
        best->posicao[i] = pop[ibest]->posicao[i];
    }

//    int parada = Number_Evaluations(num_func);
    int parada = 2000;

    while(func_eval < parada){

        int alpha, beta, gamma;
        double mutado[num_individuos][dimension];
        Individuo **tentativa = new Individuo*[num_individuos];
        for(int i=0; i<num_individuos; i++){
            tentativa[i] = new Individuo(dimension);
        }

        //mutação
        for(int i=0; i<num_individuos; i++){

            alpha = rand()%num_individuos;
            beta = rand()%num_individuos;
            gamma = rand()%num_individuos;

            while(alpha == i){
                alpha = rand()%num_individuos;
            }
            while(beta == alpha || beta == i){
                beta = rand()%num_individuos;
            }
            while(gamma == beta || gamma == alpha || gamma == i){
                gamma = rand()%num_individuos;
            }

            for(int j=0; j<dimension; j++){
                mutado[i][j] = pop[gamma]->posicao[j] + fator_ponderacao*(pop[alpha]->posicao[j] - pop[beta]->posicao[j]);

                if(mutado[i][j] > ub[j]){
                    mutado[i][j] = ub[j];
                }
                if(mutado[i][j] < lb[j]){
                    mutado[i][j] = lb[j];
                }
            }

        }

        //cruzamento
        double r;
        for(int i=0; i<num_individuos; i++){
           for(int j=0; j<dimension; j++){
                r = random_generate();
                if(r <= cr){
                    tentativa[i]->posicao[j] = mutado[i][j];
                }
                else{
                    tentativa[i]->posicao[j] = pop[i]->posicao[j];
                }
            }
        }

        //selecao
        for(int i=0; i<num_individuos; i++){

            tentativa[i]->valor = objfun(tentativa[i]->posicao);
            func_eval++;
            if(tentativa[i]->valor < pop[i]->valor){
                pop[i]->valor = tentativa[i]->valor;
                for(int j=0; j<dimension; j++){
                    pop[i]->posicao[j] = tentativa[i]->posicao[j];
                }
                if(pop[i]->valor < best->valor){
                    best->valor = pop[i]->valor;
                    for(int j=0; j<dimension; j++){
                        best->posicao[j] = pop[i]->posicao[j];
                    }
                }
            }
        }

        for(int i=0; i<num_individuos; i++){
            delete tentativa[i];
        }
        delete tentativa;
    }

//    cout<<";"<<setprecision(10)<<best->valor;
//    cout<<setprecision(10)<<best->valor;

    double aux = best->valor;
    delete best;
    for(int i=0; i<num_individuos; i++){
        delete pop[i];
    }
    delete pop;

    return aux;
}