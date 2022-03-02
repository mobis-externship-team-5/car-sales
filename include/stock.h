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
int print_list_stock(STOCK *sthead, int page_no,char element_column[][6][20],int arr[6]);
int stock_search(STOCK *sthead, STOCK **shead, STOCK **stail,int *user_role, int opt2);
int stock_search_ID(STOCK *sthead,STOCK **shead,STOCK **stail,int stock_id);
int stock_copy(STOCK *origin,STOCK *copy);

#endif
