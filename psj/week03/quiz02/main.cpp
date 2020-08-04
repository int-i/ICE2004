#include <iostream>

void increment_by_value(int);
void increment_by_reference1(int*);
void increment_by_reference2(int&);

int main() {
    int number = 10;
    std::cout << "number = " << number << "\n\n";

    increment_by_value(number);
    std::cout << "1을 증가하는 함수(값으로 전달)를 호출하였으나 변하지 않는다.\n";
    std::cout << "number = " << number << "\n\n";

    increment_by_reference1(&number);
    std::cout << "1을 증가하는 함수(포인터로 전달)를 호출하니 1이 증가한다.\n";
    std::cout << "number = " << number << "\n\n";

    increment_by_reference2(number);
    std::cout << "1을 증가하는 함수(레퍼런스로 전달)를 호출하니 1이 증가한다.\n";
    std::cout << "number = " << number << "\n\n";
    return 0;
}

void increment_by_value(int number) {
    number++;
}

void increment_by_reference1(int* number) {
    (*number)++;
}

void increment_by_reference2(int& number) {
    number++;
}
