#ifndef ORDER_H
#define ORDER_H

#include "user.h"
#include "product.h"


typedef struct order_t {
    int id;
    int order_num;
    int date; // 구매 날짜
    int user_id; // 고객 아이디 FK
    int product_id; // 상품 아이디 FK
    // USER user; // 고객
    // PRODUCT product; // 구매한 상품
    int total_price;
} ORDER;


// 상품 구매
// 상품의 상태를 변경시키고
// ORDER 구조체 동적 할당 (추가)
int purchase(int user_id, int product_id);

// + 추가적인 구매 페이지를 둘 건지?

#endif

// load_file(); 파일에 저장된 구조체 내용들을 모두 불러온다
// 프로그램이 종료 되면 save_file();


// 주문 데이터는 관리자의 '구매내역조회'에서 사용될 예정
// 매출 관리는 어디에서..?

// Question !!
// (1) 구조체 안에 외래키를 포함시킬지? (2) 참조하는 구조체 자체를 포함시킬지?
// (1) 구조체 자체 크기는 감소하나, 파일 입출력이 까다로울 것으로 예상
// (2) 구조체의 크기가 커지지만, 하나의 파일 출력으로 해결될 것으로 예상