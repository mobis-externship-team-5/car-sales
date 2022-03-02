#ifndef PRODUCT_DETAIL_H
#define PRODUCT_DETAIL_H

#include "hash.h"

#define ERR_PRODUCT_DETAIL_OK           0 /* 함수 성공 시 상수값 */
#define ERR_PRODUCT_DETAIL_CREATE   -2000 /* 메모리 할당 시 오류 코드 */
#define ERR_PRODUCT_DETAIL_FILE     -2001 /* 파일 입출력 오류 코드 */

enum SIZE {
    COMPACT,
    MEDIUM,
    FULL_SIZE,
    TRUCK
};
char *size_str[] = { "COMPACT", "MEDIUM", "FULL_SIZE", "TRUCK" };

typedef struct product_detail_t {
    int product_id;
    char detail_name[100];
    char color [20];
    enum SIZE size;
    int cc;

    struct product_detail_t *next;
} PRODUCT_DETAIL;

int create_product_detail(PRODUCT_DETAIL **product_detail);
int insert_product_detail(int product_id, LPHASH *pdhash);
int input_product_detail(PRODUCT_DETAIL **product_detail);
int find_product_detail(LPHASH pdhash, int product_id, PRODUCT_DETAIL **product_detail);
int print_product_detail_list(LPHASH pdhash);
int print_product_detail(PRODUCT_DETAIL *product_detail);

int load_product_detail(LPHASH *pdhash, char *filename);
int save_product_detail(LPHASH pdhash, char *filename);

#endif