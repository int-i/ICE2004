// 기능 단위로 파일을 나누기 때문에 미디어에 관한 모든 클래스를 `media.h`에 정의함

// 중복 삽입 방지를 위한 Define Guard
#ifndef ICE2004_WEEK07_HW01_MEDIA_H
#define ICE2004_WEEK07_HW01_MEDIA_H

// 사용할 헤더 정의
#include <iostream>
#include <string>

/** 미디어에 관한 클래스 */
class Media {
private:
    /** 미디어 제목 */
    std::string title;

    /** 미디어 길이 */
    int length;

public:
    /** 총 생성된 미디어 개수 */
    static int count;

    /**
     * 주어진 제목과 길이로 미디어 객체를 생성합니다.
     * @param title 미디어 제목
     * @param length 미디어 길이
     */
    Media(const std::string& title, int length);

    /**
     * 미디어 객체를 삭제합니다.
     */
    ~Media();

    /**
     * 미디어 길이를 반환합니다.
     * @return 미디어 길이
     */
    int get_length() const;

    /**
     * 미디어에 대한 상태를 반환합니다.
     * @return 미디어 상태
     */
    virtual std::string get_status() const;

    /**
     * 미디어 제목을 반환합니다.
     * @return 미디어 제목
     */
    const std::string& get_title() const;

    /**
     * 표준출력으로 미디어의 정보를 출력합니다.
     */
    virtual void play() const;

    /**
     * 미디어 길이를 설정합니다.
     * @param length 미디어 길이
     */
    void set_length(int length);

    /**
     * 미디어 제목을 설정합니다.
     * @param title 미디어 제목
     */
    void set_title(const std::string& title);

    /**
     * 두 개의 미디어를 합쳐서 새로운 미디어를 생성합니다.
     * 이 함수로부터 생성된 미디어는 수동 메모리 할당해지가 필요합니다.
     * @param media_ptr 기존 미디어에 합칠 새로운 미디어
     * @return 새로 합쳐진 미디어
     */
    [[nodiscard]] Media* operator+(Media* media_ptr);

    /**
     * 출력스트림으로 미디어의 정보를 출력하게 합니다.
     * @param out 출력스트림
     * @param media_ptr 출력할 미디어
     * @return 출력스트림
     */
    friend std::ostream& operator<<(std::ostream& out, Media* media_ptr);
};

/**
 * DVD에 관한 클래스
 * @extends Media
 */
class DVD : public Media {
private:
    /** DVD 라이선스 */
    std::string license;

public:
    /**
     * 주어진 제목과 길이, 라이선스로 DVD 객체를 생성합니다.
     * @param title DVD 제목
     * @param length DVD 길이
     * @param license DVD 라이선스
     */
    DVD(const std::string& title, int length, const std::string& license);

    /**
     * DVD 라이선스를 반환합니다.
     * @return DVD 라이선스
     */
    const std::string& get_license() const;

    /**
     * DVD에 대한 상태를 반환합니다.
     * @return DVD 상태
     */
    virtual std::string get_status() const override;

    /**
     * 표준출력으로 DVD의 정보를 출력합니다.
     */
    virtual void play() const override;

    /**
     * DVD 라이선스를 설정합니다.
     * @param license DVD 라이선스
     */
    void set_license(const std::string& license);
};

/**
 * 합법 DVD에 관한 클래스
 * @extends DVD
 */
class LegalDVD : public DVD {
private:
    /** 합법 DVD 저작권 */
    std::string copyright;

public:
    /**
     * 주어진 제목과 길이, 라이선스, 저작권 정보로 합법 DVD 객체를 생성합니다.
     * @param title 합법 DVD 제목
     * @param length 합법 DVD 길이
     * @param license 합법 DVD 라이선스
     * @param copyright 합법 DVD 저작권
     */
    LegalDVD(const std::string& title, int length, const std::string& license, const std::string& copyright);

    /**
     * 합법 DVD 저작권을 반환합니다.
     * @return 합법 DVD 저작권
     */
    const std::string& get_copyright() const;

    /**
     * 합법 DVD에 대한 상태를 반환합니다.
     * @return 합법 DVD 상태
     */
    virtual std::string get_status() const override;

    /**
     * 표준출력으로 합법 DVD의 정보를 출력합니다.
     */
    virtual void play() const override;

    /**
     * 합법 DVD 저작권을 설정합니다.
     * @param copyright 합법 DVD 저작권
     */
    void set_copyright(const std::string& copyright);
};

/**
 * VTR에 관한 클래스
 * @extends Media
 */
class VTR : public Media {
private:
    /** VTR 포맷 */
    std::string format;

public:
    /**
     * 주어진 제목과 길이, 포맷 정보로 VTR 객체를 생성합니다.
     * @param title VTR 제목
     * @param length VTR 길이
     * @param license VTR 포맷
     */
    VTR(const std::string& title, int length, const std::string& format);

    /**
     * VTR 포맷을 반환합니다.
     * @return VTR 포맷
     */
    const std::string& get_format() const;

    /**
     * VTR에 대한 상태를 반환합니다.
     * @return VTR 상태
     */
    virtual std::string get_status() const override;

    /**
     * 표준출력으로 VTR의 정보를 출력합니다.
     */
    virtual void play() const override;

    /**
     * VTR 포맷을 설정합니다.
     * @param format VTR 포맷
     */
    void set_format(const std::string& format);
};

#endif // ICE2004_WEEK07_HW01_MEDIA_H
