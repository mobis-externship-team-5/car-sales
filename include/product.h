#ifndef PRODUCT_H
#define PRODUCT_H

#define ERR_PRODUCT_OK           0  /* 함수 성공 상수값 */
#define ERR_PRODUCT_CREATE   -1000  /* 메모리 할당 오류 코드 */
#define ERR_PRODUCT_ID       -1001  /* 아이디 부여 오류 코드 */
#define ERR_PRODUCT_FILE     -1002  /* 파일 입출력 오류 코드 */
#define ERR_PRODUCT_NOTFOUND -1003  /* 상품 검색 실패 코드 */

/* 판매 상태 */
enum PRODUCT_STATUS {
    ABLE,
    DISABLE
};
char *product_status_str[] = { "ABLE", "DISABLE" };

/* 제조사 */
enum OEM {
    HYUNDAI,
    KIA,
    GENESIS
};
char *oem_str[] = { "HYUNDAI", "KIA", "GENESIS" };

/* 연료 */
enum FUEL {
    GASOLINE,
    DIESEL,
    LPG,
    EV,
    HEV,
    FCEV
};
char *fuel_str[] = { "GASOLINE", "DIESEL", "LPG", "EV", "HEV", "FCEV" };

/* 차량 상품 */
typedef struct product_t {
    int product_id;
    char model[50]; // 모델명
    enum OEM oem; // 제조사
    int price; // 가격
    enum FUEL fuel; // 연료
    double gas_mileage; // 연비
    enum PRODUCT_STATUS status; // 상품의 판매 상태

    struct product_t *next;
} PRODUCT;

typedef PRODUCT *LP_PRODUCT;

int create_product(PRODUCT **product);
int link_product(PRODUCT **phead, PRODUCT **ptail, PRODUCT **product);
int insert_product(PRODUCT **phead, PRODUCT **ptail);
int input_product_info(PRODUCT **product, PRODUCT *ptail);
int set_product_id(PRODUCT **product, PRODUCT *ptail);
int print_product_list(PRODUCT *phead, int page_no);
int product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail,int *user_role,int opt);
int product_copy(PRODUCT *origin,PRODUCT *copy);

int product_search_ID(PRODUCT *phead,PRODUCT **shead,PRODUCT **stail,int product_id);

int print_product_list_in_detail(PRODUCT *phead);

int print_list_product(PRODUCT *phead, int page_no, char element_column[][6][20], int arr[6], int ign_status);

int find_product(PRODUCT *phead, PRODUCT **product, int product_id);

int load_product(PRODUCT **phead, PRODUCT **ptail, const char *filename);
int save_product(PRODUCT *phead, const char *filename);

int get_product_sales_info(PRODUCT *phead, int *total_price);

int product_search_price(PRODUCT *phead,PRODUCT **shead,PRODUCT **stail,int *user_role, int *price_min,int *price_max);

#endif

