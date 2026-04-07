#include "listechainee.h"

DoublyLinkedList::DoublyLinkedList() {
    // Initialize sentinels
    // Sentinels are not treated as "free" or "active" data nodes.
    headSentinel = new Node(-1); // Data is irrelevant for sentinels
    tailSentinel = new Node(-1);

    headSentinel->next = tailSentinel;
    tailSentinel->prev = headSentinel;
}

DoublyLinkedList::~DoublyLinkedList() {
    Node* current = headSentinel;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

void DoublyLinkedList::ajouter(int value) {
    // Insert at the end, just before the tailSentinel
    Node* newNode = new Node(value);
    Node* lastActive = tailSentinel->prev;

    newNode->next = tailSentinel;
    newNode->prev = lastActive;
    lastActive->next = newNode;
    tailSentinel->prev = newNode;
}

Node* DoublyLinkedList::trouver(int value) {
    // Iterate from headSentinel->next up to tailSentinel
    Node* current = headSentinel->next;
    while (current != tailSentinel) {
        if (!current->isFree && current->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr; // Not found or only found as a freed node
}

bool DoublyLinkedList::supprimer(int value) {
    Node* target = trouver(value);
    if (target) {
        target->isFree = true; // Lazy deletion
        return true;
    }
    return false;
}

void DoublyLinkedList::removeNodePhysically(Node* node) {
    if (!node || node == headSentinel || node == tailSentinel) return;

    Node* p = node->prev;
    Node* n = node->next;

    p->next = n;
    n->prev = p;

    delete node;
}

void DoublyLinkedList::compacter() {
    // Iterate and remove all nodes marked as free
    Node* current = headSentinel->next;
    while (current != tailSentinel) {
        Node* nextNode = current->next; // Save next before potential deletion
        if (current->isFree) {
            removeNodePhysically(current);
        }
        current = nextNode;
    }
}

void DoublyLinkedList::afficher() const {
    Node* current = headSentinel->next;
    std::cout << "[HEAD] <-> ";
    while (current != tailSentinel) {
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

// --- Iterator Implementation ---

DoublyLinkedList::Iterator::Iterator(Node* start, DoublyLinkedList* l)
    : current(start), list(l) {
    // Ensure the iterator starts at the first active node
    while (current != nullptr && (list->tailSentinel == current || current->isFree)) {
        // This logic is slightly simplified; since begin() passes headSentinel->next,
        // we just need to skip freed nodes.
        if (current == list->tailSentinel) break;
        current = current->next;
    }
}

bool DoublyLinkedList::Iterator::hasNext() {
    return (current != nullptr && current != list->tailSentinel);
}

int DoublyLinkedList::Iterator::next() {
    if (!hasNext()) {
        throw std::out_of_range("No more active elements in the list");
    }

    int val = current->data;
    current = current->next;

    // Skip any freed nodes to land on the next active one
    while (current != nullptr && current != list->tailSentinel && current->isFree) {
        current = current->next;
    }

    return val;
}

DoublyLinkedList::Iterator DoublyLinkedList::begin() {
    // Start iterator from the first node after headSentinel
    return Iterator(headSentinel->next, this);
}