// modeleCanevas.cpp

#include "gurobi_c++.h"
using namespace std;

int
main(int argc, char *argv[])
{
    // Instance ===============================================================
    
    const int M   = 2;
    const int I   = 2;
    const int J   = 2;
    const int N   = 2;   

    int flot[][N] = { {20, 6},	
                      {3, 10}
                    };
    int dist[][N] = { {8, 9},	
                      {9, 8}
                    };     

    int s[ ]      = { 26, 13};	
    int S[ ]      = { 46, 46};
    int r[ ]      = { 23, 16};	
    int R[ ]      = { 46, 46};                                   	
/*
    const int M   = 8;
    const int I   = 4;
    const int J   = I;
    const int N   = M;    

    int flot[][N] = { {0,	0,	26,	0,	0,	0,	0,	0},	
                      {22,	0,	0,	0,	0,	0,	0,	0},	
                      {41,	32,	0,	50,	30,	0,	0,	0},	
                      {0,	0,	0,	0,	10,	31,	0,	0},	
                      {40,	0,	0,	44,	0,	0,	50,	0},	
                      {0,	47,	0,	31,	0,	0,	0,	0},	
                      {0,	0,	0,	0,	43,	0,	0,	0},	
                      {0,	44,	31,	0,	0,	0,	0,	31}
                    };

    int dist[][J] = { {8,	9,	10,	11},	
                      {9,	8,	9,	10},	
                      {10,	9,	8,	9},	
                      {11,	10,	9,	8}
                    };	

    int s[ ]      = { 26, 22, 153, 41, 134, 78, 43, 106};	

    int S[ ]      = { 166, 166, 166, 166 };
    
    int r[ ]      = { 103, 123, 57, 125, 83, 31, 50, 31};	

    int R[ ]      = { 166, 166, 166, 166 };
                                 
*/

    // Create an environment ==================================================

    GRBEnv env = GRBEnv(true);
    env.set("LogFile", "modF1.log");
    env.start();

    // Create an empty model
    GRBModel model = GRBModel(env);
    model.set(GRB_StringAttr_ModelName, "modF1");


    // Allocate dynamically the memory and create the variables ===============

    // the 4 dimensional variables : z_{m,i,n,j}

    GRBVar ****z = new GRBVar***[M];
    for (int m=0; m<M; m++)
    {
        z[m] = new GRBVar**[I];
        for (int i=0; i<I; i++)
        {
            z[m][i] = new GRBVar*[N];
            for (int n=0; n<N; n++)
            {
                z[m][i][n] = new GRBVar[J];
            }
        }
    }


    // the 2 dimensional variables : x_{m,i}

    GRBVar **x = new GRBVar*[M];
    for (int m=0; m<M; m++)
        x[m] = new GRBVar[I];


    // the 2 dimensional variables : y_{n,j}

    GRBVar **y = new GRBVar*[N];
    for (int n=0; n<N; n++)
        y[n] = new GRBVar[J];                                                       


    // Set objective ==========================================================

    // ...


    // Add assigment constraints ==============================================

    // constraints (1.1)

    // ...

    // constraints (1.2)

    // ...


    // Add knapsack constraints ===============================================

    // constraints (1.3)

    // ...

    // constraints (1.4)

    // ...


    // Add linearization constraints ==========================================

    // constraints (2.1)

    // ...

    // constraints (2.2)

    // ...

    // constraints (2.3)

    // ...                                  

    model.write("modF1.lp");


    // Optimize model =========================================================

    // ...



    // Get results ============================================================

    // ...


    // Desallocate the memory =================================================

    for (int m=0; m<M; m++)
        for (int i=0; i<I; i++) 
            for (int n=0; n<N; n++) 
                delete[] z[m][i][n];
    for (int m=0; m<M; m++)
        for (int i=0; i<I; i++)  
            delete[] z[m][i]; 
    for (int m=0; m<M; m++)
        delete[] z[m]; 
    delete[] z;

    for (int m=0; m<M; m++)
        delete[] x[m];
    delete[] x;    

    for (int n=0; n<N; n++)
        delete[] y[n];
    delete[] y;

  return 0;
}
