/* 자동차 제조류 */
#ifndef PRODUCT_H
#define PRODUCT_H

#include "product-detail.h"
#include "stock.h"

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
    int product_id;
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

// [관리자] 차량 입고 (프로그램 시작 시 또는 관리자 선택 시 차량 상품 삽입)
// 재고가 되기 전 목록들
int insert_product(PRODUCT **phead, PRODUCT **ptail, PRODUCT_DETAIL **dhead, PRODUCT_DETAIL **dtail);

// [관리자] 재고 현황 확인 (차량 목록 출력)
// 상품 목록
// ABLE 값이 설정된 상품만 출력
// ABLE, DISABLE 모두 가능
int print_all_product(PRODUCT *phead, int page_no);

// 페이지 별로 상품 리스트 출력
// ABLE 인것만 출력
int print_product_list(PRODUCT *phead, int page_no);

// 상품 검색
int product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);


int find_product(PRODUCT *tmp_product, int product_id);


#endif