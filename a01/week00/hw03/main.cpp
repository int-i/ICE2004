#include <iostream>
#include "list.h"

int list_sum1(const DLinkedList<int>& l) {
    int sum = 0;
    for (int i = 0; i < l.size(); i += 1) {
        sum += l[i];
    }
    return sum;
}

int list_sum2(DLinkedList<int>& l) {
    using Iterator = DLinkedList<int>::iterator;
    int sum = 0;
    for (Iterator it = l.begin(); it != l.end(); ++it) {
        sum += *it;
    }
    return sum;
}

int list_sum3(const DLinkedList<int>& l) {
    using ConstIterator = DLinkedList<int>::const_iterator;
    int sum = 0;
    for (ConstIterator it = l.cbegin(); it != l.cend(); ++it) {
        sum += *it;
    }
    return sum;
}

int main() {
    DLinkedList<int> l;
    for (int i = 1; i <= 10; i += 1) {
        l.push_back(i);
    }

    std::cout << "list_sum1: " << list_sum1(l) << std::endl;
    std::cout << "list_sum2: " << list_sum2(l) << std::endl;
    std::cout << "list_sum3: " << list_sum3(l) << std::endl;
    return 0;
}
