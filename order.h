#ifndef ORDER_H
#define ORDER_H

#include "product.h"

typedef struct order_t {
    int order_num;
    char date[20]; // 구매 날짜
    int user_id; // 고객 아이디 FK
    int product_id; // 상품 아이디 FK

    struct order_t *next;
} ORDER;


// 상품 구매
// 상품의 상태를 변경시키고
// ORDER 구조체 동적 할당 (추가)
// 이 함수에서 동적 할당받아 생성한 PRODUCT 를 재고 관리 함수로 넘기기
int purchase(ORDER **ohead, ORDER **otail, PRODUCT *phead, int user_id, int product_id);

// 차랑 출고 (사용자가 '주문'을 하면 차량 상품 목록에서 DISABLE)
// 전체 주문 목록 출력, 팔았다 = 출고 == 주문
// 관리자 입장에서는 '모든' 구매 내역 확인, 사용자 입장에서는 '자신의' 구매 내역만 확인
int print_order_list(ORDER *ohead, PRODUCT *phead);

// 메출 출력 (판매한 총 금액) // STATUS == DISABLE
// 어떻게 하면 보기 좋게 출력할지? total_price 말고 더 보여줄게 뭐가 있을지?
// 검색 결과에 따른 리스트들의 총합 (월별 매출 리스트)
// 명세서처럼 양식이 달라져도 괜찮을 듯 (지난 달 대비 증감)
int print_toatl_order_price(ORDER *ohead, PRODUCT *phead);

#endif