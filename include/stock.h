#ifndef STOCK_H
#define STOCK_H

#define ERR_STOCK_OK                  0
#define ERR_STOCK_CREATE          -4000
#define ERR_STOCK_FILE            -4001
#define ERR_STOCK_NOT_FOUND       -4002


typedef struct stock_t {
    char model[20]; 
    int quantity;

    struct stock_t *next;
} STOCK;

int increase_stock(STOCK **sthead, STOCK **sttail, const char* product_model);
int insert_stock(STOCK **sthead, STOCK **sttail, const char* product_model);
int create_stock(STOCK **stock);
int link_stock(STOCK **sthead, STOCK **sttail, STOCK **stock);
int decrease_stock(STOCK **sthead, STOCK **sttail, const char* product_model); // main: cur_product
int delete_stock(STOCK **sthead, STOCK **sttail, const char* product_model);
int print_stock_list(STOCK *sthead);
int print_stock(STOCK *sthead, const char* product_model);
int load_stock(STOCK **sthead, STOCK **sttail, const char *filename);
int save_stock(STOCK *sthead, const char *filename);

#endif