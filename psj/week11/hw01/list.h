// 중복 삽입 방지를 위한 Define Guard
#ifndef ICE2004_WEEK11_HW01_LIST_H
#define ICE2004_WEEK11_HW01_LIST_H

/**
 * 양방향 연결 리스트 클래스
 * @tparam T 리스트에 담을 타입
 */
template<typename T>
class DLinkedList {
public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;

    /** 리스트의 노드 클래스 */
    class Node {
    private:
        /** 노드 값 */
        T value;

        /** 이전 노드 */
        Node* prev;

        /** 다음 노드 */
        Node* next;

        // `DLinkedList`가 `Node`의 private 멤버 변수에 접근할 수 있도록 friend 클래스로 선언합니다.
        friend DLinkedList<T>;
    };

    /**
     * 양방향 연결 리스트를 생성합니다.
     * 주의: 복사 생성자가 구현되어 있지 않습니다. 복사된 리스트가 소멸되면 메모리 오류를 발생시킵니다.
     */
    DLinkedList()
    : header(new Node), trailer(new Node) {
        connect(header, trailer);
    }

    /**
     * 양방향 연결 리스트의 소멸자입니다.
     */
    ~DLinkedList() {
        // 더 이상 노드가 없을 때까지 노드를 제거합니다.
        while (!empty()) {
            pop_back();
        }
        // `header`와 `trailer`를 삭제합니다.
        delete header;
        delete trailer;
    }

    /**
     * 리스트가 비어있는지 확인합니다.
     * @return 비어있다면 `true`를 반환합니다.
     */
    bool empty() const {
        // `header`와 `trailer` 사이에 아무 노드도 없다면, 리스트는 비어있는 상태입니다.
        return header->next == trailer;
    }

    /**
     * 리스트의 첫 번째 값을 반환합니다.
     * @return 리스트의 첫 번째 값
     */
    const_reference front() const {
        return header->next->value;
    }

    /**
     * 리스트의 마지막 값을 반환합니다.
     * @return 리스트의 마지막 값
     */
    const_reference back() const {
        return trailer->prev->value;
    }

    /**
     * 리스트의 맨 앞에 값을 삽입합니다.
     * @param value 리스트에 넣을 값
     */
    void push_front(const_reference value) {
        // `insert` 함수를 이용해 `header`와 그 다음 노드 사이에 값을 삽입합니다.
        insert(header->next, value);
    }

    /**
     * 리스트의 맨 뒤에 값을 삽입합니다.
     * @param value 리스트에 넣을 값
     */
    void push_back(const_reference value) {
        // `insert` 함수를 이용해 `trailer`와 그 이전 노드 사이에 값을 삽입합니다.
        insert(trailer, value);
    }

    /**
     * 리스트의 맨 앞에서 값을 제거합니다.
     */
    void pop_front() {
        // `remove` 함수를 이용해 `header` 다음 노드를 제거합니다.
        remove(header->next);
    }

    /**
     * 리스트의 맨 뒤에서 값을 제거합니다.
     */
    void pop_back() {
        // `remove` 함수를 이용해 `trailer` 이전 노드를 제거합니다.
        remove(trailer->prev);
    }

protected:
    /**
     * 두 개의 노드를 서로 연결합니다.
     * @param a 앞 노드
     * @param b 뒤 노드
     */
    void connect(Node* a, Node* b) {
        a->next = b;
        b->prev = a;
    }

    /**
     * `where` 앞에 새로운 노드를 만들고 값을 저장합니다.
     * @param where 노드를 생성할 위치
     * @param value 노드에 담을 값
     */
    void insert(Node* where, const_reference value) {
        // 새로운 노드 생성
        Node* new_node = new Node;
        // 노드에 값 저장
        new_node->value = value;
        // 앞 노드와 새로운 노드를 연결
        connect(where->prev, new_node);
        // 새로운 노드와 뒤 노드를 연결
        connect(new_node, where);
    }

    /**
     * 해당 노드를 제거합니다.
     * @param target 제거할 노드
     */
    void remove(Node* target) {
        // 앞 노드와 뒤 노드를 서로 연결합니다.
        connect(target->prev, target->next);
        // 사용이 끝난 노드를 삭제합니다.
        delete target;
    }

private:
    /** 리스트의 첫 번째 노드를 가리키는 헤더 */
    Node* header;

    /** 리스트의 마지막 노드를 가리키는 트레일러 */
    Node* trailer;
};

#endif // ICE2004_WEEK11_HW01_LIST_H
