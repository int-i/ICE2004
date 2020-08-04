// 사용할 헤더 정의
#include "media.h"
#include <iostream>
#include <string>
#include <utility>

// 정적 멤버변수 초기화
int Media::count = 0;

// 생성자 초기화 리스트를 이용
// 불필요한 멤버 변수 할당이 없어서 성능 향상에 유리함
Media::Media(const std::string& title, int length)
: title(title), length(length) {
    // 생성자가 실행될 때마다 `count`를 1씩 증가시킴
    count += 1;
}

Media::~Media() {
    // 생성자가 실행될 때마다 `count`를 1씩 감소시킴
    count -= 1;
}

int Media::get_length() const {
    return length;
}

// `get_status`는 가상 메소드이기 때문에 동적할당시 vtable을 참조해 자식클래스의 메소드를 호출함
std::string Media::get_status() const {
    // 리터럴을 반환하기 때문에 복사로 반환
    return "A media is playing.";
}

const std::string& Media::get_title() const {
    // 변수를 반환하기 때문에 상수형 참조로 반환할 수 있음
    return title;
}

// `play`는 가상 메소드이기 때문에 동적할당시 vtable을 참조해 자식클래스의 메소드를 호출함
void Media::play() const {
    std::cout << "Play a media." << std::endl;
}

void Media::set_length(int length) {
    // `this`를 이용해 인자와 이름이 같은 멤버변수에 접근할 수 있음
    this->length = length;
}

void Media::set_title(const std::string& title) {
    this->title = title;
}

// `+` 연산자 오버로딩
Media* Media::operator+(Media* media_ptr) {
    // 동적할당 되었기 때문에 반환값을 변수에 저장하지 않고 지나가면 메모리 누수가 발생함
    // 함수를 `nodiscard`로 정의해 반환값이 사용되지 않으면 경고함
    return new Media(title, length + media_ptr->length);
}

// 클래스 내부에서 `friend`로 정의했기 때문에 `std::ostream`을 오버로딩할 수 있음
std::ostream& operator<<(std::ostream& out, Media* media_ptr) {
    out << media_ptr->get_status();
    // 인자로 받은 `std::ostream`을 참조로 반환
    return out;
}

// 생성자 초기화 리스트를 이용해 부모 클래스를 초기화할 수 있음
DVD::DVD(const std::string& title, int length, const std::string& license)
: Media(title, length), license(license) {}

const std::string& DVD::get_license() const {
    return license;
}

std::string DVD::get_status() const {
    return "A DVD is playing.";
}

void DVD::play() const {
    std::cout << "Play a DVD." << std::endl;
}

void DVD::set_license(const std::string& license) {
    this->license = license;
}

LegalDVD::LegalDVD(const std::string& title, int length, const std::string& license, const std::string& copyright)
: DVD(title, length, license), copyright(copyright) {}

const std::string& LegalDVD::get_copyright() const {
    return copyright;
}

std::string LegalDVD::get_status() const {
    return "A legal DVD is playing.";
}

void LegalDVD::play() const {
    std::cout << "Play a legal DVD." << std::endl;
}

void LegalDVD::set_copyright(const std::string& copyright) {
    this->copyright = copyright;
}

VTR::VTR(const std::string& title, int length, const std::string& format)
: Media(title, length), format(format) {}

const std::string& VTR::get_format() const {
    return format;
}

std::string VTR::get_status() const {
    return "A VTR is playing.";
}

void VTR::play() const {
    std::cout << "Play a VTR." << std::endl;
}

void VTR::set_format(const std::string& format) {
    this->format = format;
}
