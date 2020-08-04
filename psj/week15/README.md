# Final Exam

> 문제 유형만 같으며, 일부 문제가 누락됨

## Theory

### 1. Write the execution result of the code below, and describe how to modify it to print the intended output.

```cpp
#include <iostream>

class A {
public:
    void get_a() const {
        std::cout << 'A' << std::endl;
    }
};

class B : public A {
public:
    void get_a() const {
        std::cout << 'A' << std::endl;
    }
};

class C : public A {
public:
    void get_a() const {
        std::cout << 'A' << std::endl;
    }
};

class D : public A {
public:
    void get_a() const {
        std::cout << 'A' << std::endl;
    }
};

int main() {
    A a;
    B b;
    C c;
    D d;

    A objects[] = { a, b, c, d };

    for (int i = 0; i < 4; i += 1) {
        objects[i].get_a();
    }
    return 0;
}
```

Answer:

```text
A
A
A
A
```

Declare `A`'s `get_a` as `virtual`, so define it as a virtual function.

### 2. Prove that the following operation has a given time complexity.

#### 1. n^3+nlogn is O(n^3)

#### 2. 5*2^n+n^2 is O(2^n)

### 3. Find the complexity of the code below.

```cpp
int special(const int* array, int p, int r) {
    if (p == r) {
        return 0;
    }
    int sum = 0;
    for (int i = p; i < r; i += 1) {
        sum += array[i];
    }
    int q = (p + r) / 2;
    return sum + special(array, p, q) + special(array, q + 1, r);
}
```

Answer:

- Time Complexity: O(nlogn)

### 4. Show the process of converting a infix expression to postfix expression with below operator priority table.

Input: ((a#b)$c^d)

| Operator | PIS | PIE |
| -------- | --- | --- |
| )        | -   | -   |
| ^        | 3   | 3   |
| #        | 2   | 2   |
| $        | 1   | 1   |
| (        | 0   | 4   |

Answer: ab#cd^$

### 5. Implement `removeLastBefore` with reference to the `removeLast` member function.

```cpp
void removeLast() throw(StackEmptyException) {
    if (size == 0) {
        throw StackEmptyException();
    }
    Node* old = trailer->prev;
    Node* new_last = old->prev;
    trailer->prev = new_last;
    new_last->next = trailer;
    size -= 1;
    delete old;
}
```

Answer:

```cpp
void removeLastBefore() throw(StackRemoveFailException) {
    if (size <= 1) {
        throw StackRemoveFailException();
    }
    Node* old = trailer->prev->prev;
    Node* new_last = old->prev;
    trailer->prev->prev = new_last;
    new_last->next = trailer->prev;
    size -= 1;
    delete old;
}
```

### 6. Draw a binary tree that satisfies the following conditions.

1. Traversing the tree as preorder is `FUNEMXA`.
2. Traversing the tree as inorder is `FUNEMXA`.

Answer:

```text
      F
     / \
    U   A
   / \
  N   X
 / \
E   M
```

### 7. Draw the shape of the binary tree when you delete 6 from the tree below.

```text
        1
      /   \
    5       3
   / \     / \
  2   6   7  10
 / \   \
8   9   4
       / \
      11 12
```

Answer:

```text
        1
      /   \
    5       3
   / \     / \
  2   11  7  10
 / \   \
8   9   4
         \
         12
```

### 8. Solve the problem below using the given 2-3 tree.

#### 1. Draw the shape of the tree when you add 10 to the tree.

#### 2. After (1), Draw the shape of the tree when you delete 7 from the tree.

### 9. Solve the problem below about the heap.

#### 1. Write three conditions of the heap.

Answer:

1. degree = 2
2. Complete Binary Tree
3. parent node <= child node (min heap)

#### 2. Draw the shape of the **max** heap tree when `{5, 1, 9, 7, 3}` is inserted in the heap.

Answer:

```text
    9
   / \
  7   5
 / \
1   3
```

#### 3. After (2), describe the process of **max** heap sorting.

Answer:

```text
    3
   / \
  7   5
 /
1
```

```text
    7
   / \
  3   5
 /
1
```

```text
  1
 / \
3   5
```

```text
  5
 / \
3   1
```

```text
  1
 /
3
```

```text
  3
 /
1
```

```text
1
```
