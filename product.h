/* 자동차 제조류 */
#ifndef PRODUCT_H
#define PRODUCT_H

enum PRODUUCT_STATUS {
    ABLE,
    DISABLE
};

enum OEM {
    HYUNDAI,
    KIA,
    GENESIS
};

/* 연료 */
enum FEUL {
    GASOLINE,
    DIESEL,
    LPG,
    EV, // 전기
    HEV, // 하이브리드
    FCEV // 수소 전기차
};

/* 상품 구조체 */
// auto, vehicle, car, product
typedef struct product_t {
    int id;
    char model[100]; // 모델명
    enum OEM oem; // 제조사
    int price; // 가격
    enum FEUL fuel; // 연료
    double gas_mileage; // 연비
    enum PRODUUCT_STATUS status; // 상품의 판매 상태

    struct product_t *next;
} PRODUCT;

typedef PRODUCT *LP_PRODUCT;

/* 임의로 만들어 놓은 상품들만 있다고 가정 */

// 페이지 별로 상품 리스트 출력
// ABLE 인것만 출력
int print_list(void *head, int page_no);

// 상품 검색
int search(PRODUCT *head, PRODUCT **shead, PRODUCT **stail);

int find_product(int id);

#endif