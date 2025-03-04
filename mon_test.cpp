#include <iostream>
#include <fstream> // Pour la lecture et l'écriture des fichiers
#include "jeu.h"
using namespace std;

/* ios::in - Ouvre le fichier en mode lecture. Le fichier doit exister, 
   sinon l'ouverture échouera.
  
   ios::out - Ouvre le fichier en mode écriture. Si le fichier existe, 
   son contenu est effacé. Sinon, un nouveau fichier est créé.

    ios::app - Ouvre le fichier en mode ajout (append). Les données sont ajoutées 
    à la fin du fichier existant, sans effacer son contenu. Si le fichier 
    n'existe pas, un nouveau fichier est créé.

    ios::binary - Ouvre le fichier en mode binaire. Ce mode est utilisé pour 
    les fichiers binaires, comme les fichiers image, audio, etc.
 */

int test_main(){
    Grille g;
    // vector<vector<int>> v = restaure2(g, "save0.txt");
    // cout << "Bienvenue dans le 2048 ! \nParamètres\nCible: " 
    // <<  g.cible << "\nDimension de la grille: " << g.dimension << " x " << g.dimension 
    // << "\nProportion: " << g.proportion << endl << endl ;
    
    // for(size_t i=0; i<v.size(); i++){
    //     for(size_t j=0; j<v.at(i).size(); j++){
    //         cout << v.at(i).at(j) << " ";
    //     }
    //     cout << endl;
    // }
    restaure(g, "save0.txt");
    affiche(g);
    int D =droite(g);
    //cout<< coordonnees_cases_vides(g)<<endl;
    place(g);
    affiche(g);
    droite(g);
    //g.table.at(place(g));
    cout<< droite(g)<<endl;
    affiche(g);
    bas(g);
    affiche(g);
    gauche(g);
    affiche(g);
    haut(g);
    affiche(g);
    return 0;
}
/*
int sauveur(){
    cout << "Dans le test...";
    
    string filename = "save1.txt";
    vector<string> data;
    string line;

    Grille g;
    init(g, 6, 4096, 7);

    // Ecriture dans le fichier    
    ofstream write_file(filename);
    if(!write_file){
        cout << "Fichier introuvable";
    }
    write_file << g.cible << endl;
    write_file << g.dimension << endl;
    write_file << g.proportion << endl;
    vector<vector<int>> v = g.table;
    int dim = g.dimension;

    for(size_t i=0; i<dim; i++){
        // string contenu_grille = "";
        for(size_t j=0; j<dim; j++){
            write_file << v.at(i).at(j) << " ";
        }
        write_file << endl;
    }
    write_file.close();

    // Lecture du fichier ligne par ligne
    ifstream read_file(filename, ios::in);
    if(!read_file) {
    cout << "Fichier introuvable!";
    }
    while(getline(read_file, line)) {
        data.push_back(line);
    }
    read_file.close();
    
    // Affichage du contenu
    cout << "Contenue du fichier\n";
    for(size_t i=0; i<data.size(); i++){
        cout << data.at(i) << endl;
    }
    return 0;
}

int restaureur(){
    string filename = "save1.txt";
    Grille g;

    string line;
    vector<string> data;

    // Lecture du fichier ligne par ligne
    ifstream read_file(filename, ios::in);
    if(!read_file) {
    cout << "Fichier introuvable!";
    }
    while(getline(read_file, line)) {
        data.push_back(line);
    }
    read_file.close();

    // Affichage du contenu
    cout << "Contenue du fichier\n";
    for(size_t i=0; i<data.size(); i++){
        cout << data.at(i) << endl;
    }

    int cible = stoi(data.at(0));
    int prop = stoi(data.at(2));
    vector<vector<int>> v;

    for(size_t i=3; i<data.size(); i++){
        v.push_back(string_a_vector(data.at(i)));
    }

    charge(g, v, cible, prop);

    affiche(g);

    return 0;
}
*/