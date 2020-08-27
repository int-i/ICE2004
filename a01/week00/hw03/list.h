#ifndef ICE2004_WEEK00_HW03_LIST_H
#define ICE2004_WEEK00_HW03_LIST_H

#include <cstddef>
#include <iterator>
#include <list>

template<typename T>
class DLinkedList {
public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;

    struct Node {
        T value;
        Node* prev;
        Node* next;
    };

    struct Iterator {
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using pointer = value_type*;
        using reference = value_type&;

        explicit Iterator(Node* node)
        : node(node) {}

        Iterator& operator++() {
            if (node) {
                node = node->next;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator it = *this;
            ++(*this);
            return it;
        }

        pointer operator->() {
            return &(node->value);
        }

        reference operator*() {
            return node->value;
        }

        bool operator==(const Iterator& it) {
            return node == it.node;
        }

        bool operator!=(const Iterator& it) {
            return node != it.node;
        }

        Node* node;
    };

    struct ConstIterator {
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using pointer = const value_type*;
        using reference = const value_type&;

        explicit ConstIterator(Node* node)
        : node(node) {}

        ConstIterator& operator++() {
            if (node) {
                node = node->next;
            }
            return *this;
        }

        ConstIterator operator++(int) {
            Iterator it = *this;
            ++(*this);
            return it;
        }

        pointer operator->() {
            return &(node->value);
        }

        reference operator*() {
            return node->value;
        }

        bool operator==(const ConstIterator& it) {
            return node == it.node;
        }

        bool operator!=(const ConstIterator& it) {
            return node != it.node;
        }

        Node* node;
    };

    using iterator = Iterator;
    using const_iterator = ConstIterator;

    DLinkedList()
    : header(new Node), trailer(new Node), count(0) {
        connect(header, trailer);
    }

    DLinkedList(const DLinkedList& list) {
        if (this != &list) {
            header = new Node;
            trailer = new Node;
            count = 0;

            Node* node = header->next;
            while (node != trailer) {
                push_back(node->value);
                node = node->next;
            }
        }
    }

    ~DLinkedList() {
        while (!empty()) {
            pop_back();
        }
        delete header;
        delete trailer;
    }

    DLinkedList& operator=(const DLinkedList& rhs) {
        if (this != &rhs) {
            header = new Node;
            trailer = new Node;
            count = 0;

            Node* node = header->next;
            while (node != trailer) {
                push_back(node->value);
                node = node->next;
            }
        }
        return *this;
    }

    reference operator[](std::size_t idx) {
        Node* node = header;
        for (int i = 0; i <= idx; i += 1) {
            node = node->next;
        }
        return node->value;
    }

    const_reference operator[](std::size_t idx) const {
        Node* node = header;
        for (int i = 0; i <= idx; i += 1) {
            node = node->next;
        }
        return node->value;
    }

    bool empty() const {
        return header->next == trailer;
    }

    size_type size() const {
        return count;
    }

    const_reference front() const {
        return header->next->value;
    }

    const_reference back() const {
        return trailer->prev->value;
    }

    void push_front(const_reference value) {
        insert(header->next, value);
        count += 1;
    }

    void push_back(const_reference value) {
        insert(trailer, value);
        count += 1;
    }

    void pop_front() {
        remove(header->next);
        count -= 1;
    }

    void pop_back() {
        remove(trailer->prev);
        count -= 1;
    }

    iterator begin() {
        return Iterator(header->next);
    }

    iterator end() {
        return Iterator(trailer);
    }

    const_iterator cbegin() const {
        return ConstIterator(header->next);
    }

    const_iterator cend() const {
        return ConstIterator(trailer);
    }

protected:
    void connect(Node* a, Node* b) {
        a->next = b;
        b->prev = a;
    }

    void insert(Node* where, const_reference value) {
        Node* new_node = new Node;
        new_node->value = value;
        connect(where->prev, new_node);
        connect(new_node, where);
    }

    void remove(Node* target) {
        connect(target->prev, target->next);
        delete target;
    }

private:
    Node* header;
    Node* trailer;
    size_type count;
};

#endif // ICE2004_WEEK00_HW03_LIST_H
