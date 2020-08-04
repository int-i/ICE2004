# Class Inheritance and Operator Overloading

## Homework

### 1. 아래와 같은 클래스 다이어그램을 구현하고 주어진 `main` 함수와 같이 동작하도록 구현한다.

```cpp
#include "DVD.h"
#include "LegalDVD.h"
#include "Media.h"
#include "VTR.h"

// 주석점수 10점
// 보고서 점수 20점
// `static int count`값을 0으로 초기화 (10점)

int main() {
    Media* mp[4];
    // `new` 할때마다 `count` 증가하도록 구현 (10점)
    mp[0] = new VTR("Hello", 15, "avi");
    mp[1] = new DVD("Superman", 3, "123-9899");
    mp[2] = new LegalDVD("Marvel", 10, "456-9899", "GG entertainment");
    mp[3] = new VTR("Disney", 23, "mkv");
    for (int i = 0; i < "count을 이용"; i++) // 다형성 구현 (20점)
        mp[i]->play();
    cout << "연산자 오버로딩 실습" << endl;
    cout << mp[0]; // "VTR이 play되고 있습니다."가 출력되도록 연산자 오버로딩 구현(30점)
    mp[3] = *mp[1] + mp[2]; //`mp[1]`의 `length`+`mp[2]`의 `length`가 되게끔 오버로딩 (30점)
    cout << mp[3]->getLength() << endl; // 출력값은 13
    return 0; // `new`한 객체들이 잘 소멸되는지 보일 것 (20점)
}
```

See [HW 1](./hw01/)
