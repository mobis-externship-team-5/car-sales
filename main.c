#include <stdio.h>

#include "user.h"
#include "product.h"
#include "product-detail.h"

int main(void)
{
    USER current_user;
    PRODUCT *HEAD, *TAIL; // 파일로부터 불러온 모든 상품 리스트
    PRODUCT *SHEAD, *STAIL; // 모든 상품 리스트에서 검색한 상품들만 저장된 리스트
    PRODUCT_DETAIL *DETAIL_HEAD;
    USER *USER_HEAD;

    load_func();

    //

    return 0;
}