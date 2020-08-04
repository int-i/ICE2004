#include <iostream>

void add_by_value(int a, int b, int c);
void add_by_pointer(int a, int b, int* c);
void add_by_reference(int a, int b, int& c);

int main() {
    int a = 3;
    int b = 9;
    int c = 0; // a+b의 결과가 저장되는 변수, c=a+b
    add_by_value(a, b, c);
    std::cout << "add_by_value() 호출 후 c=" << c << "입니다.\n";
    add_by_pointer(a, b, &c);
    std::cout << "add_by_pointer() 호출 후 c=" << c << "입니다.\n";
    b = 13;
    add_by_reference(a, b, c);
    std::cout << "add_by_reference() 호출 후 c=" << c << "입니다.\n";
    return 0;
}

void add_by_value(int a, int b, int c) {
    c = a + b;
}

void add_by_pointer(int a, int b, int* c) {
    *c = a + b;
}

void add_by_reference(int a, int b, int& c) {
    c = a + b;
}
