#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "product-detail.h"


int create_product_detail(PRODUCT_DETAIL **product_detail)
{
    *product_detail = (PRODUCT_DETAIL *)malloc(sizeof(PRODUCT_DETAIL));
    if (*product_detail == NULL) {
        return ERR_PRODUCT_DETAIL_CREATE;
    }

    return ERR_PRODUCT_DETAIL_OK;
}


int insert_product_detail(int product_id, LPHASH *pdhash)
{
    int err_code;
    
    PRODUCT_DETAIL *new_product_detail;
    err_code = create_product_detail(&new_product_detail);
    if (ERR_PRODUCT_DETAIL_OK != err_code) {
        return err_code;
    }

    input_product_detail(&new_product_detail);

    err_code = hashSetValue(pdhash, product_id, (LPDATA) new_product_detail);
    if (ERR_HASH_OK != err_code) {
		printf("%s:%d error code = %d\n",__FILE__, __LINE__, err_code);
	}

    return ERR_PRODUCT_DETAIL_OK;
}


int input_product_detail(PRODUCT_DETAIL **product_detail)
{
    int i;
    int err_code;

    printf("\nINPUT VEHICLE DETAILS\n\n");
    
    printf("DETAIL NAME\n>> ");
    fgets((*product_detail)->detail_name, sizeof((*product_detail)->detail_name)-1, stdin);
    (*product_detail)->detail_name[strlen((*product_detail)->detail_name) - 1] = '\0';

    printf("COLOR\n>> ");
    fgets((*product_detail)->color, sizeof((*product_detail)->color)-1, stdin);
    (*product_detail)->color[strlen((*product_detail)->color) - 1] = '\0';

    printf("SIZE NUMBER - ");
    for(i=0; i<sizeof(size_str)/sizeof(char*); i++) {
        printf("%d (%s)\t", i, size_str[i]);
    }
    printf("\n>> ");
    scanf("%d", &(*product_detail)->size);

    printf("CC\n>> ");
    scanf("%d", &(*product_detail)->cc); getchar();
    
    return ERR_PRODUCT_DETAIL_OK;
}


int find_product_detail(LPHASH pdhash, int product_id, PRODUCT_DETAIL **product_detail)
{
    int err_code;
    
    err_code = hashGetValue(pdhash, product_id, (LPDATA *) product_detail);
    if (ERR_HASH_OK != err_code) {
		printf("%s:%d error code = %d\n",__FILE__, __LINE__, err_code);
	} else {
    	//key 값과 value를 ?력한다.
    	printf("key = %d\n", product_id);
        print_product_detail(*product_detail);
    }

    return ERR_HASH_OK;
}


int print_product_detail_list(LPHASH pdhash)
{
    int err_code;
    POSITION pos;
    int key;
    PRODUCT_DETAIL* value;

    // 해시 테이블의 처음 위치를 pos에 저장
    err_code = hashGetFirstPostion(pdhash, &pos);
    if (ERR_HASH_OK != err_code) {
		printf("%s:%d error code = %d\n",__FILE__, __LINE__, err_code);
	}

	//다음 위치로 이동하여 
	while (NULL != pos) {
		err_code = hashGetNextPostion(pdhash, &pos, &key, (LPDATA*) &value);
		if (ERR_HASH_OK != err_code) {
			printf("%s:%d error code = %d\n",__FILE__, __LINE__, err_code);
			break;
		}
		
		print_product_detail(value);
	}
    
    return ERR_PRODUCT_DETAIL_OK;
}


int print_product_detail(PRODUCT_DETAIL *product_detail)
{
    printf("%10s %10s %10s %10d\n",
            product_detail->detail_name, product_detail->color, size_str[product_detail->size],
            product_detail->cc);

    return ERR_PRODUCT_DETAIL_OK;
}


int load_product_detail(LPHASH *pdhash, char *filename)
{
    int err_code;
    FILE *fp;
    PRODUCT_DETAIL *new_product_detail;

    if ((fp = fopen(filename, "r")) == NULL) {
        return ERR_PRODUCT_DETAIL_FILE;
    }

    while (1)
    {
        create_product_detail(&new_product_detail);

        if ((fread(new_product_detail, sizeof(PRODUCT_DETAIL), 1, fp))) {
            err_code = hashSetValue(pdhash, new_product_detail->product_id, (LPDATA) new_product_detail);
            if (ERR_HASH_OK != err_code) {
                printf("%s:%d error code = %d\n",__FILE__, __LINE__, err_code);
            }
        }
        else {
            free(new_product_detail);
            break;
        }
    }

    fclose(fp);
    return ERR_PRODUCT_DETAIL_OK;
}

int save_product_detail(LPHASH pdhash, char *filename)
{
    int err_code;
    FILE *fp;
    POSITION pos;
    int key;
    PRODUCT_DETAIL* value;

    if ((fp = fopen(filename, "w")) == NULL) {
        return ERR_PRODUCT_DETAIL_FILE;
    }

    // 해시 테이블의 처음 위치를 pos에 저장
    err_code = hashGetFirstPostion(pdhash, &pos);
    if (ERR_HASH_OK != err_code) {
		printf("%s:%d error code = %d\n",__FILE__, __LINE__, err_code);
	}

	//다음 위치로 이동하여 
	while (NULL != pos) {
		err_code = hashGetNextPostion(pdhash, &pos, &key, (LPDATA*) &value);
		if (ERR_HASH_OK != err_code) {
			printf("%s:%d error code = %d\n",__FILE__, __LINE__, err_code);
			break;
		}

        fwrite(value, sizeof(PRODUCT_DETAIL), 1, fp);
	}

    fclose(fp);
    return ERR_HASH_OK;
}