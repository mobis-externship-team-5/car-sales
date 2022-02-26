#ifndef PRODUCT_DETAIL_H
#define PRODUCT_DETAIL_H

#include "product.h"

enum SIZE {
    COMPACT, // 소형
    MEDIUM, // 중형
    FULL_SIZE, // 대형
    TRUCK // 트럭
};

typedef struct product_detail_t {
    int product_id;
    int color;
    enum SIZE size;
    int cc;
    int description;
} PRODUCT_DETAIL;

// 상품 리스트
// 상품 번호 | 내용 | 내용
// DETAIL 상품번호(product_id)
// 상품 번호에 해당되는 상품 찾고
// 상품 번호에 해당되는 상세 찾고
// 출력
int print_detail(PRODUCT *shead, PRODUCT_DETAIL *dhead, int product_id);


#endif