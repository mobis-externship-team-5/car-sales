#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stock.h"


int increase_stock(STOCK **sthead, STOCK **sttail, const char* product_model)
{
    int err_code;
    STOCK *cur = *sthead;

    while (cur)
    {
        if (strcmp(cur->model, product_model) == 0)
        {
            cur->quantity++;
            break;
        }
        cur = cur->next;
    }

    // 재고 목록에 없는 상품인 경우
    if (cur == NULL) {
        err_code = insert_stock(sthead, sttail, product_model);
        if (ERR_STOCK_OK != err_code) {
            return err_code;
        }
    }
    
    return ERR_STOCK_OK;
}

int insert_stock(STOCK **sthead, STOCK **sttail, const char* product_model)
{
    int err_code;
    
    STOCK *new_stock;
    err_code = create_stock(&new_stock);
    if (ERR_STOCK_OK != err_code) {
        return err_code;
    }

    strcpy(new_stock->model, product_model);
    new_stock->quantity = 1;

    link_stock(sthead, sttail, &new_stock);

    return ERR_STOCK_OK;
}


int create_stock(STOCK **stock)
{
    *stock = (STOCK*)malloc(sizeof(STOCK));
    if (*stock == NULL) {
        return ERR_STOCK_CREATE;
    }
    (*stock)->next = NULL;

    return ERR_STOCK_OK;
}


int link_stock(STOCK **sthead, STOCK **sttail, STOCK **stock)
{
    if (*sthead == NULL) {
        *sthead = *sttail = *stock;
    }
    else {
        (*sttail)->next = *stock;
        (*sttail) = *stock;
    }

    return ERR_STOCK_OK;
}


int decrease_stock(STOCK **sthead, STOCK **sttail, const char* product_model)
{    
    STOCK *cur = *sthead;
    while (cur)
    {
        if (strcmp(cur->model, product_model) == 0)
        {
            break;
        }
        cur = cur->next;
    }

    // 모델명에 해당되는 재고 정보가 없는 경우
    if (cur == NULL) {
        printf("%s:%d error code = %d\n",__FILE__, __LINE__, ERR_STOCK_NOT_FOUND);
        return ERR_STOCK_NOT_FOUND;
    }

    // 재고가 하나 남았을 경우 삭제
    if (cur->quantity == 1) {
        delete_stock(sthead, sttail, product_model);
    }
    else {
        cur->quantity--;
    }

    return ERR_STOCK_OK;
}


int delete_stock(STOCK **sthead, STOCK **sttail, const char* product_model)
{
    STOCK *cur, *prev;
    cur = prev = *sthead;

    while (cur)
    {
        if (strcmp(cur->model, product_model) == 0)
        {
            if (cur == *sthead) {
                *sthead = cur->next;
            }
            else if (cur == *sttail) {
                *sttail = prev;
                prev->next = NULL;
            }
            else {
                prev->next = cur->next;
            }
            free(cur);

            break;
        }
        prev = cur;
        cur = cur->next;
    }

    if (cur == NULL) {
        free(cur);
        return ERR_STOCK_NOT_FOUND;
    }

    return ERR_STOCK_OK;
}


int print_stock_list(STOCK *sthead)
{
    STOCK *cur = sthead;
    
    while (cur) {
        printf("%20s  %3d\n", cur->model, cur->quantity);
        cur = cur->next;
    }

    return ERR_STOCK_OK;
}


int print_stock(STOCK *sthead, const char* product_model)
{
    STOCK *cur = sthead;
    
    while (cur) {
        if (strcmp(cur->model, product_model) == 0) {
            printf("find: %20s  %3d\n", cur->model, cur->quantity);
        }
        cur = cur->next;
    }

    return ERR_STOCK_OK;
} 


int load_stock(STOCK **sthead, STOCK **sttail, const char *filename)
{
    FILE *fp;
    STOCK *new_stock;
    int err_code;

    if ((fp = fopen(filename, "r")) == NULL) {
        return ERR_STOCK_FILE;
    }

    while (1)
    {
        err_code = create_stock(&new_stock);
        if (ERR_STOCK_OK != err_code) {
            printf("%s:%d error code = %d\n",__FILE__, __LINE__, err_code);
            return err_code;
        }

        if ((fread(new_stock, sizeof(STOCK), 1, fp))) {
            link_stock(sthead, sttail, &new_stock);
        }
        else {
            free(new_stock);
            break;
        }
    }

    fclose(fp);
    return ERR_STOCK_OK;
}


int save_stock(STOCK *sthead, const char *filename)
{
    FILE *fp;
    STOCK *cur;

    if ((fp = fopen(filename, "w")) == NULL) {
        return ERR_STOCK_FILE;
    }

    cur = sthead;
    while (cur)
    {
        fwrite(cur, sizeof(STOCK), 1, fp);
        cur = cur->next;
    }

    fclose(fp);
    return ERR_STOCK_OK;
}