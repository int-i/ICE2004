#include <algorithm>
#include <chrono>
#include <iostream>
#include <utility>
#include "helper.h"
#include "sort.h"

#define MAX_ARRAY_SIZE 100000000

// 배열의 크기가 매우 크기 때문에 전역에 선언합니다.
int random_array[MAX_ARRAY_SIZE];
int test_array[MAX_ARRAY_SIZE];

void test_array_sort(std::size_t size);
void check_stable_sort();
void bench_array_sort(std::size_t size);

int main() {
    std::cout << "<Test Array Sort Algorithm>" << std::endl;
    test_array_sort(10);
    std::cout << std::endl;
    test_array_sort(25);
    std::cout << std::endl;
    test_array_sort(50);
    std::cout << std::endl;

    std::cout << "<Check Stable Algorithm>" << std::endl;
    check_stable_sort();
    std::cout << std::endl;

    std::cout << "<Bench Array Sort Algorithm>" << std::endl;
    bench_array_sort(1000); // 1천
    std::cout << std::endl;
    bench_array_sort(2000); // 2천
    std::cout << std::endl;
    bench_array_sort(3000); // 3천
    std::cout << std::endl;
    bench_array_sort(4000); // 4천
    std::cout << std::endl;
    bench_array_sort(5000); // 5천
    std::cout << std::endl;
    bench_array_sort(10000); // 1만
    std::cout << std::endl;
    bench_array_sort(100000); // 10만
    std::cout << std::endl;
    bench_array_sort(1000000); // 100만
    std::cout << std::endl;
    bench_array_sort(10000000); // 1000만
    std::cout << std::endl;
    bench_array_sort(100000000); // 1억
    return 0;
}

// 각 정렬 알고리즘 작성한 후 정렬이 정상 동작함을 보일 것
void test_array_sort(std::size_t size) {
    generate_random_array(random_array, size, 100);  // 주어진 크기로 임의의 배열을 생성합니다.
    std::cout << "input: ";
    print_array(random_array, size);
    std::cout << std::endl;

    std::copy(random_array, random_array + size, test_array);
    insert_sort(test_array, size);
    std::cout << "output(insert sort): ";
    print_array(test_array, size);
    std::cout << std::endl;

    std::copy(random_array, random_array + size, test_array);
    merge_sort(test_array, size);
    std::cout << "output(merge sort): ";
    print_array(test_array, size);
    std::cout << std::endl;

    std::copy(random_array, random_array + size, test_array);
    quick_sort(test_array, size);
    std::cout << "output(quick sort): ";
    print_array(test_array, size);
    std::cout << std::endl;
}

// 중복을 허용하여 10개 정도의 원소로 이루어진 데이터셋을 임의로 구성하여 각 알고리즘이 stable한 지를 제시할 것
void check_stable_sort() {
    using pair = std::pair<int, char>; // 타입을 사용하기 편하게 `pair`로 정의했습니다.
    pair random_pairs[10] = {
        { 2, 'a' },
        { 1, 'b' },
        { 2, 'c' },
        { 1, 'd' },
        { 5, 'e' },
        { 3, 'f' },
        { 4, 'g' },
        { 3, 'h' },
        { 5, 'i' },
        { 4, 'j' }
    };
    std::size_t size = sizeof(random_pairs) / sizeof(*random_pairs);
    pair test_pairs[10];

    // `pair`에 대한 비교자입니다.
    auto cmp = [](const pair& a, const pair& b) {
        return a.first < b.first;
    };

    std::copy(random_pairs, random_pairs + size, test_pairs);
    insert_sort(test_pairs, size, cmp);
    std::cout << "output(insert sort): ";
    print_array(test_pairs, size);
    std::cout << std::endl;

    std::copy(random_pairs, random_pairs + size, test_pairs);
    merge_sort(test_pairs, size);
    std::cout << "output(merge sort): ";
    print_array(test_pairs, size);
    std::cout << std::endl;

    std::copy(random_pairs, random_pairs + size, test_pairs);
    quick_sort(test_pairs, size);
    std::cout << "output(quick sort): ";
    print_array(test_pairs, size);
    std::cout << std::endl;
}

// 데이터셋을 임의로 생성하고 데이터셋의 크기를 변화시켜가면서 세 알고리즘의 성능을 비교할 것
void bench_array_sort(std::size_t size) {
    std::cout << "size: " << size << std::endl;
    generate_random_array(random_array, size, MAX_ARRAY_SIZE); // 주어진 크기로 임의의 배열을 생성합니다.

    std::chrono::system_clock::time_point start_time, end_time; // 알고리즘의 시간을 시작/종료 시각을 기록하기 위한 변수입니다.

    if (size <= 100000) { // 10만개가 넘어가면 삽입 정렬은 너무 오래걸리기 때문에 측정하지 않습니다.
        std::copy(random_array, random_array + size, test_array);
        start_time = std::chrono::system_clock::now(); // 시작 시각
        insert_sort(test_array, size);
        end_time = std::chrono::system_clock::now(); // 종료 시각
        std::cout << "output(insert sort): " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << "ns" << std::endl; // (종료 시각 - 시작 시각)을 나노초[ns]로 나타냅니다.
    }

    std::copy(random_array, random_array + size, test_array);
    start_time = std::chrono::system_clock::now();
    merge_sort(test_array, size);
    end_time = std::chrono::system_clock::now();
    std::cout << "output(merge sort): " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << "ns" << std::endl;

    std::copy(random_array, random_array + size, test_array);
    start_time = std::chrono::system_clock::now();
    quick_sort(test_array, size);
    end_time = std::chrono::system_clock::now();
    std::cout << "output(quick sort): " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << "ns" << std::endl;
}
