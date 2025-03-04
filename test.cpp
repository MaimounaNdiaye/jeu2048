#include "jeu.h"
#include <cassert>
# include <iostream>
using namespace std;


/* Quelques fonctions de test mises à disposition.
 * Elles sont lancées par la fonction testFV qui est elle-même lançable
 * dans la fonction main()à située en fin de fichier.
 * Pour l'instant l'appel à cette fonction est mis en commentaire.
*/

void teste3() {
  Grille g;
  vector<vector<int>> v = { { 8, 4, 4, 4 }, { 4, 0, 4, 4 }, { 4, 4, 4, 4 }, { 4, 0, 0, 4} };
  cout << "Debut du test3\n";
  assert(charge(g, v, 32, 7)); // charge et teste le resultat
  affiche(g);

  gauche(g); affiche(g);
  droite(g); affiche(g);
  haut(g);   affiche(g);
  gauche(g); affiche(g);
  haut(g);   affiche(g);
  bas(g);    affiche(g);
  assert(succes(g));
  assert(score(g) == 128);
  assert(score(g) == 128 and succes(g));
  cout << "Teste3 OK" << endl;
}

void teste3bis() {
  Grille g;
  vector<vector<int>> v =
    { { 2, 4, 0, 0, 4 }, { 4, 0, 4, 8, 8 }, { 0, 0, 4, 0, 4 }, { 2, 4, 0, 0, 4},
      { 2, 4, 0, 4, 2 }
    };
  cout << "Debut du teste3bis" << endl;
  assert(charge(g, v, 64, 10)); // avec que des tuiles de valeur 2
  affiche(g);
  
  gauche(g); affiche(g);
  assert(score(g) == 56 and gauche(g) == -1);
  cout << "teste3bis-I: OK" << endl;
  // On repart de la meme configuration initiale mais on essaye
  // un autre deplacement
  Grille g2;
  assert(charge(g2, v, 8, 0));
  affiche(g2);
  
  haut(g2);   affiche(g2);
  bas(g2);    affiche(g2);
  droite(g2); affiche(g2);
  assert(score(g2) == 68 and vides(g2) == 16);
  cout << "teste3bis-II: OK" << endl;
  cout << "Fin de teste3bis" << endl;
}

void teste4() {
  Grille g;
  vector<vector<int>> v =
  // une grille bloquée.
    { { 128, 8, 2, 4 }, { 4, 16, 4, 8 }, { 8, 2, 8, 4}, { 2, 4, 16, 32} };
  cout << "Debut du test4" << endl;
  assert(charge(g, v, 2048, 7));
  affiche(g);
  
  assert(gauche(g) == -1 and droite(g) == -1 and
	 haut(g)   == -1 and droite(g) == -1);
  affiche(g);
  cout << "Teste4 OK" << endl;
}

void teste5() {
  Grille g;
  cout << "Debut du test5" << endl;
  assert(init(g, 5, 8, 0)); // on ne cree que des tuiles de valeur 4
  affiche(g);
  
  haut(g);   affiche(g);
  droite(g); affiche(g);
  assert(score(g) == 8 and succes(g));
  cout << "Teste5 OK" << endl;
}

void testFV() {
  teste3();
  teste3bis();
  teste4();
  teste5();
}

/* Nos tests */
void test_sauve_restaure1(){
  Grille g;
  vector<vector<int>> v ={ { 0, 8, 8, 4, 32 }, { 0, 16, 16, 4, 32 }, { 0, 2, 0, 4, 0}, { 2, 0, 16, 4, 0}, {2, 4, 0, 0, 0} };
  vector<vector<int>> v2 ={ { 0, 0, 0, 0, 0 }, { 64, 0, 0, 0, 0 }, { 32, 0, 0, 0, 0}, { 32, 2, 0, 0, 0}, {4, 16, 4, 0, 0} };
  
  charge(g, v, 1024, 5);
  g.score = 116;  affiche(g);
  bas(g); haut(g); gauche(g); bas(g); bas(g); haut(g);
  droite(g); bas(g); gauche(g);gauche(g); affiche(g);
  sauve(g, "test_sauve_restaure");
  Grille g2;
  restaure(g2, "test_sauve_restaure.txt");
  affiche(g2);
  assert(g2.table == v2);
  assert(g2.score == 296);
  cout << "\nTest sauve restaure 1 OK\n";
}

void test_sauve_restaure2(){
  Grille g;
  vector<vector<int>> v ={ { 0, 8, 8, 4, 32 }, { 0, 16, 16, 4, 32 }, { 0, 2, 0, 4, 0}, { 2, 0, 16, 4, 0}, {2, 4, 0, 0, 0} };
  charge(g, v, 1024, 5); 
  cout << "Affichage g\n"; affiche(g);
  sauve(g, "test_sauve_restaure"); 
  Grille g2;
  restaure(g2, "test_sauve_restaure.txt"); 
  cout << "Affichage g2\n"; affiche(g2);
  assert((g2.table == g.table ) and (g2.score == g.score) and (g2.dimension == g.dimension));
  cout << "\nTest sauve restaure 2 OK\n";
}

/* A faire dans un second temps: petit menu pour exécuter les commandes de
 * l'utilisateur
*/
int interactif() {
  int pers = 0; char continuer = ' ';
  Grille g;
  init(g, 4, 2048, 8);

  // Choix du mode
  int mode;
  cout << "Bienvenue dans le 2048 ! " 
  << "Sélectionne le mode que tu veux\n\n" 
  << "1. Pour jouer au jeu (possibilité de personnaliser les paramètres)\n"
  << "2. Pour lancer un test spécifique \n3. Pour charger une partie existante\n\n" 
  << "Tape 1, 2 ou 3: ";

  cin >> mode;
  while((mode != 1) and (mode != 2) and (mode != 3)){
    cout << "Invalide! Tape 1, 2 ou 3: ";
    cin >> mode;
  }

  switch (mode)
  {
  case 1: // Partie de jeu normale (paramètres personnalisables)
    cout << "\n\nPartie de Jeu\n";
    cout << " \nVeux-tu jouer avec les paramètres classiques ou choisir tes paramètres?" 
    << "\nEntre 1 pour classique et 2 pour personnaliser\n"
    << "\n\nParamètres Actuels\nCible: " 
    <<  g.cible << "\nDimension de la grille: " << g.dimension << " x " << g.dimension 
    << "\nProportion: " << g.proportion
    << "\nEntre 1 ou 2: ";
    
    cin >> pers;
    while((pers != 1) and (pers != 2)){
      cout << "Invalide! Tape 1 pour une partie classque et 2 pour personnaliser les paramètres: ";
      cin >> pers;
    }
    
    if(pers == 2){
      personnaliser_parametres(g);
      cout << "\n\nParamètres\nCible: " 
      <<  g.cible << "\nDimension de la grille: " << g.dimension << " x " << g.dimension 
      << "\nProportion: " << g.proportion
      << "\nEntre 1 ou 2: ";
    }

    partie(g);
    break;
  
  case 2: // Lancer des tests
    do {
      int test_num;
      cout << "\n\nLancer un test\n\nQuel test veux-tu lancer?\n"
      << "1. test3\n2. test3bis\n3. test4\n4.test5\n5. testFV (lance tous les tests précédents) "
      << "\n6.test_sauve_restaure1 \n7.test_sauve_restaure2 \n8.lancer tous les tests"
      << "\n\nTape un chiffre de 1 à 8 pour chooisir le test: ";
      cin >> test_num;
      while((test_num > 8) or (test_num < 1)){
        cout << "\nInvalide! Entre une valeur entre 1 et 8: ";
        cin >> test_num;
      }

      switch (test_num)
      {
      case 1:
        teste3();
        break;
      case 2:
        teste3bis();
        break;
      case 3:
        teste4();
        break;
      case 4:
        teste5();
        break;
      case 5:
        testFV();
        break;
      case 6: 
        test_sauve_restaure1();
        break;
      case 7: 
        test_sauve_restaure2();
        break;
      case 8:
        testFV();
        test_sauve_restaure1();
        test_sauve_restaure2();
        break;
      }

      cout << "\nveux tu lancer un autre test ou terminer le programme?\n"
      << "Tape a pour continuer (toute autre lettre terminera le programme): ";
      cin >> continuer;
    } while(continuer == 'a');

    break;

  case 3: // Reprendre une partie existante
    string file;
    cout << "\n\nChargement d'une partie déjà existante\n\n";
    cout << "Entre le nom de la partie (nom du fichier avec extension): ";
    cin >> file; 
    Grille g;
    restaure(g, file); 
    partie(g);
    break;
  }
  return 0;
}

int main() {

  interactif();
  
  return 0;
}


