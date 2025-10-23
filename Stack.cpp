#include <iostream>
using namespace std;

template <typename T>
class Stack {
private:
    T arr[100];     // fixed-size array stack
    int top;

public:
    Stack() {
        top = -1;   // initialize empty stack
    }

    void push(T value) {
        if (top >= 99) {
            cout << "Stack Overflow!" << endl;
            return;
        }
        arr[++top] = value;
        cout << value << " pushed to stack." << endl;
    }

    void pop() {
        if (top < 0) {
            cout << "Stack Underflow!" << endl;
            return;
        }
        cout << arr[top--] << " popped from stack." << endl;
    }

    void display() {
        if (top < 0) {
            cout << "Stack is empty." << endl;
            return;
        }
        cout << "Stack contents: ";
        for (int i = 0; i <= top; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    // Integer stack
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.display();
    intStack.pop();
    intStack.display();

    cout << endl;

    // Float stack
    Stack<float> floatStack;
    floatStack.push(3.14f);
    floatStack.push(2.71f);
    floatStack.display();
    floatStack.pop();
    floatStack.display();

    return 0;
}
