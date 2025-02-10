#include "Stack.h"
#include <iostream>

// Constructor to initialize an empty stack
Stack::Stack() {
    top = -1;
    // TODO: Your code here
}

// Adds a province to the top of the stack
void Stack::push(int province) {
    if (top == MAX_SIZE - 1) {
        std::cerr << "Stack is full." << std::endl;
        return;
    }
    top++;
    data[top] = province;
    // TODO: Your code here
}

// Removes and returns the top province from the stack
int Stack::pop() {
    if (top == -1) {
        std::cerr << "Stack is empty." << std::endl;
        return -1;
    }
    int tempTopValue = data[top];
    top--;
    return tempTopValue;
    // TODO: Your code here
}

// Returns the top province without removing it
int Stack::peek() const {
    if (top == -1) {
        std::cerr << "Stack is empty." << std::endl;
        return -1;
    }
    return data[top];
    // TODO: Your code here
}

// Checks if the stack is empty
bool Stack::isEmpty() const {
    return top == -1;
    // TODO: Your code here
}

// Function to get the current size of the stack
int Stack::getSize() const {
    return top + 1 ;
    // TODO: Your code here
}
