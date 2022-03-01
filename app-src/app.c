#include <stdio.h>

#include "file-name.h"
#include "user.h"
#include "product.h"
#include "product-detail.h"
#include "stock.h"


int main(void)
{
    int err_code;

    USER cur_user;

    USER *uhead, *utail;    /* 사용자 연결 리스트 */
    PRODUCT *phead, *ptail; /* 상품 연결 리스트 */
    STOCK *shead, *stail;   /* 재고 연결 리스트 */
    
    LPHASH pdhash;          /* 상품 상세설명 해시 */
    PRODUCT_DETAIL* cur_product_detail;
    
    uhead = utail = NULL;
    phead = ptail = NULL;
    shead = stail = NULL;
    
    err_code = hashCreate(&pdhash);
    if (ERR_HASH_OK != err_code) {
        return 0;
    }
    
    printf("Hello, world!!!\n");

    load_product(&phead, &ptail, PRODUCT_FILE);
    printf("after load product\n");
    print_product_list(phead, 0);

    for(int i=0; i<3; i++) {
        // insert_product(&phead, &ptail);
        insert_product_detail(i, &pdhash);
        print_product_detail_list(i, pdhash);
    }

    for (int i=0; i<3; i++)
    {
        find_product_detail(pdhash, 2-i, &cur_product_detail);
        print_product_detail(cur_product_detail);
    }
    


    save_product(phead, PRODUCT_FILE);

    return 0;
}