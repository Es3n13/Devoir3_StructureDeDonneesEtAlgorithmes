#include "listechainee.h"

//  Constructeur
DoublyLinkedList::DoublyLinkedList() {
    headSentinel = new Node(-1);
    tailSentinel = new Node(-1);

    // La tête pointe vers la fin, et la fin pointe vers la tête = liste vide
    headSentinel->next = tailSentinel;
    tailSentinel->prev = headSentinel;
}

// Destructeur
DoublyLinkedList::~DoublyLinkedList() {
    // Parcours de la liste entière pour libérer la mémoire de chaque nœud
    Node* current = headSentinel;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

// Ajouter un élément
void DoublyLinkedList::ajouter(int value) {
    // Insère un nouveau nœud juste avant la sentinelle de fin
    Node* newNode = new Node(value);
    Node* lastActive = tailSentinel->prev; // Dernier élément avant la fin

    // Chaînage du nouveau nœud
    newNode->next = tailSentinel;
    newNode->prev = lastActive;
    lastActive->next = newNode;
    tailSentinel->prev = newNode;
}

// Trouver un élément
Node* DoublyLinkedList::trouver(int value) {
    // Parcours depuis le début jusqu’à la fin pour chercher une valeur active
    Node* current = headSentinel->next;
    while (current != tailSentinel) {
        if (!current->isFree && current->data == value) {
            return current; // Trouvé = retourne le pointeur vers ce nœud
        }
        current = current->next;
    }
    return nullptr; // Non trouvé ou trouvé dans un nœud marqué supprimé
}

// Suppression logique d’un nœud
bool DoublyLinkedList::supprimer(int value) {
    // Recherche le nœud contenant la valeur
    Node* target = trouver(value);
    if (target) {
        target->isFree = true; // Marque le nœud comme supprimé sans le retirer
        return true;
    }
    return false; // Valeur non trouvée
}

//  Suppression physique d’un nœud
void DoublyLinkedList::removeNodePhysically(Node* node) {
    // Vérifie que le nœud est valide et que ce n’est pas une sentinelle
    if (!node || node == headSentinel || node == tailSentinel) return;

    Node* p = node->prev;
    Node* n = node->next;

    // "Détache" le nœud de la chaîne
    p->next = n;
    n->prev = p;

    delete node; // Libère la mémoire
}

// Compactage
void DoublyLinkedList::compacter() {
    // Parcourt toute la liste et supprime physiquement les nœuds marqués libres
    Node* current = headSentinel->next;
    while (current != tailSentinel) {
        Node* nextNode = current->next; // Sauvegarde du suivant avant suppression
        if (current->isFree) {
            removeNodePhysically(current);
        }
        current = nextNode;
    }
}

// Affichage de la liste
void DoublyLinkedList::afficher() const {
    Node* current = headSentinel->next;
    std::cout << "[HEAD] <-> ";
    while (current != tailSentinel) {
        // Affiche différemment les nœuds supprimés
        if (current->isFree) {
            std::cout << "[FREE:" << current->data << "] <-> ";
        }
        else {
            std::cout << current->data << " <-> ";
        }
        current = current->next;
    }
    std::cout << "[TAIL]" << std::endl;
}

// Constructeur de l’itérateur
DoublyLinkedList::Iterator::Iterator(Node* start, DoublyLinkedList* l)
    : current(start), list(l) {
    // Positionner l’itérateur sur le premier nœud non libre
    while (current != nullptr && (list->tailSentinel == current || current->isFree)) {
        if (current == list->tailSentinel) break;
        current = current->next;
    }
}

// Vérifie s’il reste des éléments à parcourir
bool DoublyLinkedList::Iterator::hasNext() {
    return (current != nullptr && current != list->tailSentinel);
}

// Récupère la valeur du nœud courant et avance
int DoublyLinkedList::Iterator::next() {
    if (!hasNext()) {
        throw std::out_of_range("Aucun autre élément actif dans la liste");
    }

    int val = current->data;
    current = current->next;

    // Saute les nœuds marqués comme libres
    while (current != nullptr && current != list->tailSentinel && current->isFree) {
        current = current->next;
    }

    return val;
}

// Renvoie un itérateur pointant sur le premier élément réel de la liste
DoublyLinkedList::Iterator DoublyLinkedList::begin() {
    return Iterator(headSentinel->next, this);
}