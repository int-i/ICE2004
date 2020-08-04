// 중복 삽입 방지를 위한 Define Guard
#ifndef ICE2004_WEEK11_HW01_STACK_H
#define ICE2004_WEEK11_HW01_STACK_H

// 사용할 헤더를 정의합니다.
#include <exception>
#include <string>
#include "deque.h"

/**
 * 빈 스택에서 값을 가져올 때 발생하는 예외
 * @extends std::exception
 */
class StackEmpty : public std::exception {
private:
    /** 예외 메세지 */
    std::string message;

public:
    /**
     * 주어진 예외 메세지로 예외를 생성합니다.
     * @param message 예외 메세지
     */
    explicit StackEmpty(const std::string& message)
    : message(message) {}

    /**
     * 예외의 오류 메세지를 반환합니다.
     * @return 오류 메세지
     */
    std::string get_message() const {
        return this->message;
    }
};

/**
 * 덱으로 구현된 스택 클래스
 * @tparam T 스택에 담을 타입
 */
template<typename T>
class DequeStack {
private:
    /** 스택의 값을 담을 컨테이너 */
    LinkedDeque<T> container;

public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;

    /**
     * 현재 스택이 가지고 있는 값의 개수를 반환합니다.
     * @return 스택의 크기
     */
    int size() const {
        return container.size();
    }

    /**
     * 스택이 비어있는지 확인합니다.
     * @return 비어있다면 `true`를 반환합니다.
     */
    bool empty() const {
        return container.empty();
    }

    /**
     * 스택의 맨 위 값을 반환합니다.
     * @return 스택의 맨 위 값
     */
    const_reference top() const throw(StackEmpty) {
        // 먼저 스택이 비어있는지 확인합니다.
        if (!empty()) {
            return container.front();
        }
        // 스택이 비어있다면 예외를 반환합니다.
        throw StackEmpty("top of empty stack");
    }

    /**
     * 스택의 맨 위에 값을 삽입합니다.
     * @param value 스택에 넣을 값
     */
    void push(const_reference value) {
        container.push_front(value);
    }

    /**
     * 스택의 맨 위에서 값을 제거합니다.
     */
    void pop() throw(StackEmpty) {
        // 먼저 스택이 비어있는지 확인합니다.
        if (!empty()) {
            container.pop_front();
        } else {
            // 스택이 비어있다면 예외를 반환합니다.
            throw StackEmpty("pop of empty stack");
        }
    }
};

#endif // ICE2004_WEEK11_HW01_STACK_H
