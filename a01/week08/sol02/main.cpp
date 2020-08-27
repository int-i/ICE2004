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
    int size() {
        return inner_stack.size();
    }
};

bool is_valid_paren(const std::string& input) {
    try {
        Stack<char> stack;
        for (const char c : input) {
            switch (c) {
            case '(':
            case '{':
            case '[':
                stack.push(c);
                break;
            case ')':
                if (stack.top() != '(') {
                    return false;
                }
                stack.pop();
                break;
            case '}':
                if (stack.top() != '{') {
                    return false;
                }
                stack.pop();
                break;
            case ']':
                if (stack.top() != '[') {
                    return false;
                }
                stack.pop();
                break;
            }
        }
        return stack.empty();
    } catch (StackEmpty& e) {
        return false;
    }
}

void problem3() {
    Stack<std::string> stack;

    std::string info = "(name):[studentid]";
    stack.push("( )([ ]){([(ice2004)])}");
    stack.push("((( )ice2004(( )){([( )])}");
    stack.push(")(( )){([( )])}");
    stack.push("({[ ])}");
    stack.push("(ice2004");
    stack.push(info);

    int n = stack.size();
    for (int i = 0; i < n; i++) {
        std::cout << stack.top();
        if (is_valid_paren(stack.top())) {
            std::cout << ": correct" << std::endl;
        } else {
            std::cout << ": incorrect" << std::endl;
        }
        stack.pop();
    }
    stack.pop();
}

int main() {
    try {
        problem3();
    } catch (StackEmpty& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
