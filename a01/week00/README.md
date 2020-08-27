# Assignment

## Homework

### 1. 주어진 의사코드의 시간/공간 복잡도를 계산하시오.

```text
Algorithm BinaryFibonacci(k)
    Input: An integer k
    Output: The k-th Fibonacci number
    if k <= 1 then
        return k
    else
        return BinaryFibonacci(k - 1) + BinaryFibonacci(k - 2)
```

Answer:

- Time Complexity: O(2^n)
- Space Complexity: O(n)

~~Multiply and Surrender Algorithm~~

### 2. 주어진 의사코드의 시간/공간 복잡도를 계산하시오.

```text
Algorithm LinearFibonacci(k)
    Input: An integer k
    Output: A pair (F_k, F_{k-1})

    if k <= 1 then
        return (k, 0)
    else
        (i, j) <- LinearFibonacci(k - 1)
    return (i + j, i)
```

Answer:

- Time Complexity: O(n)
- Space Complexity: O(n)

### 3. 아래 코드는 `std::vector` 원소들의 합을 구하는 코드이다. 아래 코드와 같은 형식으로 Linked List의 합을 구하는 함수를 만들 때, Linked List가 올바르게 작동하도록 멤버함수와 반복자를 구현하시오.

```cpp
#include <vector>

int vector_sum1(const std::vector<int> &v) {
    int sum = 0;
    for (int i = 0; i < v.size(); i += 1) {
        sum += v[i];
    }
    return sum;
}

int vector_sum2(std::vector<int> &v) {
    using Iterator = std::vector<int>::iterator;
    int sum = 0;
    for (Iterator it = v.begin(); it != v.end(); ++it) {
        sum += *it;
    }
    return sum;
}

int vector_sum3(const std::vector<int> &v) {
    using ConstIterator = std::vector<int>::const_iterator;
    int sum = 0;
    for (ConstIterator it = v.cbegin(); it != v.cend(); ++it) {
        sum += *it;
    }
    return sum;
}
```

See [HW 3](./hw03/)

## Project

### 1. Tree 자료구조를 이용해 가족 족보를 구현하는 프로그램을 작성하시오.

1. 실제 가족 족보(4대 이상)을 구현하시오. (필수 X)
2. 족보 중 같은 대에서 적어도 3명 이상의 형제를 가지는 대(level)을 포함하시오.
3. 가족 구성원을 추가하거나 삭제하는 기능을 제공하시오.
4. 가족 구성원의 이름을 입력하면 몇대손인지 출력하는 기능을 제공하시오.

### 2. 아래 문장에 대해 자료구조를 이용해 허프만 코드를 구현하는 프로그램을 작성하시오.

1. 각 문자, 부호에 대한 허프만 이진 코드를 출력하는 함수를 제공할 것
2. 각 문자, 부호의 사용 빈도를 출력하는 함수를 제공할 것

Input: The Little Prince draws unflattering portraits of grown-ups as being hopelessly narrow-minded. In contrast, children come to wisdom through open-mindedness and a willingness to explore the world around them and within themselves. The main theme of the fable is expressed in the secret that the fox tells the little prince: "It is only with the heart that one can see rightly: what is essential is invisible to the eye."
