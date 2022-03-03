#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui-printlist.h"

#include "product.h"

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

    link_product(phead, ptail, &new_product);
    
    return ERR_PRODUCT_OK;
}

/* 상품 정보를 입력받는 함수 */
int input_product_info(PRODUCT **product, PRODUCT *ptail)
{
    int i;
    int err_code;

    err_code = set_product_id(product, ptail);
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
int set_product_id(PRODUCT **product, PRODUCT *ptail)
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
int print_product_list_in_detail(PRODUCT *phead)
{
    PRODUCT *current = phead;

        printf(" MODEL NAME : %s\n OEM : %s\n GAS_MILLEGE : %2.2f\n FUEL : %s\n PRICE : %d\n\n",
                current->model, oem_str[current->oem],
                current->gas_mileage, fuel_str[current->fuel],current->price);


    return ERR_PRODUCT_OK;
}

int find_product(PRODUCT* phead, PRODUCT **product, int product_id)
{
    PRODUCT *cur = phead;
    while (cur)
    {
        if (cur->product_id == product_id) {
            *product = cur;
            break;
        }
        cur = cur->next;
    }

    if (cur == NULL) {
        printf("PRODUCT(ID:%d) NOT FOUND.. REPRESS THE OPTION!\n", product_id);
        return ERR_PRODUCT_NOTFOUND;
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
    
    if ((fp = fopen(filename, "w")) == NULL) {
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

int print_list_product(PRODUCT *phead, int page_no, char element_column[][6][20], int arr[6], int ign_status)
{
    PRODUCT *current = phead;
    int chart_length = 72;
    int arr_size = 6;
    //      ui_printlist_printroof('-','*');

    ui_printlist_printline('=');
    ui_printlist_printline('-');
    set_column_size(arr, chart_length, arr_size, element_column, 1, 0);
    ui_printlist_printline('-');

    // 정수는 루트 10으로 자르고
    for (int i = 0; i < page_no * 5; i++)
    {
        if (current == NULL)
            break;
        if (current->status == ign_status) 
            i--;
        current = current->next;
    }
    int count = 0;
    while (current)
    {
        if (count == 5)
            break;
        if (current->status == ign_status) {
            current = current->next;
            continue; // 판매된 상품 출력 X
        }
            
        printf("|");
        printspace_int(current->product_id, arr[0]);
        printspace_string(current->model, arr[1]);
        printspace_string(oem_str[current->oem], arr[2]);
        printspace_double(current->gas_mileage, arr[3]);
        printspace_string(fuel_str[current->fuel], arr[4]);
        printspace_int(current->price, arr[5]);

        //printspace_string(product_status_str[current->status],arr[0]);
        printf("\n");

        current = current->next;
        count++;
    }
    ui_printlist_printline('-');
    printf("\n                                   %d/10                           \n", page_no + 1);
    ui_printlist_printline('=');

    return ERR_PRODUCT_OK;
}

int product_search_ID(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail, int product_id)
{
    PRODUCT *search, *smake;
    search = phead;
    *shead = NULL;

    while (search != NULL)
    {
        if (product_id == search->product_id)
        {
            smake = (PRODUCT *)malloc(sizeof(PRODUCT));
            product_copy(search, smake);
            if ((*shead) == NULL)
            {
                *shead = *stail = smake;
                break;
            }
        }
        search = search->next;
    }

    return ERR_PRODUCT_OK;
}

int product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail,int *user_role, int opt2)
{
	int role = *user_role;
    PRODUCT *search, *smake;
    int em, min, max, fu;
    int opt = opt2;
    double mile;
    char m[100];
    
    search = phead;
    *shead = NULL;
    if(opt==1){ // 모델명으로 검색
        printf("검색할 모델명 입력 : ");
        fgets(m,99,stdin);
        m[strlen(m)-1]='\0';
        while(search!=NULL){
            if(strcmp(m,search->model)==0) {
                if(role==1 && search->status==1){ //회원으로 접속이고 검색한 제품이 disable이면 제외
                    search = search->next;
                    continue;
                }
                smake = (PRODUCT*)malloc(sizeof(PRODUCT));
                product_copy(search,smake);
                if((*shead)==NULL){
                    *shead = *stail = smake;
                }
                else{
                    (*stail)->next = smake;
                    *stail = smake;
                }
            }
            search = search->next;
        }        
    } 

    else if(opt==2){ //제조사(브랜드)로 검색
        printf("검색할 제조사(브랜드)를 선택 >> 0.HYUNDAI, 1.KIA, 2.GENESIS\n");
        printf("번호 선택 : ");
        scanf("%d",&em);
        getchar();

        while(search!=NULL){
            if(em==search->oem) {
		        if(role==1 && search->status==1){ //회원으로 접속이고 검색한 제품이 disable이면 제외
                    search = search->next;
                    continue;
                }
                smake = (PRODUCT*)malloc(sizeof(PRODUCT));
                product_copy(search,smake);
                if((*shead)==NULL){
                    *shead = *stail = smake;
                }
                else{
                    (*stail)->next = smake;
                    *stail = smake;
                }
            }
	
	search = search->next;          
        }
    }

    else if(opt==3){ //가격으로 검색
        printf("검색할 가격대 입력(단위 : 만원) >> ex) 1000 2000\n");
        printf("최소 가격 : ");
        scanf("%d",&min);
        getchar();
        printf("최대 가격 : ");
        scanf("%d",&max);
        getchar();
        
        while(search!=NULL){
            if(search->price>=min && search->price<=max) {
                if(role==1 && search->status==1){ //회원으로 접속이고 검색한 제품이 disable이면 제외
                    search = search->next;
                    continue;
                }
                smake = (PRODUCT*)malloc(sizeof(PRODUCT));
                product_copy(search,smake);
                if((*shead)==NULL){
                    *shead = *stail = smake;
                }
                else{
                    (*stail)->next = smake;
                    *stail = smake;
                }
            }
            search = search->next;
        }                
    }

    else if(opt==4){ //엔진 유형으로 검색
        printf("검색할 엔진 선택 >> 0.GASOLINE, 1.DIESEL, 2.LPG, 3.EV, 4.HEV\n");
        printf("번호 선택 : ");
        scanf("%d",&fu);
        getchar();

        while(search!=NULL){
            if(fu==search->fuel) {
                if(role!=2 && search->status==1){ //회원으로 접속이고 검색한 제품이 disable이면 제외
                    search = search->next;
                    continue;
                }
                smake = (PRODUCT*)malloc(sizeof(PRODUCT));
                product_copy(search,smake);
                if((*shead)==NULL){
                    *shead = *stail = smake;
                }
                else{
                    (*stail)->next = smake;
                    *stail = smake;
                }
            }
            search = search->next;
        }
    }

    else if(opt==5){ //연비 유형으로 검색
        printf("검색할 최소 연비 입력 : ");
        scanf("%lf",&mile);
getchar();
        
        while(search!=NULL){
            if(mile<=search->gas_mileage) {
                if(role==1 && search->status==1){ //회원으로 접속이고 검색한 제품이 disable이면 제외
                    search = search->next;
                    continue;
                }
                smake = (PRODUCT*)malloc(sizeof(PRODUCT));
                product_copy(search,smake);
                if((*shead)==NULL){
                    *shead = *stail = smake;
                }
                else{
                    (*stail)->next = smake;
                    *stail = smake;
                }
            }
            search = search->next;
        } 
    }
    else {
        printf("잘못된 입력입니다. \n");
    }

    return 0;
}

int product_copy(PRODUCT *origin,PRODUCT *copy)
{
    copy->product_id = origin->product_id;
    strcpy(copy->model,origin->model);
    copy->oem = origin->oem;
    copy->price = origin->price;
    copy->fuel = origin->fuel;
    copy->gas_mileage = origin->gas_mileage;
    copy->status = origin->status;
    return 0;
}

// DISABLE한 상품 통계
int get_product_sales_info(PRODUCT *phead, int *total_price)
{
    // VISIBLE
    PRODUCT* cur = phead;

    // 총 금액
    while (cur)
    {
        if (cur->status == DISABLE) {
            *(total_price) += cur->price;
        }
        cur = cur->next;
    }
    
    return ERR_PRODUCT_OK;
}

