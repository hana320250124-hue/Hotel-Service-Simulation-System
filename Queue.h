#ifndef QUEUE_H
#define QUEUE_H

#include "Customer.h"

// ── Single node in the linked list ──────────
struct Node {
    Customer data;
    Node*    next;

    Node(Customer c) {
        data = c;
        next = nullptr;
    }
};

// ── Manual Queue (no STL) ───────────────────
//
//  FIX 1: Destructor now deletes nodes directly
//          instead of calling dequeue() (avoids
//          unnecessary Customer copies)
//
//  FIX 2: Copy Constructor added  ──────────┐
//  FIX 3: Assignment Operator added          │
//          (Rule of Three – required because  │
//          we manage raw pointers manually)   │
//          Without these, copying a Queue    │
//          gives two objects pointing to the │
//          same nodes → double-delete crash  ┘
//
class Queue {
private:
    Node* frontNode;
    Node* rearNode;

    // Deep-copy helper used by copy constructor
    // and assignment operator
    void copyFrom(const Queue& other) {
        frontNode = rearNode = nullptr;
        Node* cur = other.frontNode;
        while (cur) {
            enqueue(cur->data);   // creates brand-new nodes
            cur = cur->next;
        }
    }

public:
    // ── Constructor ─────────────────────────
    Queue() {
        frontNode = rearNode = nullptr;
    }

    // ── FIX 2: Copy Constructor ─────────────
    Queue(const Queue& other) {
        frontNode = rearNode = nullptr;
        copyFrom(other);
    }

    // ── FIX 3: Assignment Operator ──────────
    Queue& operator=(const Queue& other) {
        if (this == &other) return *this;   // self-assignment guard
        clearAll();                          // free existing nodes first
        copyFrom(other);
        return *this;
    }

    // ── FIX 1: Destructor (direct delete) ───
    ~Queue() {
        clearAll();
    }

    // ── Core operations ─────────────────────
    bool isEmpty() const {
        return frontNode == nullptr;
    }

    void enqueue(Customer c) {
        Node* n = new Node(c);
        if (isEmpty()) {
            frontNode = rearNode = n;
        } else {
            rearNode->next = n;
            rearNode       = n;
        }
    }

    Customer dequeue() {
        if (isEmpty()) return Customer();

        Node*    temp = frontNode;
        Customer c    = temp->data;

        frontNode = frontNode->next;
        delete temp;

        if (!frontNode) rearNode = nullptr;

        return c;
    }

private:
    // Free every node without copying Customer data
    void clearAll() {
        while (frontNode) {
            Node* tmp = frontNode;
            frontNode = frontNode->next;
            delete tmp;   // just delete the node, no Customer copy
        }
        rearNode = nullptr;
    }
};

#endif