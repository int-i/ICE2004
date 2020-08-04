// 중복 삽입 방지를 위한 Define Guard
#ifndef ICE2004_WEEK14_HW01_SORT_H
#define ICE2004_WEEK14_HW01_SORT_H

#include <algorithm>
#include <cstddef>
#include <functional>
#include "heap.h"

/**
 * 힙(배열) 정렬을 이용해 주어진 배열을 정렬합니다.
 * @tparam T 배열 원소의 타입
 * @tparam Compare 배열 원소 비교자 타입
 * @param array 배열 포인터
 * @param size 배열의 크기
 * @param cmp 배열 원소 비교자
 */
template<typename T, typename Compare = std::less<T>> // 기본 비교자는 오름차순 정렬
void heap_sort(T* array, std::size_t size, Compare cmp = Compare()) {
    ArrayHeap<T> heap(size);
    for (std::size_t i = 0; i < size; i += 1) {
        heap.push(array[i]);
    }
    for (std::size_t i = 0; i < size; i += 1) {
        array[i] = heap.top();
        heap.pop();
    }
}

/**
 * 힙(완전 이진 트리) 정렬을 이용해 주어진 배열을 정렬합니다.
 * @tparam T 배열 원소의 타입
 * @tparam Compare 배열 원소 비교자 타입
 * @param array 배열 포인터
 * @param size 배열의 크기
 * @param cmp 배열 원소 비교자
 */
template<typename T, typename Compare = std::less<T>> // 기본 비교자는 오름차순 정렬
void heap_sort2(T* array, std::size_t size, Compare cmp = Compare()) {
    LinkedHeap<T> heap;
    for (std::size_t i = 0; i < size; i += 1) {
        heap.push(array[i]);
    }
    for (std::size_t i = 0; i < size; i += 1) {
        array[i] = heap.top();
        heap.pop();
    }
}

#endif // ICE2004_WEEK14_HW01_SORT_H
