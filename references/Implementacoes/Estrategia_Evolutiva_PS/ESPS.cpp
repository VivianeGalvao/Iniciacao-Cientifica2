#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include "Avaliation_Function.h"
#include<random>

using namespace std;

int stop;

bool Exploratory_Moves(double *pattern, double delta, double *x_iteration, double function, int size, int number_function, double* lb, double* ub){

    bool exit = false;
    int i;
    double *x_perturbation = new double[size];
    double fx=function, fx_perturbation=0.0;


    for(i = 0; i<size; i++){x_perturbation[i] = x_iteration[i];}

    for(i=0; i<size; i++){

        x_perturbation[i] = x_iteration[i] + delta*pattern[i];

        if(lb != NULL && ub != NULL){
            if(x_perturbation[i] < lb[i] || x_perturbation[i] > ub[i]){
                x_perturbation[i] = x_iteration[i];
                x_perturbation[i] = x_iteration[i] - delta*pattern[i];
                if(x_perturbation[i] < lb[i] || x_perturbation[i] > ub[i]){  x_perturbation[i] = x_iteration[i]; }
                else{
                    fx_perturbation = Compute_Function(x_perturbation, size, number_function); stop++;
                    if(fx > fx_perturbation){ x_iteration[i] = x_perturbation[i]; fx = fx_perturbation; exit = true;}
                    else{ x_perturbation[i] = x_iteration[i]; }
                }
            } else{
                fx_perturbation = Compute_Function(x_perturbation, size, number_function); stop++;
                if(fx < fx_perturbation){
                    x_perturbation[i] = x_iteration[i];
                    x_perturbation[i] = x_iteration[i] - delta*pattern[i];
                }
                if(x_perturbation[i] < lb[i] || x_perturbation[i] > ub[i]){  x_perturbation[i] = x_iteration[i]; }
                else{
                    fx_perturbation = Compute_Function(x_perturbation, size, number_function); stop++;
                    if(fx > fx_perturbation){ x_iteration[i] = x_perturbation[i]; fx = fx_perturbation; exit = true;}
                    else{ x_perturbation[i] = x_iteration[i]; }
                }
            }
        }
        else{
            fx_perturbation = Compute_Function(x_perturbation, size, number_function);stop++;
            if(fx < fx_perturbation){
                x_perturbation[i] = x_iteration[i];
                x_perturbation[i] = x_iteration[i] - delta*pattern[i];
                fx_perturbation = Compute_Function(x_perturbation, size, number_function); stop++;
            }
            if(fx > fx_perturbation){ x_iteration[i] = x_perturbation[i]; fx = fx_perturbation; exit = true;}
            else{ x_perturbation[i] = x_iteration[i]; }
        }
    }

    delete []x_perturbation;
    return exit;
}

double Normal_distribuition(double mean, double desvio_padrao){
    default_random_engine generator;
    normal_distribution<double> distribution(mean,desvio_padrao);
    return distribution(generator);
}

void Evolutionary_Strategy(int seed, double expected_mean, int dimension, int number_function, double delta, double *x){
    if(delta > 0){
        stop = 0;
        srand(seed);
        double **pattern = new double*[2*dimension];
        int i;
        bool success = false;
        double desvio_padrao = expected_mean/sqrt(dimension),objective_function;
        int *successful = new int[dimension*10];

        //matriz de padrões
        for(i = 0; i<2*dimension; i++){
             pattern[i] = new double[dimension];
            for(int j=0; j<dimension; j++){
                if(i<dimension){
                    if(j==i){pattern[i][j] = 1.0;}
                    else{ pattern[i][j] = 0.0; }
                }
                else{
                    if(i-j == dimension){ pattern[i][j] = -1.0; }
                    else{ pattern[i][j] = 0.0; }
                }
            }
        }

       double *lb = new double[dimension], *ub = new double[dimension];
       Lower_Bounds(number_function, dimension, lb);
       Upper_Bounds(number_function, dimension, ub);

        for(i=0; i<dimension*10; i++){ successful[i] = 0; }
        //indivíduo inicial
        if(lb != NULL && ub!=NULL){
            for(i=0; i<dimension; i++){
                x[i] = (ub[i] - lb[i])*(rand()%10)*0.01 + lb[i]*0.01;
             //   cout<<x[i]<<"   ";
            }
            //cout<<endl;
        }
        else{ for(i=0; i<dimension; i++){ x[i] = (rand()%10)*0.01; } }
        objective_function = Compute_Function(x, dimension, number_function);
        stop++;

        int es = 0, ps  = 0, criteria = Number_Evaluations(number_function);
        int t=0, stop=0;

        while(stop < criteria){
            success=false;
            //regra de 1/5 de sucessos
            if(t%dimension == 0 && t>=dimension*10){
                double sum=0, ps;
                for(i=0; i<dimension*10; i++){sum += successful[i]; }
                ps = sum/10*dimension;
                if(ps > 1/5){ desvio_padrao = desvio_padrao/0.85;}
                if(ps < 1/5){ desvio_padrao = desvio_padrao*0.85; }
            }
            double y[dimension];
            for(i=0; i<dimension; i++){
                y[i] = x[i] + Normal_distribuition(0, desvio_padrao*desvio_padrao);
                if(lb != NULL && ub != NULL){
                    if(y[i] < lb[i]){ y[i] = x[i]; }
                    if(y[i] > ub[i]){ y[i] = x[i]; }
                }
            }
            double aux = Compute_Function(y, dimension, number_function); stop++;
            if(aux < objective_function){
                objective_function = aux;
                for(i=0; i<dimension; i++){ x[i] = y[i]; }
                successful[(t+1)%(dimension*10)] = 1;
                success = true;
            }
            else{ successful[(t+1)%(dimension*10)] = 0;}

            if(!success){
                es++;
                bool exit = false;
                for(i=0; i<2*dimension && stop < criteria; i++){
                        if(Exploratory_Moves(pattern[i],delta, x, objective_function, dimension, number_function, lb, ub)){
                            delta = 1.5*delta;
                            //exit = false;
                            objective_function = Compute_Function(x, dimension, number_function); stop++;
                        }
                        else{ delta = (0.5)*delta; exit = true; }
                }
                if(exit)ps++;
            }
            t = t+1;
        }
        cout<<"AVALIACOES DA FUNCAO OBJETIVO ------- "<<stop<<endl;
        cout<<"NUMERO DE ITERACOES ----------------- "<<t<<endl;
        cout<<"ITERACOES SEM SUCESSO ES ------------ "<<es<<endl;
        cout<<"ITERACOES SEM SUCESSO PS ------------ "<<ps<<endl;
        cout<<"ITERACOES DE SUCESSO ---------------- "<<(t - es) + (es - ps)<<endl;

        delete []successful;
        for(i=0; i<2*dimension; i++){ delete []pattern[i]; }
        delete []pattern;
        if(lb != NULL && ub != NULL){
            delete []lb;
            delete []ub;
        }
    }
}

void VerificadorSolucao(double *x, int dimension, int number_function){
    if(x != NULL){
        double *lb = new double[dimension], *ub = new double[dimension];
        Lower_Bounds(number_function, dimension, lb);
        Upper_Bounds(number_function, dimension, ub);
        for(int i=0; i<dimension; i++){
            if(x[i] < lb[i]){ cout<<"Solucao nao-factivel "<<x[i]<<endl; break; }
            if(x[i] > ub[i]){ cout<<"Solucao nao-factivel"<<x[i]<<endl; break; }
        }
        delete []lb;
        delete []ub;
    }
}