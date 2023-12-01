/*  Xavier Gandibleux
    Cross-Dock Assignement Problem (CDAP)
    2023

    Materiel pour le projet :
    - parser d'instances
    - affichage d'une instance
    - liberation de la memoire allouee dynamiquement pour une instance
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// structures de donnees ------------------------------------------------------

// parametres d'une instance numerique
struct Parametres {
    string  fname;
    int     M, I, J, N;  // #fournisseurs, #quais en entree, #quais en sortie, #magasins 
    int **  flot;        // matrice de nombre de palettes prevu de m a n
    int **  dist;        // matrice de distance entre quai i et j
    int *   s;           // vecteur de nombre de palettes sortant des m fournisseurs
    int *   S;           // vecteur de capacite des i quais en entree du terminal
    int *   r;           // vecteur de nombre de palettes entrant dans les n magasins
    int *   R;           // vecteur de capacite des j quais en sortie du terminal
};

// prototypes -----------------------------------------------------------------
Parametres CDAPparser(string fname);
void CDAPafficheInstance(Parametres instance);
void CDAPlibereMemoire(Parametres instance);   


// ============================================================================
// point d'entree principal 

int main()
{
    struct Parametres instance;
    string fname;

    fname = "SetA_8x4S5.txt";
    instance = CDAPparser(fname);
    CDAPafficheInstance(instance);
    CDAPlibereMemoire(instance);   

    return 0;
}

// ============================================================================
// parser d'instances

Parametres CDAPparser(string fname)
{
    struct Parametres instance;

    instance.fname = fname;

    ifstream fichier(fname, ios::in); 
    if(fichier)  // pas de probleme rencontre lors de l'ouverture du fichier
    {       
        // 4 scalaires --------------------------------------------------------
        fichier >> instance.M; 
        fichier >> instance.I; 
        fichier >> instance.J; 
        fichier >> instance.N; 

       // matrice flots -------------------------------------------------------
        instance.flot = (int **) malloc(instance.M * sizeof(int*));
        for (int m=0; m<instance.M; m++)                                                             
            instance.flot[m] = (int *) malloc(instance.N * sizeof(int));  

        for (int m=0; m<instance.M; m++)
            for (int n=0; n<instance.N; n++)
                fichier >> instance.flot[m][n]; 

        // matrice distances --------------------------------------------------
        instance.dist = (int **) malloc(instance.I * sizeof(int*));
        for (int i=0; i<instance.I; i++)  
            instance.dist[i] = (int *) malloc(instance.J * sizeof(int));  

        for (int i=0; i<instance.I; i++)
            for (int j=0; j<instance.J; j++)
                fichier >> instance.dist[i][j];              

        // vecteur du nombre de palettes entrantes depuis un fournisseur ------
        instance.s = (int *) malloc(instance.M * sizeof(int));
        
        for (int m=0; m<instance.M; m++)
            fichier >> instance.s[m]; 

        // vecteur des capacites des quais entrants ---------------------------
        instance.S = (int *) malloc(instance.I * sizeof(int));
   
        for (int i=0; i<instance.I; i++)
            fichier >> instance.S[i]; 

        // vecteur du nombre de palettes sortantes vers un magasin ------------
        instance.r = (int *) malloc(instance.N * sizeof(int));
   
        for (int n=0; n<instance.N; n++)
            fichier >> instance.r[n]; 
  
        // vecteur des capacites des quais sortants ---------------------------
        instance.R = (int *) malloc(instance.J * sizeof(int));
   
        for (int j=0; j<instance.J; j++)
            fichier >> instance.R[j]; 
                       

        fichier.close();  
      
    }
    else  
        cerr << "Impossible d'ouvrir le fichier !" << endl;


    return instance;
}


// ============================================================================
// affichage de tous les parametres d'une instance numerique

void CDAPafficheInstance(Parametres instance)
{
    // nom de l'instance --------------------------------------------------
    cout << "\nfname : " << instance.fname 
         << endl;

    // 4 scalaires --------------------------------------------------------
    cout << "(M) " << instance.M 
         << "  (I) " << instance.I 
         << "  (J) " << instance.J 
         << "  (N) " << instance.N 
         << endl << endl;

    // matrice flots -------------------------------------------------------
    for (int m=0; m<instance.M; m++)
        for (int n=0; n<instance.N; n++)
            cout << m << " " << n << " " << instance.flot[m][n] << endl;
    cout << endl;

    // matrice distances --------------------------------------------------
    for (int i=0; i<instance.I; i++)
        for (int j=0; j<instance.J; j++)
            cout << i << " " << j << " " << instance.dist[i][j] << endl;              
    cout << endl;

    // vecteur du nombre de palettes entrantes depuis un fournisseur ------
    for (int m=0; m<instance.M; m++)
        cout << m << " " << " " << instance.s[m] << endl;              
    cout << endl;    

    // vecteur des capacites des quais entrants ---------------------------
    for (int i=0; i<instance.I; i++)
        cout << i << " " << " " << instance.S[i] << endl;             
    cout << endl; 

    // vecteur du nombre de palettes sortantes vers un magasin ------------
    for (int n=0; n<instance.N; n++)
        cout << n << " " << " " << instance.r[n] << endl;             
    cout << endl;    

    // vecteur des capacites des quais sortants ---------------------------
    for (int j=0; j<instance.J; j++)
       cout << j << " " << " " << instance.R[j] << endl;               
    cout << endl;                         
}


// ============================================================================
// libere proprement la memoire allouee dynamiquement pour une instance

void CDAPlibereMemoire(Parametres instance)
{
    for (int m=0; m<instance.M; m++)  
        delete instance.flot[m];
    for (int i=0; i<instance.I; i++)  
        delete instance.dist[i];
    delete instance.s;
    delete instance.S;
    delete instance.r; 
    delete instance.R;
}
