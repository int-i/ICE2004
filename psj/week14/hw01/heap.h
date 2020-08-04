// 중복 삽입 방지를 위한 Define Guard
#ifndef ICE2004_WEEK15_HW01_HEAP_H
#define ICE2004_WEEK15_HW01_HEAP_H

#include <cstddef>
#include <queue>
#include <utility>

/**
 * 배열로 구현되는 힙 클래스
 * @tparam T 힙에 담을 타입
 * @param cmp 힙 원소 비교자
 */
template<typename T, typename Compare = std::greater<T>>
class ArrayHeap {
public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;

    /**
     * 힙을 생성합니다.
     * 주의: 복사 생성자가 구현되어 있지 않습니다. 복사된 힙이 소멸되면 메모리 오류를 발생시킵니다.
     * @param cmp 힙 원소 비교자
     */
    explicit ArrayHeap(std::size_t capacity, const Compare& compare = Compare())
    : container(new T[capacity]), capacity(capacity), size(0), comp(compare) {}

    /**
     * 힙의 소멸자입니다.
     */
    ~ArrayHeap() {
        delete[] container;
    }

    /**
     * 힙에 값을 삽입합니다.
     * 만약 힙이 가득 차 있다면 오류를 반환하며 프로그램을 종료합니다.
     * @param value 힙에 넣을 값
     */
    void push(const_reference value) {
        std::size_t inserted_index = size; // 값이 삽입될 위치입니다.
        container[inserted_index] = value;

        size += 1; // 크기를 1 증가시킵니다.

        // 힙의 규칙을 만족하도록 값을 바꿔줍니다. (UpHeap)
        while (inserted_index != 0 && comp(container[(inserted_index - 1) / 2], container[inserted_index])) {
            std::swap(container[(inserted_index - 1) / 2], container[inserted_index]);
            inserted_index = (inserted_index - 1) / 2;
        }
    }

    /**
    * 힙의 루트의 값을 제거합니다.
    * 루트의 값은 가장 아래의 자식의 값으로 채우고 빈 자식은 삭제합니다.
    * 만약 힙이 비어있다면 오류를 반환하며 프로그램을 종료합니다.
    */
    void pop() {
        std::size_t removed_index = size - 1;

        size -= 1; // 크기를 1 감소시킵니다.

        if (size != 0) {
            std::swap(container[0], container[removed_index]);

            // 힙의 규칙을 만족하도록 값을 바꿔줍니다. (DownHeap)
            std::size_t parent_index = 0;
            while (parent_index * 2 + 1 < size) {
                std::size_t compared_index;
                if (parent_index * 2 + 2 < size) { // 자식 노드가 두 개라면 왼쪽과 오른쪽 중 더 작은 값을 가진 노드와 부모 노드를 비교해야 합니다.
                    compared_index = comp(container[parent_index * 2 + 2], container[parent_index * 2 + 1]) ? parent_index * 2 + 1 : parent_index * 2 + 2;
                } else { // 자식 노드가 한 개라면 왼쪽 노드와 부모 노드를 비교하면 됩니다.
                    compared_index = parent_index * 2 + 1;
                }

                if (comp(container[parent_index], container[compared_index])) {
                    std::swap(container[parent_index], container[compared_index]);
                    parent_index = compared_index;
                } else {
                    break;
                }
            }
        }
    }

    /**
     * 힙의 루트의 값을 반환합니다.
     * 만약 반환할 값이 없다면 `T()`를 반환합니다.
     * @return 힙의 루트의 값
     */
    value_type top() const {
        if (size >= 1) {
            return container[0];
        }
        return T();
    }

private:
    T* container;
    std::size_t capacity;
    std::size_t size;
    Compare comp;
};

/**
 * 완전 이진 트리로 구현되는 힙 클래스
 * @tparam T 힙에 담을 타입
 * @param cmp 힙 원소 비교자
 */
template<typename T, typename Compare = std::greater<T>>
class LinkedHeap {
public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;

    /** 완전 이진 트리의 노드 클래스 */
    struct Node {
        /** 노드 값 */
        value_type value;

        /** 노드의 부모 노드 */
        Node* parent;

        /** 노드의 좌측 자식 노드 */
        Node* left_child;

        /** 노드의 우측 자식 노드 */
        Node* right_child;
    };

    /** 완전 이진 트리의 루트 노드 */
    Node* root;

    /**
     * 힙을 생성합니다.
     * @param cmp 힙 원소 비교자
     */
    explicit LinkedHeap(const Compare& compare = Compare())
    : root(nullptr), comp(compare) {}

    /**
     * 힙의 소멸자입니다.
     */
    ~LinkedHeap() {
        while (root != nullptr) {
            pop();
        }
    }

    /**
     * 완전 이진 트리에 값을 삽입합니다.
     * @param value 완전 이진 트리에 넣을 값
     */
    void push(const_reference value) {
        // 삽입할 값을 동적할당된 노드에 저장합니다.
        Node* inserted_node = new Node{
            value,
            nullptr,
            nullptr,
            nullptr,
        };

        if (root == nullptr) { // 루트 노드가 없다면 루트 노드에 노드를 추가합니다.
            root = inserted_node;
        } else {
            // 큐를 이용해 노드를 삽입할 자리를 찾습니다.
            std::queue<Node*> node_queue; // BFS(너비 우선 탐색)
            node_queue.push(root);
            while (!node_queue.empty()) {
                Node* parent_node = node_queue.front();
                node_queue.pop();

                if (parent_node->left_child == nullptr) { // 왼쪽에 자식 노드가 없으면
                    // 노드를 삽입하고 반복문을 종료합니다.
                    parent_node->left_child = inserted_node;
                    inserted_node->parent = parent_node;
                    break;
                } else if (parent_node->right_child == nullptr) { // 오른쪽에 자식 노드가 없으면
                    // 노드를 삽입하고 반복문을 종료합니다.
                    parent_node->right_child = inserted_node;
                    inserted_node->parent = parent_node;
                    break;
                } else {
                    node_queue.push(parent_node->left_child);
                    node_queue.push(parent_node->right_child);
                }
            }

            // 힙의 규칙을 만족하도록 값을 바꿔줍니다. (UpHeap)
            while (inserted_node->parent != nullptr && comp(inserted_node->parent->value, inserted_node->value)) {
                std::swap(inserted_node->parent->value, inserted_node->value);
                inserted_node = inserted_node->parent;
            }
        }
    }

    /**
     * 완전 이진 트리의 루트 노드의 값을 제거합니다.
     * 루트 노드의 값은 가장 아래의 자식 노드의 값으로 채우고 빈 자식 노드는 삭제합니다.
     * 만약 트리가 비어있다면 오류를 반환하며 프로그램을 종료합니다.
     */
    void pop() {
        // 마지막에 나오는 노드가 완전 이진 트리의 마지막 노드입니다.
        Node* removed_node;
        std::queue<Node*> node_queue; // BFS(너비 우선 탐색)
        node_queue.push(root);
        while (!node_queue.empty()) {
            removed_node = node_queue.front();
            node_queue.pop();

            if (removed_node->left_child != nullptr) { // 왼쪽에 자식 노드가 존재하면
                node_queue.push(removed_node->left_child);
            }
            if (removed_node->right_child != nullptr) { // 오른쪽에 자식 노드가 존재하면
                node_queue.push(removed_node->right_child);
            }
        }
        // 완전 이진 트리의 마지막 노드는 삭제해야 될 노드입니다.

        if (removed_node != root) { // 삭제할 노드가 루트 노드인지 확인합니다.
            std::swap(root->value, removed_node->value); // 삭제할 노드와 루트 노드의 값을 바꿉니다.
            // 더이상 필요없는 노드를 삭제하기 위해 삭제할 노드의 부모 노드를 수정합니다.
            if (removed_node->parent->left_child == removed_node) {
                removed_node->parent->left_child = nullptr;
            } else {
                removed_node->parent->right_child = nullptr;
            }

            // 힙의 규칙을 만족하도록 값을 바꿔줍니다. (DownHeap)
            Node* parent_node = root;
            while (parent_node->left_child != nullptr) {
                Node* compared_node;
                if (parent_node->right_child != nullptr) { // 자식 노드가 두 개라면 왼쪽과 오른쪽 중 더 작은 값을 가진 노드와 부모 노드를 비교해야 합니다.
                    compared_node = comp(parent_node->right_child->value, parent_node->left_child->value) ? parent_node->left_child : parent_node->right_child;
                } else { // 자식 노드가 한 개라면 왼쪽 노드와 부모 노드를 비교하면 됩니다.
                    compared_node = parent_node->left_child;
                }

                if (comp(parent_node->value, compared_node->value)) {
                    std::swap(parent_node->value, compared_node->value);
                    parent_node = compared_node;
                } else {
                    break;
                }
            }
        } else {
            root = nullptr; // 루트 노드라면 위와 같은 과정이 필요없습니다.
        }
        delete removed_node; // 사용한 노드를 메모리에서 해지합니다.
    }

    /**
     * 완전 이진 트리의 루트 노드의 값을 반환합니다.
     * 만약 반환할 값이 없다면 오류를 반환하며 프로그램을 종료합니다.
     * @return 트리의 루트 노드의 값
     */
    value_type top() const {
        return root->value;
    }

private:
    /** 힙 원소 비교자 객체 */
    Compare comp;
};

#endif // ICE2004_WEEK15_HW01_HEAP_H
