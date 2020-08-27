# Midterm Exam

## Practice

### 1. STL에서 제공하는 `stack`을 상속받는 `Stack` 클래스를 아래의 요구사항에 맞게 구현하시오. (50점)

#### 1) `pop` 함수 구현 (30점)

주어진 `problem1` 함수가 에러 없이 실행가능하도록 `pop` 함수를 오버로딩하시오.

- try-catch 문을 이용하여 예외처리 하고 예외발생시 메시지를 출력하고 정상종료 하도록 할 것.
- `StackEmpty` 클래스를 만들어서 예외처리 할 것, `Stack` 클래스의 `pop` 함수에서 값을 리턴 받도록 구현 할 것.)

See [Sol. 1-1](./sol01_01/main.cpp)

```text
1
Stack is empty!
```

#### 2. `top` 함수 구현 (20점)

`try-catch` 문을 이용하여 주어진 `problem2` 함수가 에러 없이 실행가능하도록 `top` 함수를 오버로딩하시오.

See [Sol. 1-2](./sol01_02/main.cpp)

```text
Stack is empty!
```

### 2. 위 문제에서 구현한 `Stack`을 이용하여 `problem3` 함수가 에러없이 정상실행 할 수 있도록 괄호매칭 알고리즘을 `bool is_valid_paren(const std::string&)`에 구현하시오. (40점)

See [Sol. 2](./sol02/main.cpp)

```text
(name):[studentid]: correct
(ice2004: incorrect
({[ ])}: incorrect
)(( )){([( )])}: incorrect
((( )ice2004(( )){([( )])}: incorrect
( )([ ]){([(ice2004)])}: correct
Stack is empty!
```

### 3. (객관식:단일정답) STL에서 제공하는 `stack`는 어떤 자료구조를 이용하여 구현되었는가? (10점)

1. array
2. singly linked list
3. queue
4. deque

Answer: 4
