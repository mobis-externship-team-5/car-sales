#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui-printlist.h"
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





int print_list_stock(STOCK *sthead, int page_no,char element_column[][6][20],int arr[6]){
        STOCK *current = sthead;
        int chart_length = 72;
        int arr_size = 6;
//      ui_printlist_printroof('-','*');

        ui_printlist_printline('=');
        ui_printlist_printline('-');
        set_column_size(arr,chart_length,arr_size,element_column,1,0);
	ui_printlist_printline('-');

//�젙�닔�뒗 猷⑦듃 10�뀋�쑝濡� 吏쒕Ⅴ怨졼뀘�꽩
        for(int i=0; i<page_no*5;i++){
           if(current==NULL)
			break;
		current=current->next;
	}
        int count = 0;
        while (current)
    {
        if(count == 5)
                break;
        printf("|");
        printspace_string(current->model,arr[0]);
        printspace_int(current->quantity,arr[1]);
        printspace_string("",arr[2]);
        printspace_string("",arr[3]);
        printspace_string("",arr[4]);
        printspace_string("",arr[5]);
//printspace_string(stock_status_str[current->status],arr[0]);
        printf("\n");

        current = current->next;
        count++;
        }
        ui_printlist_printline('-');
        printf("\n                                   %d/10                           \n",page_no+1);
        ui_printlist_printline('=');


}
/*
int stock_search_ID(STOCK *sthead,STOCK **shead,STOCK **stail,int stock_id){
    STOCK *search, *smake;
       search = sthead;
    	*shead = NULL;
 
        while(search!=NULL){
            if( == search->model) {
                smake = (STOCK*)malloc(sizeof(STOCK));
                stock_copy(search,smake);
                if((*shead)==NULL){
                    *shead = *stail = smake;
               		break;
		 }
            }
            search = search->next;
        }
}
*/
int stock_search(STOCK *sthead, STOCK **shead, STOCK **stail,int *user_role, int opt2)
{
    int role = *user_role;
    STOCK *search, *smake;
    int opt = opt2;
    char m[100];
    
    search = sthead;
    *shead = NULL;
    if(opt==1){ // 紐⑤뜽紐낆쑝濡� 寃��깋
        printf("INPUT STOCK YOU WANT TO FIND: ");
        fgets(m,99,stdin);
        m[strlen(m)-1]='\0';
        while(search!=NULL){
            if(strcmp(m,search->model)==0) {
                smake = (STOCK*)malloc(sizeof(STOCK));
                stock_copy(search,smake);
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
        printf("IT's WRONG. \n");
    }
    return 0;
}

int stock_copy(STOCK *origin,STOCK *copy)
{
    copy->quantity = origin->quantity;
    strcpy(copy->model,origin->model);
    return 0;
}










