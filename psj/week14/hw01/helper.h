#ifndef ICE2004_WEEK15_HW01_HELPER_H
#define ICE2004_WEEK15_HW01_HELPER_H

#include <cstddef>
#include <iostream>
#include <random>
#include <utility>

/**
 * 주어진 크기를 갖는 임의의 배열을 생성합니다.
 * @tparam Int 배열 원소의 타입(정수)
 * @param out 배열
 * @param n 배열의 크기
 * @param max 배열 원소의 최댓값
 */
template<typename Int = int>
void generate_random_array(Int* out, std::size_t n, Int max = 100) {
    std::random_device rd;
    std::mt19937 gen(rd()); // 메르센 트위스터 알고리즘을 이용해 난수를 생성합니다.
    std::uniform_int_distribution<Int> distrib(0, max); // 균등 분포 난수를 생성합니다.
    for (std::size_t i = 0; i < n; i += 1) {
        out[i] = distrib(gen);
    }
}

/**
 * 배열을 표준출력스트림으로 출력합니다.
 * @tparam T 배열 원소의 타입
 * @param array 배열
 * @param size 배열의 크기
 */
template<typename T>
void print_array(const T* array, std::size_t size) {
    for (std::size_t i = 0; i < size; i += 1) {
        std::cout << array[i] << ' ';
    }
}

#endif // ICE2004_WEEK15_HW01_HELPER_H
