#ifndef ORDER_H
#define ORDER_H

#define ERR_ORDER_OK                  0
#define ERR_ORDER_CREATE          -3000
#define ERR_ORDER_FILE            -3001
#define ERR_ORDER_NOT_FOUND       -3002

#include "user.h"
#include "ui-printlist.h"

typedef struct order_t {
    int order_num;
    char date[30]; // 구매 날짜
    char user_id[20]; // 고객 아이디
    char user_name[20]; // 고객 이름
    int product_id;
    int price;

    struct order_t *next;
} ORDER;


int purchase(ORDER **ohead, ORDER **otail, const char *user_id, const char *user_name, int price, int product_id);
int create_order(ORDER **prder);
int input_order_info(ORDER **order, const char *user_id, const char *user_name, int price, int product_id);
int set_order_num(ORDER **order, ORDER *otail);
int link_order(ORDER **ohead, ORDER **otail, ORDER **order);

int print_order(ORDER *order);
int print_all_order_list(ORDER *ohead);
int print_customer_order_list(ORDER *ohead, const char* user_id);
int print_sales(ORDER *ohead);

int load_order(ORDER **ohead, ORDER **otail, const char* filename);
int save_order(ORDER *ohead, const char *filename);

int print_list_order(ORDER *ohead, int page_no, char element_column[][6][20], int arr[6], int user_role, USER *user);


#endif