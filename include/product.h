#ifndef PRODUCT_H
#define PRODUCT_H

#define ERR_PRODUCT_OK          0 /* 함수 성공 상수값 */
#define ERR_PRODUCT_CREATE  -1000 /* 메모리 할당 오류 코드 */
#define ERR_PRODUCT_ID      -1001 /* 아이디 부여 오류 코드 */
#define ERR_PRODUCT_FILE    -1002 /* 파일 입출력 오류 코드 */

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
    char model[100]; // 모델명
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
int increase_product_id(PRODUCT **product, PRODUCT *ptail);
int print_product_list(PRODUCT *phead, int page_no);
int print_all_product(PRODUCT *phead, int page_no);
int product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);
int product_copy(PRODUCT *origin, PRODUCT *copy);
int find_product(PRODUCT *tmp_product, int product_id);

int load_product(PRODUCT **phead, PRODUCT **ptail, const char *filename);
int save_product(PRODUCT *phead, const char *filename);

#endif