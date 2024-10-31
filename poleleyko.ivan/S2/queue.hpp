#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <stdexcept>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };
    Node* front;
    Node* back;

public:
    Queue() : front(nullptr), back(nullptr) {}

    ~Queue() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
        if (back) {
            back->next = newNode;
        }
        back = newNode;
        if (front == nullptr) {
            front = back;
        }
    }

    void pop() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            back = nullptr;
        }
        delete temp;
    }

    T frontElement() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return front->data;
    }
};

#endif
