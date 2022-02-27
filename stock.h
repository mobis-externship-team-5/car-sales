#ifndef STOCK_H
#define STCOK_H

#include "product.h"

// 날짜 입력 형식: YYYY-MM-DD

typedef struct stock_t {
    char model[20]; 
    int quantity;

    struct stock_t *next;
} STOCK;

// 입고는 임의로 데이터를 삽입하고, 관리자가 추가한다고 가정하자
// 그렇다면 출고 날짜와 고객 인수 날짜는 어떻게 지정하나?
//   - 사용자가 구매를 한 날짜에서 오차 범위 안

// model, quantity
int print_stock(STOCK *sthead);

int increase_stock(STOCK **sthead, PRODUCT product);

int decrease_stock(STOCK **sthead, PRODUCT product);

// 재고 찾는 함수가 중복되면 search 따로 빼는 것을 고려 해봅시다!

#endif


// 차량 재고 관리 함수는 여기 있어야하나?