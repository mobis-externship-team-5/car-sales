#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"

extern int errno;

int create_product(PRODUCT **product)
{
    *product = (PRODUCT *)malloc(sizeof(PRODUCT));
    if (*product == NULL) {
        return ERR_PRODUCT_CREATE;
    }
    (*product)->next = NULL;

    return ERR_PRODUCT_OK;
}

int link_product(PRODUCT **phead, PRODUCT **ptail, PRODUCT **product)
{
    if (*phead == NULL) {
        *phead = *ptail = *product;
    }
    else {
        (*ptail)->next = *product;
        *ptail = *product;
    }

    return ERR_PRODUCT_OK;
}

/* 상품 리스트에 삽입하는 함수 */
int insert_product(PRODUCT **phead, PRODUCT **ptail)
{
    int err_code;

    PRODUCT *new_product;
    err_code = create_product(&new_product);
    if (ERR_PRODUCT_OK != err_code) {
        return err_code;
    }

    err_code = input_product_info(&new_product, *ptail);
    if (ERR_PRODUCT_OK != err_code) {
        return err_code;
    }

    // if (*phead == NULL) {
    //     *phead = *ptail = new_product;
    // }
    // else {
    //     (*ptail)->next = new_product;
    //     *ptail = new_product;
    // }

    link_product(phead, ptail, &new_product);

    print_product_list(*phead, 0);
    
    return ERR_PRODUCT_OK;
}

/* 상품 정보를 입력받는 함수 */
int input_product_info(PRODUCT **product, PRODUCT *ptail)
{
    int i;
    int err_code;

    err_code = increase_product_id(product, ptail);
    if (ERR_PRODUCT_OK != err_code) {
        return err_code;
    }

    printf("INPUT VEHICLE INFORMATION\n\n");
    
    // 모델명 입력
    printf("MODEL\n>> ");
    fgets((*product)->model, sizeof((*product)->model)-1, stdin);
    (*product)->model[strlen((*product)->model) - 1] = '\0';

    // 제조사 입력
    printf("OEM - ");
    for(i=0; i<sizeof(oem_str)/sizeof(char*); i++) {
        printf("%d(%s)  ", i, oem_str[i]);
    }
    printf("\n>> ");
    scanf("%d", &(*product)->oem);

    // 가격 입력
    printf("PRICE\n>> ");
    scanf("%d", &(*product)->price);

    // 연료 입력
    printf("FUEL - ");
    for(i=0; i<sizeof(fuel_str)/sizeof(char*); i++) {
        printf("%d(%s)  ", i, fuel_str[i]);
    }
    printf("\n>> ");
    scanf("%d", &(*product)->fuel);

    // 연비 입력
    printf("GAS MILEAGE\n>> ");
    scanf("%lf", &(*product)->gas_mileage); getchar();
    
    return ERR_PRODUCT_OK;
}

/* 상품 아이디를 부여하는 함수 */
int increase_product_id(PRODUCT **product, PRODUCT *ptail)
{
    // 상품이 처음 입고된 경우
    if(ptail == NULL) {
        (*product)->product_id = 0;
    }
    else {
        // 아이디의 범위가 정수 크기를 넘어간 경우
        if (ptail->product_id == __INT_MAX__) {
            return ERR_PRODUCT_ID;
        }
        (*product)->product_id = ptail->product_id + 1;
    }

    return ERR_PRODUCT_OK;
}

/* 상품 리스트를 출력하는 함수 (디버깅) */
int print_product_list(PRODUCT *phead, int page_no)
{
    PRODUCT *current = phead;

    while (current)
    {
        printf("%5d %20s %15s %10d %10s %.2lf %8s\n",
                current->product_id, current->model, oem_str[current->oem], 
                current->price, fuel_str[current->fuel], current->gas_mileage, product_status_str[current->status]);
        
        current = current->next;
    }

    return ERR_PRODUCT_OK;
}

/* 파일로부터 상품 리스트를 불러오는 함수 */
int load_product(PRODUCT **phead, PRODUCT **ptail, const char *filename)
{
    FILE *fp;
    PRODUCT *new_product;

    if ((fp = fopen(filename, "r")) == NULL) {
        return ERR_PRODUCT_FILE;
    }

    while (1)
    {
        create_product(&new_product);

        if ((fread(new_product, sizeof(PRODUCT), 1, fp))) {
            link_product(phead, ptail, &new_product);
        }
        else {
            free(new_product);
            break;
        }
    }

    fclose(fp);
    return ERR_PRODUCT_OK;
}

/* 상품 리스트를 파일에 저장하는 함수 */
int save_product(PRODUCT *phead, const char *filename)
{
    FILE *fp;
    PRODUCT *current;
    
    int errnum;
    if ((fp = fopen(filename, "w")) == NULL) {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
        return ERR_PRODUCT_FILE;
    }

    current = phead;
    while (current)
    {
        fwrite(current, sizeof(PRODUCT), 1, fp);
        current = current->next;
    }

    fclose(fp);
    return ERR_PRODUCT_OK;
}