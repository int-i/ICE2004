#ifndef ICE2004_WEEK11_HW01_HELPER_H
#define ICE2004_WEEK11_HW01_HELPER_H

#include <iostream>
#include "list.h"

/**
 * 주어진 토큰이 연산자인지 확인합니다.
 * @param token 토큰 문자
 * @return 연산자라면 `true`를 반환합니다.
 */
bool is_operator(char token) {
    return token == '(' || token == ')' || token == '+' || token == '-' || token == '*' || token == '/' || token == '^';
}

/**
 * 주어진 토큰이 피연산자인지 확인합니다.
 * @param token 토큰 문자
 * @return 피연산자라면 `true`를 반환합니다.
 */
bool is_operand(char token) {
    return token != '=' && !is_operator(token);
}

/**
 * 스택 내에서 주어진 연산자의 우선순위를 반환합니다.
 * @param token 토큰 문자
 * @return 연산자의 우선순위
 */
int priority_in_stack(char token) {
    switch (token) {
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    case '(':
        return 0;
    default: // must be unreached
        return -1;
    }
}

/**
 * 식 내에서 주어진 연산자의 우선순위를 반환합니다.
 * @param token 토큰 문자
 * @return 연산자의 우선순위
 */
int priority_in_expr(char token) {
    switch (token) {
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    case '(':
        return 4;
    default: // must be unreached
        return -1;
    }
}

/**
 * 표준 출력 스트림으로 배열의 원소를 출력합니다.
 * @tparam T 배열의 타입
 * @param array 배열
 * @param size 배열의 크기
 */
template<typename T>
void print_array(const T* array, int size) {
    for (int i = 0; i < size; i += 1) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
}

/**
 * 표준 출력 스트림으로 리스트의 첫 번째와 마지막 원소를 출력합니다.
 * @tparam T 리스트 내부의 타입
 * @param list 리스트
 */
template<typename T>
void print_list(const DLinkedList<T>& list) {
    std::cout << "front: " << list.front() << std::endl
              << "back: " << list.back() << std::endl;
}

#endif // ICE2004_WEEK11_HW01_HELPER_H
