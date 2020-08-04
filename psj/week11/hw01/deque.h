// 중복 삽입 방지를 위한 Define Guard
#ifndef ICE2004_WEEK11_HW01_DEQUE_H
#define ICE2004_WEEK11_HW01_DEQUE_H

// 사용할 헤더를 정의합니다.
#include <exception>
#include <string>
#include "list.h"

/**
 * 빈 덱에서 값을 가져올 때 발생하는 예외
 * @extends std::exception
 */
class DequeEmpty : public std::exception {
private:
    /** 예외 메세지 */
    std::string message;

public:
    /**
     * 주어진 예외 메세지로 예외를 생성합니다.
     * @param message 예외 메세지
     */
    explicit DequeEmpty(const std::string& message)
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
 * 연결 리스트로 구현된 덱 클래스
 * @tparam T 덱에 담을 타입
 */
template<typename T>
class LinkedDeque {
private:
    /** 덱의 값을 담을 컨테이너 */
    DLinkedList<T> container;

    /** 컨테이너가 담고 있는 값의 개수 */
    int container_size;

public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;

    /**
     * 연결 리스트로 구현된 덱 클래스를 생성합니다.
     */
    LinkedDeque()
    : container_size(0) {}

    /**
     * 현재 덱이 가지고 있는 값의 개수를 반환합니다.
     * @return 덱의 크기
     */
    int size() const {
        return container_size;
    }

    /**
     * 덱이 비어있는지 확인합니다.
     * @return 비어있다면 `true`를 반환합니다.
     */
    bool empty() const {
        return container.empty();
    }

    /**
     * 덱의 첫 번째 값을 반환합니다.
     * @return 덱의 첫 번째 값
     */
    const_reference front() const throw(DequeEmpty) {
        // 먼저 덱이 비어있는지 확인합니다.
        if (!empty()) {
            return container.front();
        }
        // 덱이 비어있다면 예외를 반환합니다.
        throw DequeEmpty("front of empty deque");
    }

    /**
     * 덱의 마지막 값을 반환합니다.
     * @return 덱의 마지막 값
     */
    const_reference back() const throw(DequeEmpty) {
        // 먼저 덱이 비어있는지 확인합니다.
        if (!empty()) {
            return container.back();
        }
        // 덱이 비어있다면 예외를 반환합니다.
        throw DequeEmpty("back of empty deque");
    }

    /**
     * 덱의 맨 앞에 값을 삽입합니다.
     * @param value 덱에 넣을 값
     */
    void push_front(const_reference value) {
        // 값을 삽입하고 크기를 1 증가시킵니다.
        container.push_front(value);
        container_size += 1;
    }

    /**
     * 덱의 맨 뒤에 값을 삽입합니다.
     * @param value 덱에 넣을 값
     */
    void push_back(const_reference value) {
        // 값을 삽입하고 크기를 1 증가시킵니다.
        container.push_back(value);
        container_size += 1;
    }

    /**
     * 덱의 맨 앞에서 값을 제거합니다.
     */
    void pop_front() throw(DequeEmpty) {
        // 먼저 덱이 비어있는지 확인합니다.
        if (!empty()) {
            // 값을 제거하고 크기를 1 감소시킵니다.
            container.pop_front();
            container_size -= 1;
        } else {
            // 덱이 비어있다면 예외를 반환합니다.
            throw DequeEmpty("pop_front of empty deque");
        }
    }

    /**
     * 덱의 맨 뒤에서 값을 제거합니다.
     */
    void pop_back() throw(DequeEmpty) {
        // 먼저 덱이 비어있는지 확인합니다.
        if (!empty()) {
            // 값을 제거하고 크기를 1 감소시킵니다.
            container.pop_back();
            container_size -= 1;
        } else {
            // 덱이 비어있다면 예외를 반환합니다.
            throw DequeEmpty("pop_back of empty deque");
        }
    }
};

#endif // ICE2004_WEEK11_HW01_DEQUE_H
