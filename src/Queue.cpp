#include "Queue.h"
#include <iostream>

// Constructor to initialize an empty queue
Queue::Queue() {
    front = -1;
    rear = -1;

    // TODO: Your code here
}

// Adds a province to the end of the queue
void Queue::enqueue(int province) {
    if ((rear + 1) % MAX_QUEUE_SIZE == front) {
        std::cerr << "Queue is full." << std::endl;
        return;
    }
    if (front == -1) {
        front = 0;
    }
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    data[rear] = province;
    // TODO: Your code here
    // Implement circular structure 
    // Add the province  
}

// Removes and returns the front province from the queue
int Queue::dequeue() {
    if (front == -1) {
        std::cerr << "Queue is empty." << std::endl;
        return -1;
    }
    int province = data[front];
    if (front == rear) {
        front = -1;
        rear = -1;
    }else {
        front = (front + 1) % MAX_QUEUE_SIZE;
    }
    // TODO: Your code here
    return province;
}

// Returns the front province without removing it
int Queue::peek() const {
    if (front == -1) {
        std::cerr << "Queue is empty." << std::endl;
        return -1;
    }
    return data[front];
    // TODO: Your code here
}

// Checks if the queue is empty
bool Queue::isEmpty() const {
    return  front == -1;
    // TODO: Your code here
}

// Add a priority neighboring province in a way that will be dequeued and explored before other non-priority neighbors
void Queue::enqueuePriority(int province) {
    if ((rear + 1) % MAX_QUEUE_SIZE == front) {
        std::cerr << "Queue is full." << std::endl;
        return;
    }

    if (front == -1) {
        enqueue(province);
        return;
    }

    int current = rear;
    while (current != (front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE) {
        int next = (current + 1) % MAX_QUEUE_SIZE;
        data[next] = data[current];
        current = (current - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    }



    data[front] = province;
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    // TODO: Your code here
}

