#include <iostream>
#include <string>
#include "listechainee.h"

// Affichage du menu
void afficherMenu() {
    std::cout << "\n=== Liste doublement chainee ===\n";
    std::cout << "1. Ajouter une valeur\n";
    std::cout << "2. Trouver une valeur\n";
    std::cout << "3. Supprimer une valeur\n";
    std::cout << "4. Compacter la liste\n";
    std::cout << "5. Afficher la liste\n";
    std::cout << "6. Quitter\n";
    std::cout << "Choix : ";
}

int main() {
    DoublyLinkedList list; // Création d’une instance de la liste chaînée
    int choix; // Stocke le numéro choisi dans le menu
    int valeur; // Stocke la valeur saisie par l'utilisateur


    while (true) {
        afficherMenu();

        // Vérifie la validité de l’entrée utilisateur
        if (!(std::cin >> choix)) {
            std::cout << "Entree invalide. Veuillez entrer un nombre.\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        // Gestion du choix
        switch (choix) {
        case 1: // Ajouter
            std::cout << "Entrez des valeurs a ajouter (tapez q pour terminer) :\n";

            while (true)
            {
                std::cout << "> ";

                // Lire sous forme de string pour pouvoir accepter 'q'
                std::string input;
                if (!(std::cin >> input)) {
                    break;
                }

                // L'utilisateur veut arrêter
                if (input == "q" || input == "Q") {
                    break;
                }

                // Tenter de convertir en entier
                try {
                    int value = std::stoi(input);
                    list.ajouter(value);
                    std::cout << "Ajoute.\n";
                }
                catch (const std::exception&) {
                    std::cout << "Entree invalide, utilisez un entier ou q pour quitter.\n";
                }
            }

            break;

        case 2:
            // Trouver une valeur
            std::cout << "Valeur a trouver : ";
            std::cin >> valeur;
            if (list.trouver(valeur)) {
                std::cout << "La valeur " << valeur << " a ete trouvee.\n";
            }
            else {
                std::cout << "La valeur " << valeur << " n'a pas ete trouvee ou est marquee comme supprimee.\n";
            }
            break;

        case 3:
            // Supprimer (marquer comme supprimé)
            std::cout << "Valeur a supprimer : ";
            std::cin >> valeur;
            if (list.supprimer(valeur)) {
                std::cout << "Valeur " << valeur << " marquee comme supprimee.\n";
            }
            else {
                std::cout << "Impossible de supprimer : valeur non trouvee.\n";
            }
            break;

        case 4:
            // Compactage  (suppression physique des nœuds marqués supprimés)
            std::cout << "Compactage de la liste en cours...\n";
            list.compacter();
            std::cout << "Liste compactee. Tous les noeuds libres ont ete retires.\n";
            break;

        case 5: {
            // Afficher la liste
            std::cout << "Etat actuel de la liste :\n";
            list.afficher();

            std::cout << "Parcours via l'iterateur : ";
            DoublyLinkedList::Iterator it = list.begin();
            bool empty = true;

            // Parcours uniquement des nœuds actifs
            while (it.hasNext()) {
                std::cout << it.next() << " ";
                empty = false;
            }

            if (empty) std::cout << "(liste vide ou aucun element actif)";
            std::cout << "\n";
            break;
        }

        case 6:
            // Quitter le programme
            std::cout << "Au revoir !\n";
            return 0;

        default:
            // Gestion des choix invalides
            std::cout << "Choix invalide, veuillez recommencer.\n";
        }
    }

    return 0;
}