// 중복 삽입 방지를 위한 Define Guard
#ifndef ICE2004_WEEK14_HW01_TRAVERSAL_H
#define ICE2004_WEEK14_HW01_TRAVERSAL_H

#include <iostream>
#include "heap.h"

/**
 * PreOrder 방식으로 이진 트리를 순회하는 함수입니다.
 * @tparam T 이진 트리에 담을 타입
 * @param node 이진 트리의 루트 노드
 */
template<typename T>
void preorder_traversal(const typename LinkedHeap<T>::Node* node) {
    std::cout << node->value << ' ';
    if (node->left_child != nullptr) {
        preorder_traversal<T>(node->left_child);
    }
    if (node->right_child != nullptr) {
        preorder_traversal<T>(node->right_child);
    }
}

/**
 * InOrder 방식으로 이진 트리를 순회하는 함수입니다.
 * @tparam T 이진 트리에 담을 타입
 * @param node 이진 트리의 루트 노드
 */
template<typename T>
void inorder_traversal(const typename LinkedHeap<T>::Node* node) {
    if (node->left_child != nullptr) {
        inorder_traversal<T>(node->left_child);
    }
    std::cout << node->value << ' ';
    if (node->left_child != nullptr && node->right_child != nullptr) {
        inorder_traversal<T>(node->right_child);
    }
}

/**
 * PostOrder 방식으로 이진 트리를 순회하는 함수입니다.
 * @tparam T 이진 트리에 담을 타입
 * @param node 이진 트리의 루트 노드
 */
template<typename T>
void postorder_traversal(const typename LinkedHeap<T>::Node* node) {
    if (node->left_child != nullptr) {
        postorder_traversal<T>(node->left_child);
    }
    if (node->right_child != nullptr) {
        postorder_traversal<T>(node->right_child);
    }
    std::cout << node->value << ' ';
}

#endif // ICE2004_WEEK14_HW01_TRAVERSAL_H
