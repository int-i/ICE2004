#include <iostream>
#include "helper.h"
#include "list.h"
#include "stack.h"

void test_list();
void solve_stock_span(const int* prices, int size);
void infix_to_postfix(const std::string& infix_expr);

int main() {
    std::cout << "<Test Doubly Linked List>" << std::endl;
    test_list();
    std::cout << std::endl;

    std::cout << "<Solve Stock Span>" << std::endl;

    int prices0[] = { 6, 4, 1, 2, 1, 3, 5 };
    std::cout << "prices: ";
    print_array<int>(prices0, 7);
    std::cout << "spans: ";
    solve_stock_span(prices0, 7);
    std::cout << std::endl;

    int prices1[] = { 1, 5, 8, 1, 3, 2, 6, 4 };
    std::cout << "prices: ";
    print_array<int>(prices1, 8);
    std::cout << "spans: ";
    solve_stock_span(prices1, 8);
    std::cout << std::endl;

    int prices2[] = { 8, 3, 2, 4, 6, 2, 1, 9, 3 };
    std::cout << "prices: ";
    print_array<int>(prices2, 9);
    std::cout << "spans: ";
    solve_stock_span(prices2, 9);
    std::cout << std::endl;

    std::cout << "<Infix to Postfix>" << std::endl;

    // '='는 표기식의 끝을 나타내는 문자입니다.
    std::string expr0 = "A+B*C=";
    std::cout << "infix: " << expr0 << std::endl
              << "postfix: ";
    infix_to_postfix(expr0);
    std::cout << std::endl;

    std::string expr1 = "A*(B+C)/D=";
    std::cout << "infix: " << expr1 << std::endl
              << "postfix: ";
    infix_to_postfix(expr1);
    std::cout << std::endl;

    std::string expr2 = "((A+(B*C))-(D/E))=";
    std::cout << "infix: " << expr2 << std::endl
              << "postfix: ";
    infix_to_postfix(expr2);
    std::cout << std::endl;

    std::string expr3 = "A^B+C^(D-E)=";
    std::cout << "infix: " << expr3 << std::endl
              << "postfix: ";
    infix_to_postfix(expr3);
    return 0;
}

// 임의의 정수들을 이용하여 Doubly Linked List가 정상 동작함을 보일 것.
void test_list() {
    DLinkedList<int> list;
    // list: empty

    for (int n = 1; n <= 3; n += 1) {
        list.push_front(n);
        std::cout << "after push " << n << " front" << std::endl;
        print_list<int>(list);
        std::cout << std::endl;
    }
    // list: 3 2 1

    for (int n = 4; n <= 6; n += 1) {
        list.push_back(n);
        std::cout << "after push " << n << " back" << std::endl;
        print_list<int>(list);
        std::cout << std::endl;
    }
    // list: 3 2 1 4 5 6

    for (int i = 0; i < 2; i += 1) {
        list.pop_front();
        std::cout << "after pop front" << std::endl;
        print_list<int>(list);
        std::cout << std::endl;
    }
    // list: 1 4 5 6

    for (int i = 0; i < 3; i += 1) {
        list.pop_back();
        std::cout << "after pop back" << std::endl;
        print_list<int>(list);
        std::cout << std::endl;
    }
    // list: 1

    list.pop_back();
    // list: empty

    std::cout << "check list clear: " << list.empty() << std::endl;
}

// Stock Span 알고리즘을 구현하고 동작함을 보일 것
void solve_stock_span(const int* prices, int size) {
    DequeStack<int> days;
    // 날짜를 순서대로 순회합니다.
    for (int i = 0; i < size; i += 1) {
        // 스택에 저장된 날짜의 가격이 현재 가격보다 클 때까지 스택에서 값을 제거합니다.
        while (!days.empty() && prices[days.top()] <= prices[i]) {
            days.pop();
        }
        // 스택이 비어있는지 확인합니다.
        if (days.empty()) {
            // 스택이 비었다면 (현재 날짜+1)한 값을 출력합니다.
            // Stock Span은 1부터 시작하기 때문에 1을 더합니다.
            std::cout << i + 1 << ' ';
        } else {
            // 스택에 값이 남아있다면 (현재 날짜-스택의 값)을 출력합니다.
            std::cout << i - days.top() << ' ';
        }
        // 현재 날짜를 스택에 저장합니다.
        days.push(i);
    }
    std::cout << std::endl;
}

// 중위 표기식을 후위 표기식으로 변환하는 알고리즘을 구현할 것
void infix_to_postfix(const std::string& infix_expr) {
    DequeStack<char> operators;
    // 중위 표기식의 문자를 하니씩 순회합니다.
    for (char token : infix_expr) {
        if (is_operand(token)) {
            // 피연산자는 그대로 출력합니다.
            std::cout << token;
        } else if (token == ')') {
            // ')'는 '('를 만날 때까지 스택에서 연산자를 빼며 출력합니다.
            while (operators.top() != '(') {
                std::cout << operators.top();
                operators.pop();
            }
            operators.pop();
        } else if (is_operator(token)) {
            // 연산자는 우선순위를 비교한 후, `token`의 우선순위가 더 작다면 스택에서 연산자를 빼며 출력합니다.
            while (!operators.empty() && priority_in_stack(operators.top()) >= priority_in_expr(token)) {
                std::cout << operators.top();
                operators.pop();
            }
            // `token`은 스택에 넣어줍니다.
            operators.push(token);
        } else if (token == '=') {
            // 표기식의 마지막 문자가 들어오면, 스택이 빌 때까지 연산자를 빼며 출력합니다.
            while (!operators.empty()) {
                std::cout << operators.top();
                operators.pop();
            }
        }
    }
    std::cout << std::endl;
}
