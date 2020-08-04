#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include "heap.h"
#include "helper.h"
#include "sort.h"
#include "traversal.h"

void test_heap();
void test_heap_sort(std::size_t size);
void encode_huffman(const std::string& input);
void test_heap_traversal();

int main() {
    // std::cout << "<Test Heap>" << std::endl;
    // test_heap();
    // std::cout << std::endl;

    std::cout << "<Test Heap Sort>" << std::endl;
    test_heap_sort(10);
    std::cout << std::endl;
    test_heap_sort(25);
    std::cout << std::endl;
    test_heap_sort(50);
    std::cout << std::endl;

    std::cout << "<Traversal Heap Tree>" << std::endl
              << "Heap: 1 to 15" << std::endl;
    test_heap_traversal();
    std::cout << std::endl;

    std::cout << "<Solve Huffman Coding>" << std::endl;
    std::string input0 = "ababcbbbc";
    std::cout << "input: " << input0 << std::endl
              << "output: ";
    encode_huffman(input0);
    std::cout << std::endl;

    std::string input1 = "qwteqrqtwre";
    std::cout << "input: " << input1 << std::endl
              << "output: ";
    encode_huffman(input1);
    std::cout << std::endl;

    std::string input2 = "bbbbbeeeeeeeeeeccccccccccccaaaaaaaaaaaaaaaadddddddddddddddddfffffffffffffffffffffffff";
    std::cout << "input: " << input2 << std::endl
              << "output: ";
    encode_huffman(input2);
    std::cout << std::endl;

    return 0;
}

void test_heap() {
    ArrayHeap<int> heap(5);

    std::cout << "push: 3" << std::endl;
    heap.push(3);
    std::cout << "top: " << heap.top() << std::endl;

    std::cout << "push: 5" << std::endl;
    heap.push(5);
    std::cout << "top: " << heap.top() << std::endl;

    std::cout << "push: 2" << std::endl;
    heap.push(2);
    std::cout << "top: " << heap.top() << std::endl;

    std::cout << "push: 4" << std::endl;
    heap.push(4);
    std::cout << "top: " << heap.top() << std::endl;

    std::cout << "push: 1" << std::endl;
    heap.push(1);
    std::cout << "top: " << heap.top() << std::endl
              << std::endl;

    for (int i = 0; i < 5; i += 1) {
        std::cout << "top: " << heap.top() << std::endl
                  << "pop " << std::endl;
        heap.pop();
    }
}

// 임의의 n개의 데이터를 이용하여 Heap Sort가 정상동작 하는 것을 보일 것
void test_heap_sort(std::size_t size) {
    int random_array[100];
    generate_random_array(random_array, size, 100); // 주어진 크기로 임의의 배열을 생성합니다.
    std::cout << "input: ";
    print_array(random_array, size);
    std::cout << std::endl;

    heap_sort(random_array, size);
    std::cout << "output(heap sort - array): ";
    print_array(random_array, size);
    std::cout << std::endl;

    heap_sort2(random_array, size);
    std::cout << "output(heap sort - complete binary tree): ";
    print_array(random_array, size);
    std::cout << std::endl;
}

// Heap을 PreOrder, InOrder, PostOrder 형태로 출력하는 함수도 구현하여 정상출력되는 것을 보일 것
void test_heap_traversal() {
    LinkedHeap<int> heap;
    for (int i = 1; i <= 15; i += 1) {
        heap.push(i);
    }

    std::cout << "PreOrder: ";
    preorder_traversal<int>(heap.root);
    std::cout << std::endl;

    std::cout << "InOrder: ";
    inorder_traversal<int>(heap.root);
    std::cout << std::endl;

    std::cout << "PostOrder: ";
    postorder_traversal<int>(heap.root);
    std::cout << std::endl;
}

// 허프만 트리의 노드입니다.
struct HuffmanNode {
    char symbol;
    int frequency;
    HuffmanNode* left_child;
    HuffmanNode* right_child;
};

// 허프만 트리를 순회하는 함수입니다.
void traversal_huffman_tree(const HuffmanNode* node, std::unordered_map<char, std::string>& encode_map, const std::string& accumulator = "") {
    if (node->left_child != nullptr) {
        traversal_huffman_tree(node->left_child, encode_map, accumulator + '0');
    }
    if (node->right_child != nullptr) {
        traversal_huffman_tree(node->right_child, encode_map, accumulator + '1');
    }
    if (node->left_child == nullptr && node->right_child == nullptr) {
        encode_map[node->symbol] = accumulator;
    }
    delete node;
}

// 위에서 작성한 Heap을 바탕으로 Huffman Coding을 구현할 것
void encode_huffman(const std::string& input) {
    // 문자의 빈도 수를 계산합니다.
    std::unordered_map<char, int> frequencies; // <symbol, frequency>
    for (char c : input) {
        frequencies[c] += 1;
    }

    // 힙에서 사용하는 허프만 노드의 빈도수 비교자입니다.
    auto compare_huffman_node = [](const HuffmanNode* a, const HuffmanNode* b) {
        return a->frequency > b->frequency;
    };

    // 힙에 허프만 노드를 삽입합니다.
    LinkedHeap<HuffmanNode*, decltype(compare_huffman_node)> priority_queue(compare_huffman_node);
    for (const auto& frequency : frequencies) {
        priority_queue.push(new HuffmanNode{ frequency.first, frequency.second, nullptr, nullptr });
    }

    // 허프만 코딩을 위한 트리를 구축합니다.
    for (int i = 1; i < frequencies.size(); i += 1) {
        auto p = priority_queue.top();
        priority_queue.pop();

        auto q = priority_queue.top();
        priority_queue.pop();

        auto r = new HuffmanNode{ '\0', p->frequency + q->frequency, q, p };
        priority_queue.push(r);
    }

    // 허프만 트리를 이용해 문자별로 비트를 할당해줍니다.
    std::unordered_map<char, std::string> encode_map;
    traversal_huffman_tree(priority_queue.top(), encode_map);

    // 입력된 문자열을 허프만 인코딩해 출력합니다.
    for (char c : input) {
        std::cout << encode_map[c];
    }
    std::cout << " - ";
    for (const auto& encode : encode_map) {
        std::cout << encode.first << ": " << encode.second << ' ';
    }
    std::cout << std::endl;
}
