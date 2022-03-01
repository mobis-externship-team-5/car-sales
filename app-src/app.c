#include <stdio.h>

#include "user.h"
#include "product.h"
#include "product-detail.h"
#include "stock.h"


int main(void)
{
    int err_code;

    USER current_user;

    USER *uhead, *utail;
    PRODUCT *phead, *ptail;
    STOCK *shead, *stail;
    
    uhead = utail = NULL;
    phead = ptail = NULL;
    shead = stail = NULL;
    
    printf("Hello, world!!!\n");

    load_product(&phead, &ptail, "../data-files/product.dat");
    printf("after load product\n");
    print_product_list(phead, 0);

    for(int i=0; i<3; i++) {
        insert_product(&phead, &ptail);
        // insert_product_detail(ptail->product_id, &pdhash);
    }
    
    save_product(phead, "../data-files/product.dat");

    return 0;
}