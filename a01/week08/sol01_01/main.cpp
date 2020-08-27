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
    T& pop() {
        T& tmp = top();
        inner_stack.pop();
        return tmp;
    }
    void push(T element) {
        inner_stack.push(element);
    }
};

void problem1() {
    Stack<int> stack;
    stack.push(1);
    std::cout << stack.pop() << std::endl;
    std::cout << stack.pop() << std::endl;
}

int main() {
    try {
        problem1();
    } catch (StackEmpty& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
