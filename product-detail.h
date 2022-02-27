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
    char detail_name[50]; // 상세한 제품명
    char color [20];
    enum SIZE size;
    int cc;
    int description;

    struct product_detail_t *next;
} PRODUCT_DETAIL;

// 상품 상세 정보 출력 (상품 + 상품 디테일)
int print_detail(PRODUCT *phead, PRODUCT_DETAIL *dhead, int product_id);

#endif