#pragma once
#ifndef LISTECHAINEE_H
#define LISTECHAINEE_H

#include <iostream>

//Structure représentant un nœud dans une liste doublement chaînée.
struct Node {
    int data; // Valeur stockée dans le nœud
    bool isFree; // Indicateur de suppression "paresseuse" (true = nœud logiquement supprimé)
    Node* prev; // Pointeur vers le nœud précédent
    Node* next; // Pointeur vers le nœud suivant

    Node(int val) : data(val), isFree(false), prev(nullptr), next(nullptr) {}
};


 //Classe de la liste doublement chaînée.
class DoublyLinkedList {
public:
    DoublyLinkedList(); // Constructeur crée une liste vide
    ~DoublyLinkedList(); // Destructeur libère la mémoire allouée

    // Méthodes
    void ajouter(int value); // Ajoute un élément à la fin de la liste.
    Node* trouver(int value); // Recherche le premier nœud actif contenant la valeur donnée.
    bool supprimer(int value); // Marque le nœud comme supprimé sans le retirer physiquement.
    void compacter(); // Supprime physiquement les nœuds marqués comme supprimés.
    void afficher() const; // Affiche le contenu de la liste.


    // Itérateur permettant de parcourir la liste.
    class Iterator {
    private:
        Node* current; // Pointeur vers le nœud actuellement consulté.
        DoublyLinkedList* list; // Référence vers la liste parcourue.

    public:
        Iterator(Node* start, DoublyLinkedList* l);
        bool hasNext(); // Indique s’il reste un élément à parcourir
        int next(); // Retourne la valeur du nœud suivant et avance le pointeur
    };

    Iterator begin(); // Renvoie un itérateur pointant sur le premier élément.

private:
    Node* headSentinel; // Nœud sentinelle en tête de liste (avant le premier vrai élément)
    Node* tailSentinel; // Nœud sentinelle en fin de liste (après le dernier vrai élément)

    // Méthode pur supprimer physiquement un nœud de la chaîne
    void removeNodePhysically(Node* node);
};

#endif
