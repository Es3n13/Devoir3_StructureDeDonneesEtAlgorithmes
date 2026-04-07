#include <iostream>
#include <string>
#include "listechainee.h"

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
    DoublyLinkedList list;
    int choix;
    int valeur;

    while (true) {
        afficherMenu();
        if (!(std::cin >> choix)) {
            std::cout << "Entree invalide. Veuillez entrer un nombre.\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        switch (choix) {
        case 1:
            std::cout << "Valeur a ajouter : ";
            std::cin >> valeur;
            list.ajouter(valeur);
            std::cout << "Valeur " << valeur << " ajoutee.\n";
            break;
        case 2:
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
            std::cout << "Compactage de la liste en cours...\n";
            list.compacter();
            std::cout << "Liste compactee. Tous les noeuds libres ont ete retires.\n";
            break;
        case 5: {
            std::cout << "Etat actuel de la liste :\n";
            list.afficher();

            std::cout << "Parcours via l'Iterateur : ";
            DoublyLinkedList::Iterator it = list.begin();
            bool empty = true;
            while (it.hasNext()) {
                std::cout << it.next() << " ";
                empty = false;
            }
            if (empty) std::cout << "(liste vide ou aucun element actif)";
            std::cout << "\n";
            break;
        }
        case 6:
            std::cout << "Au revoir !\n";
            return 0;
        default:
            std::cout << "Choix invalide, veuillez recommencer.\n";
        }
    }

    return 0;
}