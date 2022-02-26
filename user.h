#ifndef USER_H
#define USER_H

#include "order.h"

enum USER_ROLE {
    CUSTOMER,
    ADMIN
};

typedef struct user_t {
    int id;
    char name[20];
    char password[20];
    enum USER_ROLE role;
} USER;

#endif;

/* 사용자 기능 */
// 고객 계정 생성 (관리자는 미리 생성된 계정 사용)
int signup();

// 아이디와 패스워드를 입력 받아
// 파일의 내용과 비교하는 연산 (사용자 정보가 파일에 저장되어 있는지 확인)
int login();

// 현재 사용자 변수 초기화 시키기
int logout();

// 프로그램 상에서 필요한 함수
int find_user(int id);

/* 관리자 기능 */

// 차량 입출고에 대한 정의

// 차량 입고 (프로그램 시작 시 또는 관리자 선택 시 차량 상품 삽입)
// 재고가 되기 전 목록들
int insert_product(PRODUCT **phead, PRODUCT **ptail, PRODUCT_DETAIL **dhead, PRODUCT_DETAIL **dtail); // TODO: tail
// UI의 흐름을 바탕으로 입력받은 product, detail
// struct 

// 상품의 정보를 입력합니다
// product detail malloc
// 모델 >> &product.model;


// 상품의 상세정보를 입력합니다
// 색상 >> &detail.color

// insert 마다 save, 


// 차랑 출고 (사용자가 '주문'을 하면 차량 상품 목록에서 DISABLE)
// 전체 주문 목록 출력, 팔았다 = 출고 == 주문
int print_order_list(ORDER *ohead);

// 재고 현황 확인 (차량 목록 출력)
// 상품 목록
// ABLE 값이 설정된 상품만 출력
// ABLE, DISABLE 모두 가능
int print_list_for_admin(PRODUCT *phead, int page_no);

// 회원 리스트 출력
int print_user_print(USER *uhead);

// 차량 재고 관리 함수는 여기 있어야하나?

