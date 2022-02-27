#ifndef STOCK_H
#define STCOK_H

#include "product.h"

// 날짜 입력 형식: YYYY-MM-DD

typedef struct stock_t {
    char model[20]; 
    int quantity;
} STOCK;

// 입고는 임의로 데이터를 삽입하고, 관리자가 추가한다고 가정하자
// 그렇다면 출고 날짜와 고객 인수 날짜는 어떻게 지정하나?
//   - 사용자가 구매를 한 날짜에서 오차 범위 안

// model, quantity
int print_stock();

// insert_product
int increase_stock();

int decrease_stock();

#endif


// 차량 재고 관리 함수는 여기 있어야하나?