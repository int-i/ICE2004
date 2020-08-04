// 사용할 헤더 정의
#include <iostream>
#include "media.h"

// 프로그램 시작점
int main() {
    // 미디어 클래스 인스턴스 포인터를 저장하는 배열
    Media* media_ptrs[] = {
        // 각 클래스를 동적할당하여 생성
        // 사용 후에는 `delete` 해야 함
        new VTR("Hello", 15, "avi"),
        new DVD("Superman", 3, "123-9899"),
        new LegalDVD("Marvel", 10, "456-9899", "GG entertainment"),
        new VTR("Disney", 23, "mkv"),
    };

    // 추상 메소드 실습
    std::cout << "<Virtual Method Practice>" << std::endl;
    // 배열의 모든 원소를 순회하는 반복문
    for (int i = 0; i < Media::count; i += 1) {
        // 각 미디어를 실행함
        // 원소의 타입은 포인터이기 때문에 화살표 연산자로 접근
        media_ptrs[i]->play();
    }
    std::cout << std::endl;

    // 연산자 오버로딩 실습
    std::cout << "<Operator Overloading Practice>" << std::endl;
    // media_ptrs 원소의 타입은 포인터이기 때문에 `std::ostream& operator<<(std::ostream& out, Media* media_ptr)`을 구현해야 함
    std::cout << "media_ptrs[0]: " << media_ptrs[0] << std::endl;
    // 아래에서 `media_ptrs[3]`를 새로 만들기 때문에 기존에 사용하던 `media_ptrs[3]`는 삭제해야 함
    delete media_ptrs[3];
    // 미디어 길이를 합친 새로운 미디어를 반환하는 `Media* operator+(Media* media_ptr)`을 구현
    // `Media*`를 반환하기 때문에 배열 원소에 바로 할당
    // 오버로딩 함수를 nodiscard 애트리뷰트(attribute)으로 정의했기 때문에 값이 사용되지 않으면 warning 출력
    media_ptrs[3] = *media_ptrs[1] + media_ptrs[2];
    // `get_length()`은 반환타입은 `int`이기 때문에 별도의 연산자 오버로딩이 필요 없음
    std::cout << "media_ptrs[3]->get_length(): " << media_ptrs[3]->get_length() << std::endl; // 3+10=13
    std::cout << std::endl;

    // 소멸자 호출 실습
    std::cout << "<Destructor Call Practice>" << std::endl;
    // 현재 미디어 클래스 객체는 총 4개 있음
    std::cout << "Media::count: " << Media::count << std::endl; // 4
    // 배열의 모든 원소를 순회하는 반복문
    // `delete`의 호출이 `Media::count`을 수정하기 떄문에 `count`로 초기값을 복사해야 함
    for (int i = 0, count = Media::count; i < count; i += 1) {
        // 동적할당된 객체를 해지함
        // 소멸자 호출 순서를 따라가면 `~Media`가 호출되기 때문에 `Media::count -= 1`이 실행됨
        delete media_ptrs[i];
    }
    // 모든 객체가 소멸되며 소멸자를 호출했기 때문에 `Media::count`는 0
    std::cout << "Media::count: " << Media::count << std::endl; // 0
    return 0;
}
