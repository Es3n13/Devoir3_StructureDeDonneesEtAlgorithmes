#pragma once
#ifndef LISTECHAINEE_H
#define LISTECHAINEE_H

#include <iostream>

/**
 * Structure representing a node in the Doubly Linked List.
 */
struct Node {
    int data;
    bool isFree;       // Lazy deletion flag: true if the node is logically deleted
    Node* prev;
    Node* next;

    Node(int val) : data(val), isFree(false), prev(nullptr), next(nullptr) {}
};

/**
 * Doubly Linked List with Lazy Deletion.
 * Uses sentinel nodes to simplify edge cases (empty list, insertions/deletions at ends).
 */
class DoublyLinkedList {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    // Core methods
    void ajouter(int value);           // Add to end, O(1)
    Node* trouver(int value);         // Find first active node, O(n)
    bool supprimer(int value);        // Lazy delete (mark isFree=true), O(n)
    void compacter();                 // Physically remove all freed nodes, O(n)
    void afficher() const;            // Display the list (including free nodes for demo)

    // Iterator class
    class Iterator {
    private:
        Node* current;
        DoublyLinkedList* list;

    public:
        Iterator(Node* start, DoublyLinkedList* l);
        bool hasNext();
        int next();
    };

    Iterator begin();

private:
    Node* headSentinel;
    Node* tailSentinel;

    // Internal helper to remove a node physically from the chain
    void removeNodePhysically(Node* node);
};

#endif // LISTECHAINEE_H
