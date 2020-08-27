#include <exception>
#include <iostream>
#include <stack>

class StackEmpty : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "Stack is empty!\n";
    }
};

template<typename T>
class Stack {
private:
    std::stack<T> inner_stack;

public:
    bool empty() {
        return inner_stack.empty();
    }
    T& top() noexcept(false) {
        if (!empty()) {
            return inner_stack.top();
        }
        throw StackEmpty();
    }
};

void problem2() {
    Stack<int> stack;
    stack.top();
}

int main() {
    try {
        problem2();
    } catch (StackEmpty& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
