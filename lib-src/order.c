#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "order.h"

int purchase(ORDER **ohead, ORDER **otail, const char *user_id, const char *user_name, int product_id)
{
    int err_code;
    ORDER *new_order;
    
    err_code = create_order(&new_order);
    if (ERR_ORDER_OK != err_code) {
        printf("%s:%d error code = %d\n",__FILE__, __LINE__, err_code);
        return err_code;
    }

    set_order_num(&new_order, *otail);
    input_order_info(&new_order, user_id, user_name, product_id);

    link_order(ohead, otail, &new_order);

    return ERR_ORDER_OK;
}


int create_order(ORDER **order)
{
    *order = (ORDER *)malloc(sizeof(ORDER));
    if (*order == NULL) {
        return ERR_ORDER_CREATE;
    }
    return ERR_ORDER_OK;
}

int set_order_num(ORDER **order, ORDER *otail)
{
    if (otail == NULL) {
        (*order)->order_num = 0;
    }
    else {
        (*order)->order_num = otail->order_num + 1;
    }

    return ERR_ORDER_OK;
}


int input_order_info(ORDER **order, const char *user_id, const char *user_name, int product_id) 
{
    char date[30];
    time_t now;
    time(&now);
    struct tm *t = (struct tm*) localtime(&now);
    

    strftime(date, sizeof(date)-1, "%Y-%m-%d %H:%M:%S", t);
    strcpy((*order)->date, date);

    strcpy((*order)->user_id, user_id);
    strcpy((*order)->user_name, user_name);
    
    (*order)->product_id = product_id;

    return ERR_ORDER_OK;
}


int link_order(ORDER **ohead, ORDER **otail, ORDER **order)
{
    if (*ohead == NULL) {
        *ohead = *otail = *order;
    }
    else {
        (*otail)->next = *order;
        *otail = *order;
    }

    return ERR_ORDER_OK;
}

// 주문 정보 입력됐는지 출력
int print_order(ORDER *order)
{
    printf("%3d %30s %10s(%s) %3d\n", 
            order->order_num, order->date, order->user_id, 
            order->user_name, order->product_id);

    return ERR_ORDER_OK;
}

/* [관리자] 출고 목록 (구매내역) */
int print_all_order_list(ORDER *ohead)
{
    ORDER *cur = ohead;

    while (cur)
    {
         printf("%3d %30s %10s(%s) %3d\n", 
                cur->order_num, cur->date, cur->user_id, 
                cur->user_name, cur->product_id);
        cur = cur->next;
    }

    return ERR_ORDER_OK;
}

/* [사용자] 구매 이력 */
int print_customer_order_list(ORDER *ohead, const char* user_id)
{
    ORDER *cur = ohead;

    while (cur)
    {
        if (strcmp(cur->user_id, user_id) == 0) {
            printf("%3d %30s %10s(%s) %3d\n", 
                cur->order_num, cur->date, cur->user_id, 
                cur->user_name, cur->product_id);
        }
        cur = cur->next;
    }

    return ERR_ORDER_OK;
}


int load_order(ORDER **ohead, ORDER **otail, const char *filename)
{
    FILE *fp;
    ORDER *new_order;

    if ((fp = fopen(filename, "r")) == NULL) {
        return ERR_ORDER_OK;
    }

    while (1)
    {
        create_order(&new_order);

        if ((fread(new_order, sizeof(ORDER), 1, fp))) {
            link_order(ohead, otail, &new_order);
        }
        else {
            free(new_order);
            break;
        }
    }

    fclose(fp);
    return ERR_ORDER_OK;
}


int save_order(ORDER *ohead, const char *filename)
{
    FILE *fp;
    ORDER *cur;
    
    if ((fp = fopen(filename, "w")) == NULL) {
        return ERR_ORDER_OK;
    }

    cur = ohead;
    while (cur)
    {
        fwrite(cur, sizeof(ORDER), 1, fp);
        cur = cur->next;
    }

    fclose(fp);
    return ERR_ORDER_OK;
}