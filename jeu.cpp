#include "jeu.h"
#include <iomanip> // pour setw dans affichage
#include <fstream> // Pour la lecture et l'écriture des fichiers
#include <iostream>
using namespace std;

/* Fonctions auxiliaires*/

vector<vector<size_t>> coordonnees_cases_vides( Grille &g){
  vector<vector<size_t>> res;

  if(vides(g) == 0) {
    return {};
  }

  for(size_t i=0; i<g.table.size(); i++){
    for(size_t j=0; j<g.table.at(i).size(); j++){
      if(g.table.at(i).at(j) == 0) {
        res.push_back({i,j});
      }
    }
  }

  return res;
}

bool ajoute_tuile(Grille &g){
  if(coordonnees_cases_vides(g).size() == 0) {
    return false;
  }    

  int n = place(g) - 1;
  // Accède à la n-ième case vide de g et met 2 ou 4 dedans
  g.table.at(coordonnees_cases_vides(g).at(n).at(0)).at(coordonnees_cases_vides(g).at(n).at(1)) = nouvelle(g);
  return true;
}

// retourne a à la puissance n
int pow(int a, int n){
  if(n == 0){ return 1;}
  if (n == 1) { return a; }
  return a * pow(a, n-1);
}

// Renvoie true si n est une puissance de 2 et false sinon
bool puissance_de_2(int n) {
  if (n%2 != 0) {
    return false;
  }

  int i = 0;
  while(n >= pow(2, i)){
    if(pow(2, i) == n) { return true; }
    i++;
  }
  return false;
}

// Fonction pour personnaliser les paramètres par le joueur
void personnaliser_parametres(Grille &g){
  cout << "\n\n=========== Personnalisation des paramètres ===========";
  cout << "\nEntre la valeur désirée pour chaque paramètre!" << endl;
  
  // Pour la cible
  int cible; 
  cout << "Entre la cible (valeur à atteindre pour gagner): ";
  cin >> cible;

  // Si ce n'est pas une puissance de 2 
  // ou si c'est plus petit que 4, rejette la valeur
  while((cible <= 4) or (not puissance_de_2(cible))) {
    cout << "Invalide! La cible doit être une puissance de 2 supérieure à 4. " << endl;
    cout << "Entre la cible (valeur à atteindre pour gagner): ";
    cin >> cible;
  } 

  // Pour la dimension
  int dim; 
  cout << "Entre la dimension de la grille: ";
  cin >> dim;
  while((dim < 2) or (dim > 10)) {
    cout << "Invalide! La dimension doit être un entier entre 2 et 10!" << endl;
    cout << "Entre la dimension de la grille: ";
    cin >> dim;
  } 

  // Pour la proportion
  int proportion; 
  cout << "Entre la probabilité pour 2 (entre 0 et 10): ";
  cin >> proportion;

  while((proportion < 0) or (proportion > 10)) {
    cout << "Invalide! La proportion doit être un entier entre 0 et 10!" << endl;
    cout << "Entre la probabilité pour 2 (entre 0 et 10): ";
    cin >> proportion;
  } 

  // initialise la grille avec les valeurs de l'utilisateur
  init(g, dim, cible, proportion);
}

// Fonction auxiliaire pour transformer chaque ligne 
// de nombres (dans un string) en un vecteur de nombre
vector<int> string_a_vector(const string &str) {
  vector<int> valeurs;
  string numStr;

  for (size_t i=0; i<str.size(); i++) {
    char c = str.at(i);
    if (c == ' ') {
      if (not numStr.empty()) {
        valeurs.push_back(stoi(numStr));
        numStr=""; 
      }
    } else {
      numStr.push_back(c);
    }
  }
  if (not numStr.empty()) {
    valeurs.push_back(stoi(numStr));
  }
  return valeurs;
}

/* Les definitions actuelles des fonctions servent uniquement à ce que le
 * compilateur ne râle pas. Il faut bien sur écrire le code de ces fonctions
 */

int vides(const Grille &g) { 
  int res = 0; 
  for(size_t i=0; i<g.table.size(); i++){
    for(size_t j=0; j<g.table.at(i).size(); j++){
      if(g.table.at(i).at(j) == 0) {
        res ++;
      }
    }
  }
  return res; 
}

// renvoie la proportion de tuiles 2 au tirage, exprimée
// par un entier entre 0 et 10 (/ 10)
int proportion(const Grille &g) { 
  return g.proportion;
}

// renvoie la valeur à atteindre pour gagner
int cible(const Grille &g)  { 
  int res = g.cible;
  return res; 
}

// renvoie la dimension de la grille
int dimension(const Grille &g)  { 
  return g.dimension; 
}

int score(const Grille &g)  { 
  int res = g.score;
  return res;
}

bool succes(const Grille &g) { 
  for(size_t i=0; i<g.table.size(); i++){
    for(size_t j=0; j<g.table.at(i).size(); j++){
      if(g.table.at(i).at(j) == cible(g)) {
        return true;
      }
    }
  }
  return false; 
}

bool init(Grille &g, int dimension, int cible, int proportion) {
  if((dimension < 2) or (cible <= 4) or (not puissance_de_2(cible)) or (proportion < 0) or (proportion > 10)){
    return false;
  }

  g.table.clear();
  g.dimension = dimension;
  g.proportion = proportion;
  g.cible = cible;
  g.score = 0;
  vector<int> ligne(dimension, 0);

  for(int i=0; i<dimension; i++){
    g.table.push_back(ligne);
  }
  
  for(int i=0; i<2; i++){
    if(not ajoute_tuile(g)){
      return false;
    };
  }
  return true;
}

// Ne pas oublier de vérifier la validité des paramètres !
bool charge(Grille &g, vector<vector<int>> &v, int cible, int proportion) {
  size_t dim = v.size();
  if((dim < 4) or (cible <= 4) or (not puissance_de_2(cible)) or (proportion < 0) or (proportion > 10)){
    return false;
  }

  for(size_t i=0; i<dim; i++){
    if(v.at(i).size() != dim){
      return false;
    }
  }
  
  g.table.clear();
  g.dimension = dim;
  g.proportion = proportion;
  g.cible = cible;
  g.score = 0;
  g.table = v;

  return true;
}


int droite(Grille &g)  {   
  int res = -1; 
  int dim = dimension(g);
  int j1=0;
    for(size_t i=0; i<dim; i++){
      // Décaler vers la droite
      for(int j=dim-1; j>0; j--){
        int k=0;
        // Si la case n'est pas vide, on la décale vers la droite
        // Fusionner
        if(g.table.at(i).at(j) != 0){
          j1=j;
          do{ 
            k+=1;
          } while(k<j and g.table.at(i).at(j1-k)!= g.table.at(i).at(j) and g.table.at(i).at(j1-k)==0 );
           if(g.table.at(i).at(j-k) == g.table.at(i).at(j)){
              g.table.at(i).at(j) = 2*g.table.at(i).at(j-k);
              g.score+=g.table.at(i).at(j);
              g.table.at(i).at(j-k) = 0 ;
              j-=k;
              res=1;
           }
        }  
      }
      //decaler 
      for(int j=dim-2; j>=0; j--){
        // Si la case n'est pas vide, on la décale vers la droite
        if(g.table.at(i).at(j) != 0){
          for(size_t k=1; k<dim-j; k++){
            if(g.table.at(i).at(j+k) == 0){
              g.table.at(i).at(j+k) =  g.table.at(i).at(j+k-1);
              g.table.at(i).at(j+k-1) = 0;
              res=1;
            } else{
              break;
            }
          }      
        }
      }
    }
  if (res!=-1){
    res=vides(g);
}
  return res;
}

int gauche(Grille &g) {
  int res = -1; 
  int dim = dimension(g);
  int j1=0;
    for(size_t i=0; i<dim; i++){
      // Décaler vers la droite
      for(size_t j=0; j<dim-1 ; j++){
        int k=0;
        // Si la case n'est pas vide, on la décale vers la droite
        // Fusionner
        if(g.table.at(i).at(j) != 0){
          j1=j;
          do{
            k+=1;
          } while(k<dim-j-1 and g.table.at(i).at(j+k)==0 and g.table.at(i).at(j+k)!=g.table.at(i).at(j));
          if(g.table.at(i).at(j+k) == g.table.at(i).at(j)){
                g.table.at(i).at(j) = 2*g.table.at(i).at(j+k);
                g.score+=g.table.at(i).at(j);
                g.table.at(i).at(j+k) = 0 ;
                j+=k;
                res=1;
          }
        }  
      }
      //decaler 
      for(int j=1; j<dim; j++){
        // Si la case n'est pas vide, on la décale vers la gauche
        if(g.table.at(i).at(j) != 0){
          for(size_t k=1; k<=j; k++){
            if(g.table.at(i).at(j-k) == 0){
              g.table.at(i).at(j-k) =  g.table.at(i).at(j-k+1);
              g.table.at(i).at(j-k+1) = 0;
              res=1;
            } else{
              break;
            }
          }      
        }
      }
    }
  if (res!=-1){
    res=vides(g);    
}
  return res;
}

int haut(Grille &g)    {
  int res = -1; 
  int dim = dimension(g);
  int j1=0;
    for(size_t i=0; i<dim; i++){
      // Décaler vers la droite
      for(size_t j=0; j<dim-1 ; j++){
        int k=0;
        // Si la case n'est pas vide, on la décale vers la droite
        // Fusionner
        if(g.table.at(j).at(i) != 0){
          j1=j;
          do{
            k+=1; 
          }while(k<dim-j-1 and g.table.at(j+k).at(i)==0 and g.table.at(j+k).at(i)!= g.table.at(j).at(i));
         if(g.table.at(j+k).at(i) == g.table.at(j).at(i)){
            g.table.at(j).at(i) = 2*g.table.at(j+k).at(i);
            g.score+=g.table.at(j).at(i);
            g.table.at(j+k).at(i) = 0 ;
            j+=k;
            res=1; 
        } } 
      }
      //decaler 
      for(int j=1; j<dim; j++){
        // Si la case n'est pas vide, on la décale vers la gauche
        if(g.table.at(j).at(i) != 0){
          for(size_t k=1; k<=j; k++){
            if(g.table.at(j-k).at(i) == 0){
              g.table.at(j-k).at(i) =  g.table.at(j-k+1).at(i);
              g.table.at(j-k+1).at(i) = 0;
              res=1;
            } else{
              break;
            }
          }      
        }
      }
    }
  if (res!=-1){
    res=vides(g);  
}
  return res;
}

int bas(Grille &g)  {   
  int res = -1; 
  int dim = dimension(g);
  int j1=0;
    for(size_t i=0; i<dim; i++){
      // Décaler vers la droite
      for(int j=dim-1; j>0; j--){
        int k=0;
        // Si la case n'est pas vide, on la décale vers la droite
        // Fusionner
        if(g.table.at(j).at(i) != 0){
          j1=j;
          do{ 
            k+=1;
          } while(k<j and g.table.at(j-k).at(i)== 0 and g.table.at(j-k).at(i) == g.table.at(j).at(i));
          if(g.table.at(j-k).at(i) == g.table.at(j).at(i)){
            g.table.at(j).at(i) = 2*g.table.at(j-k).at(i);
            g.score+=g.table.at(j).at(i);
            g.table.at(j-k).at(i) = 0 ;
            j-=k;
            res=1;
          }
        }  
      }
      //decaler 
      for(int j=dim-2; j>=0; j--){
        // Si la case n'est pas vide, on la décale vers la droite
        if(g.table.at(j).at(i) != 0){
          for(size_t k=1; k<dim-j; k++){
            if(g.table.at(j+k).at(i) == 0){
              g.table.at(j+k).at(i) =  g.table.at(j+k-1).at(i);
              g.table.at(j+k-1).at(i) = 0;
              res=1;
            } else{
              break;
            }
          }      
        }
      }
    }
  if (res!=-1){
    res=vides(g);   
}
  return res;
}

/* Pour les extensions éventuelles */
void sauve(const Grille &g, string filename) {
  vector<string> data;
  string line;
  filename.append(".txt");

  // Ouverture du fichier   
  ofstream write_file(filename);
  if(!write_file){
    cout << "\nSauvegarde impossible! Réessaye!\n";
  }
  
  // Ecriture des parametres
  write_file << g.cible << endl;
  write_file << g.dimension << endl;
  write_file << g.proportion << endl;
  write_file << g.score << endl;
  vector<vector<int>> v = g.table;
  int dim = g.dimension;

  // Ecriture de la grille
  for(size_t i=0; i<dim; i++){
    for(size_t j=0; j<dim; j++){
      write_file << v.at(i).at(j) << " ";
    }
    write_file << endl;
  }
  write_file.close();
  cout << "\nFichier sauvegardé avec succès!\n";
}

void restaure(Grille &g, string filename) {
  string line;
  vector<string> data;

  // Lecture du fichier ligne par ligne
  ifstream read_file(filename, ios::in);
  if(!read_file) {
    cout << "\nFichier introuvable! Restauration impossible!\n";
    exit(1);
  }
  
  while(getline(read_file, line)) {
    data.push_back(line);
  }
  read_file.close();

  int cible = stoi(data.at(0));
  int dimension = stoi(data.at(1));
  int prop = stoi(data.at(2));

  // Récupération de l'état de la grille
  vector<vector<int>> v;
  for(size_t i=4; i<data.size(); i++){
    v.push_back(string_a_vector(data.at(i)));
  }

  // Chargement du jeu
  charge(g, v, cible, prop);
  g.score = stoi(data.at(3));
  cout << "\nChargement effectué avec succès!\n";
}

/*
 * 		Fonctions mise à disposition. Pas de raison d'y toucher !
 *	Rappel: la fonction main() est dans le fichier test.cpp
 */	

void affiche (const Grille &g) {
  int i, j, k;
  int max = dimension(g);
  cout << endl << " \t ";
  for(k = 0; k < (6+1)*max-1; k = k+1) { cout << "-"; }
  cout << endl;
  /* Verifier si on veut que la ligne du haut soit 0 ou max-1 */
  for(i = 0; i < max; i = i+1) {
    cout << "\t|";
    for(j=0; j < max; j=j+1) {
      if(g.table.at(i).at(j) == 0) {
	cout << "      |";
      } else { cout << " " << setw(4) << g.table.at(i).at(j) << " |" ; }
    }
    if (i != max-1) {
      cout << endl << "\t|";
      for(k = 0; k < (6+1)*max-1; k = k+1) { cout << "-"; }
      cout << "|" << endl;
    } else {
      cout << endl << "\t ";
      for(k = 0; k < (6+1)*max-1; k = k+1) { cout << "-"; }
      cout << endl;
    }
  }
  cout << endl << "Score: " << score(g) << ", Vides: " << vides(g) << endl;
}

/* Fonction auxiliaire pour gérer une partie de jeu */
void partie(Grille &g){
  char mouvement;
  int mvt_reussi;
  string filename;

  cout << "======== Début de la partie ======== \n";
  affiche(g);

  while(not succes(g)){
    cout << "A tout moment du jeu, tu as l'option de sauvegarder ta partie (en tapant s)\n"
    << "Tu peux aussi quitter la partie sans la sauvegarder (en tapant q)\n"
    << "\nTape i(haut), j(gauche), k(bas), ou l(droite)\nMouvement: ";
    cin >> mouvement;
    while((mouvement != 'i') and (mouvement != 'j') and (mouvement != 'k') and (mouvement != 'l') and (mouvement != 's') and (mouvement != 'q')){
      cout << "Invalide! Tape i(haut), j(gauche), k(bas), ou l(droite), ou s(sauvegarde) ou q(quitter) \nMouvement: ";
      cin >> mouvement;
    }

    switch (mouvement) {
    case 'i':
      mvt_reussi = haut(g);
      break;
    case 'j':
      mvt_reussi = gauche(g);
      break;
    case 'k':
      mvt_reussi = bas(g);
      break;
    case 'l':
      mvt_reussi = droite(g);    
      break;
    case 'q':
      cout << "Partie abandonnée! T'as perdu!";
      exit(0);
    case 's':
      cout << "\n\nSauvegarde de la partie!\n"
      << "Entre le nom de la sauvegarde! Evite les espaces et caractères spéciaux: ";
      cin >> filename;
      sauve(g, filename);
      exit(0);
    }
    affiche(g);

    // Test si le joueur a gagné
    if(succes(g)){
      cout << "T'as gagné!"<<endl;
      break;
    }

    bool temp = ajoute_tuile(g);
    // Si le mvt n'a pas été effectué, on teste si on ne peut pas ajouter
    // de tuile dans ce cas le joueur a perdu
    if (mvt_reussi == -1) {
      if(not temp){
        affiche(g);
        cout << "T'as Perdu!" <<endl;
        exit(0);
      }
    }
  }
}
