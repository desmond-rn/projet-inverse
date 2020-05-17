
#ifndef INCLUDED_SOLVER
#define INCLUDED_SOLVER

#include <vector>
#include <fstream>

#include "mesh.hpp"

/************************************************
 * Classe pour resoudre le probleme
 */
class Solver{
    public:
        // Maillage des volumes finis pour le probleme
        Mesh *mesh;

        // Parametres physiques
        double c;                   // Vitesse de la lumiere
        double a;                   // Constante de Stefen-Boltzmann

        // Propriete du domaine
        double C_v;                 // Capacite calorifique a volume constant

        // Parametres du probleme
        double CFL;                 // Condition CFL: dt=CFL*dx/c
        double epsilon;             // Precision sur les calculs
        double t_final;             // Temps de la simulation

        // Autres proprietes du domaine
        std::string rho_expr;           // Expression de la densite du domaine
        std::string sigma_a_expr;       // Expression de l'opacite d'absorption
        std::string sigma_c_expr;       // Expression de l'opacite de scatering

        // Energies des photons
        std::vector<double> E;              // Solution du probleme: E(x, t)
        std::string E_init_expr;            // Au temps initial E(x, 0)
        std::vector<double> E_left;         // Sur le bord gauche: E(x_0, t)
        std::vector<double> E_right;        // Sur le bord droit: E(x_N, t)

        // Flux de photons
        std::vector<double> F;              // Solution du problme: F(x, t)
        std::string F_init_expr;            // Au temps initial F(x, 0)
        std::vector<double> F_left;         // Sur le bord gauche: F(x_0, t)
        std::vector<double> F_right;        // Sur le bord droit: F(x_N, t)

        // Temperatures du milieux
        std::vector<double> T;              // Solution du problme: T(x, t)
        std::string T_init_expr;            // Au temps initial T(x, 0)
        std::vector<double> T_left;         // Sur le bord gauche: T(x_0, t)
        std::vector<double> T_right;        // Sur le bord droit: T(x_N, t)

        // Fichiers ou sont exportes les donnees
        std::string export_1;            // Signaux en tout temps aux bords
        std::string export_2;            // Signaux au temps final en tout x

        // Autres parametres du probleme
        double dt;                      // Pas de temps
        int step_count;                 // Nombre d'iterations en temps
        std::vector<double> time_steps; // Les temps a chaque pas

        /***************
         * Constructeur
         * @param doubles: les parametres qui sont doubles dans l'ordre ci-haut
         * @param strings: les autres parametres (expressions pour creer les fonctions, et noms des fichiers pour les exports)
         */
        Solver(Mesh *new_mesh, double *doubles, std::string *strings);

        /***************
         * Fonction pour calculer rho a partir de son expression rho_expr
         */
        double rho(double x);

        /***************
         * Fonction pour calculer sigma_a
         */
        double sigma_a(double rho, double T);

        /***************
         * Fonction pour calculer sigma_c
         */        
        double sigma_c(double rho, double T);

        /***************
         * Calcule E(x, 0), energie a la position x au temps initial
         */ 
        double E_init(double x);

        /***************
         * Calcule F(x, 0)
         */ 
        double F_init(double x);

        /***************
         * Calcule T(x, 0)
         */ 
        double T_init(double x);

        /***************
         * Resout le probleme et exporte les resultats au fur et a mesure
         */
        void solve();

        /***************
         * Affiche les resultats sur la console
         */
        void display();

        /***************
         * Exporte les resultats en tout temps aux bords du domaine
         */
        void export_temporal();

        /***************
         * Exporte les resultats sur tout le domaine au temps final
         */
        void export_spatial();

        /***************
         * Destructeur vide
         */
        virtual ~ Solver(){};
};

#endif
