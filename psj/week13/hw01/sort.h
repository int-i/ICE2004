#ifndef ICE2004_WEEK13_HW01_SORT_H
#define ICE2004_WEEK13_HW01_SORT_H

#include <algorithm>
#include <cstddef>
#include <functional>

/**
 * 삽입 정렬을 이용해 주어진 배열을 정렬합니다.
 * @tparam T 배열 원소의 타입
 * @tparam Compare 배열 원소 비교자 타입
 * @param array 배열 포인터
 * @param size 배열의 크기
 * @param cmp 배열 원소 비교자
 */
template<typename T, typename Compare = std::less<T>> // 기본 비교자는 오름차순 정렬
void insert_sort(T* array, std::size_t size, Compare cmp = Compare()) {
    for (std::size_t i = 1; i < size; i += 1) {
        const T target = array[i];
        std::size_t j = i - 1;
        while (j < size && cmp(target, array[j])) { // j < size: check array index range
            array[j + 1] = array[j]; // 원소를 한 칸씩 이동시킨다.
            j -= 1;
        }
        array[j + 1] = target;
    }
}

/**
 * 병합 정렬을 이용해 주어진 배열에서 주어진 범위만큼을 정렬합니다.
 * @tparam T 배열 원소의 타입
 * @tparam Compare 배열 원소 비교자 타입
 * @param array 배열 포인터
 * @param start_index 정렬할 부분의 시작 위치
 * @param last_index 정렬할 부분의 마지막 위치
 * @param cmp 배열 원소 비교자
 */
template<typename T, typename Compare = std::less<T>> // 기본 비교자는 오름차순 정렬
void merge_sort_range(T* array, std::size_t start_index, std::size_t last_index, Compare cmp = Compare()) {
    const std::size_t size = last_index - start_index + 1;
    if (size >= 2) {
        std::size_t mid_index = start_index + (size / 2);
        // 배열을 반으로 나눠 정렬합니다.
        merge_sort_range(array, start_index, mid_index - 1, cmp);
        merge_sort_range(array, mid_index, last_index, cmp);
        // 나눠진 배열은 모두 정렬된 상태입니다.

        T* new_array = new T[size]; // 합친 배열을 저장할 공간을 만듭니다.

        // 나눠진 두 배열을 병합합니다.
        std::size_t i = start_index;
        std::size_t j = mid_index;
        std::size_t k = 0;
        while (i <= mid_index - 1 && j <= last_index) {
            if (cmp(array[i], array[j])) {
                new_array[k] = array[i];
                i += 1;
            } else {
                new_array[k] = array[j];
                j += 1;
            }
            k += 1;
        }
        // 아직 병합되지 못한 배열을 마저 병합합니다.
        if (i > mid_index - 1) {
            std::copy(array + j, array + last_index + 1, new_array + k);
        } else {
            std::copy(array + i, array + mid_index, new_array + k);
        }
        std::copy(new_array, new_array + size, array + start_index); // `new_array`의 원소를 `array`로 복사합니다.

        delete[] new_array; // 사용한 메모리를 정렬합니다.
    }
}

/**
 * 병합 정렬을 이용해 주어진 배열을 정렬합니다.
 * @tparam T 배열 원소의 타입
 * @tparam Compare 배열 원소 비교자 타입
 * @param array 배열 포인터
 * @param size 배열의 크기
 * @param cmp 배열 원소 비교자
 */
template<typename T, typename Compare = std::less<T>> // 기본 비교자는 오름차순 정렬
void merge_sort(T* array, std::size_t size, Compare cmp = Compare()) {
    merge_sort_range(array, 0, size - 1, cmp); // 0부터 `size - 1` 만큼을 정렬시킨다.
}

/**
 * 퀵 정렬을 이용해 주어진 배열에서 주어진 범위만큼을 정렬합니다.
 * @tparam T 배열 원소의 타입
 * @tparam Compare 배열 원소 비교자 타입
 * @param array 배열 포인터
 * @param start_index 정렬할 부분의 시작 위치
 * @param last_index 정렬할 부분의 마지막 위치
 * @param cmp 배열 원소 비교자
 */
template<typename T, typename Compare = std::less<T>> // 기본 비교자는 오름차순 정렬
void quick_sort_range(T* array, std::size_t start_index, std::size_t last_index, Compare cmp = Compare()) {
    if (start_index < last_index) {
        const T pivot = array[last_index]; // `pivot`을 배열의 마지막 원소로 지정합니다.
        std::size_t left_index = start_index;
        std::size_t right_index = last_index - 1;

        // `left_index`와 `right_index`을 이동시키며 교차했을 때 원소를 교환합니다.
        while (left_index < right_index) {
            while (left_index <= right_index && left_index < last_index - 1 && cmp(array[left_index], pivot)) { // left_index < last_index - 1: check array index array
                left_index += 1;
            }
            while (left_index <= right_index && right_index > 0 && !cmp(array[right_index], pivot)) { // right_index > 0: check array index array
                right_index -= 1;
            }
            if (left_index < right_index) {
                std::swap(array[left_index], array[right_index]);
            }
        }

        // 만약 `pivot` 극단적으로 크거나 작아 `left_index`와 `right_index`가 오른쪽 끝에 위치했다면 `left_index`을 오른쪽으로 한 칸 이동시킵니다.
        if (left_index == last_index - 1 && left_index == right_index) {
            left_index += 1; // left_index = last_index
        }

        std::swap(array[left_index], array[last_index]); // `left_index`와 `last_index`의 원소를 교환합니다.

        // `pivot`을 기준으로 두 부분으로 나눠진 배열을 각각 정렬합니다.
        if (left_index >= 1) { // check array index array
            quick_sort_range(array, start_index, left_index - 1, cmp);
        }
        quick_sort_range(array, left_index + 1, last_index, cmp);
    }
}

/**
 * 퀵 정렬을 이용해 주어진 배열을 정렬합니다.
 * @tparam T 배열 원소의 타입
 * @tparam Compare 배열 원소 비교자 타입
 * @param array 배열 포인터
 * @param size 배열의 크기
 * @param cmp 배열 원소 비교자
 */
template<typename T, typename Compare = std::less<T>> // 기본 비교자는 오름차순 정렬
void quick_sort(T* array, std::size_t size, Compare cmp = Compare()) {
    quick_sort_range(array, 0, size - 1, cmp); // 0부터 `size - 1` 만큼을 정렬시킨다.
}

#endif // ICE2004_WEEK13_HW01_SORT_H
