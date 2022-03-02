#ifndef ORDER_H
#define ORDER_H

#include "user.h"

#define ERR_ORDER_OK                  0
#define ERR_ORDER_CREATE          -3000
#define ERR_ORDER_FILE            -3001
#define ERR_ORDER_NOT_FOUND       -3002

typedef struct order_t {
    int order_num;
    char date[30]; // 구매 날짜
    char user_id[20]; // 고객 아이디
    char user_name[20]; // 고객 이름
    int product_id;

    struct order_t *next;
} ORDER;

// 상품 구매
// 상품의 상태를 변경시키고
// ORDER 구조체 동적 할당 (추가)
// 이 함수에서 동적 할당받아 생성한 PRODUCT 를 재고 관리 함수로 넘기기
int purchase(ORDER **ohead, ORDER **otail, const char *user_id, const char *user_name, int product_id);
int create_order(ORDER **prder);
int input_order_info(ORDER **order, const char *user_id, const char *user_name, int product_id) ;
int set_order_num(ORDER **order, ORDER *otail);
int link_order(ORDER **ohead, ORDER **otail, ORDER **order);

int print_order(ORDER *order);
int print_all_order_list(ORDER *ohead);
int print_customer_order_list(ORDER *ohead, const char* user_id);
int print_sales(ORDER *ohead);

int load_order(ORDER **ohead, ORDER **otail, const char* filename);
int save_order(ORDER *ohead, const char *filename);

#endif