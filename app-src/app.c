#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui-printlist.h"
#include "ui-printlist-ex.h"
#include "file-name.h"
#include "user.h"
#include "product.h"
#include "product-detail.h"
#include "stock.h"
#include "order.h"

int ui_basic_form_top(char *page_name);
int ui_basic_form_bottom();
int ui_basic_form_up();
int ui_login(char *switch_value);
int ui_main_window(char *switch_value);
int ui_mypage(char *switch_value);
int ui_product_search(char *switch_value);
int ui_product_detail(char *switch_value);
int ui_purchase();
int ui_order_list(char *switch_value);
int ui_stock_list(char *switch_value);
int ui_login_check();
int ui_signup();


int err_code;

USER cur_user;

USER *uhead, *utail;    /* 사용자 연결 리스트 */
PRODUCT *phead, *ptail; /* 상품 연결 리스트 */
STOCK *sthead, *sttail; /* 재고 연결 리스트 */
ORDER *ohead, *otail;   /* 주문 연결 리스트 */

LPHASH pdhash; /* 상품 상세설명 해시 */
PRODUCT_DETAIL *cur_product_detail;


int main(void)
{
    char switch_value; // 메뉴 번호
    
    /* 변수 초기화 */
    uhead = utail = NULL;
    phead = ptail = NULL;
    sthead = sttail = NULL;
    ohead = otail = NULL;

    err_code = hashCreate(&pdhash);
    if (ERR_HASH_OK != err_code)
    {
        return 0;
    }

    /* 구조체 데이터 로드 */
    load_product(&phead, &ptail, PRODUCT_FILE);
    load_product_detail(&pdhash, PRODUCT_DETAIL_FILE);
    load_stock(&sthead, &sttail, STOCK_FILE);
    load_order(&ohead, &otail, ORDER_FILE);

    // 파일로부터 데이터 로드 후 결과 출력
    print_product_list(phead, 0); // phead, page_no
    print_product_detail_list(pdhash);
    print_stock_list(sthead);
    print_all_order_list(ohead);

    // [start] 필요한 만큼 데이터 입력이 끝나시면, start~end 블럭 지워주시면 됩니다!
    
    // // loop 만큼 상품과 상세정보를 입력합니다.
    // for(int i=0; i<6; i++) {
    //     insert_product(&phead, &ptail);
    //     insert_product_detail(ptail->product_id, &pdhash);
    //     increase_stock(&sthead, &sttail, ptail->model);
    // }

    // // 상품과 상세정보 추가 후 결과
    // print_product_list(phead, 0); // phead, page_no
    // print_product_detail_list(pdhash);
    // print_stock_list(sthead);

    //  // 재고 삭제 확인 블럭
    // decrease_stock(&sthead, &sthead, "AAA");
    // print_stock_list(sthead);
    // decrease_stock(&sthead, &sthead, "FFF");
    // print_stock_list(sthead);

    // 0) EXIT 메뉴를 통해 프로그램을 정상종료 할 경우 입력했던 상품 목록들이 파일에 저장됩니다.
    
    purchase(&ohead, &otail, "nayeon", "nayeon", 0);
    purchase(&ohead, &otail, "nayeon", "nayeon", 1);
    print_all_order_list(ohead);

    // [end]

    //  int* page;
    // *switch_value = '1';
    printf("-- PROGRAM START --\n\n");
    printf("START LOGIN:1\nEXIT:0\n");
    printf("-> SELECT MENU : ");

    scanf("%c", &switch_value);
    getchar();
    while (1)
    {
        switch (switch_value)
        {
        case '1':
            system("clear");
            ui_login(&switch_value); //
            break;                   //로그인 화면으로
        case '2':
            system("clear");
            ui_main_window(&switch_value);
            break; //메인 화면으로
        case '3':
            system("clear");
            ui_mypage(&switch_value); //마이페이지로
            break;                    //
        case '0':
            printf("-- PROGRAM END --"); //프로그램 엔드

            /* 구조체 데이터 저장 */
            save_product(phead, PRODUCT_FILE);
            save_product_detail(pdhash, PRODUCT_DETAIL_FILE);
            save_stock(sthead, STOCK_FILE);
            save_order(ohead, ORDER_FILE);

            exit(0);
            break;
        }
    }
    return 0;
}

int ui_login(char *switch_value)
{

    char switch_value_login;
    ui_basic_form_top("LOGIN");
    ui_basic_form_bottom();
    printf("\n");
    printf("                           |                                \n");
    printf("         1.LOGIN           |                                \n");
    printf("         2.FINDIDPW        |         4.NONUSER              \n");
    printf("         3.REGISTER        |                                \n");
    printf("                           |                                \n");
    printf("                           |                                \n");
    ui_basic_form_bottom();
    printf("\n                            ★★ MENU ★★\n1:LOGIN\n2:FINDIDPW\n3:REGISTER\n4:NONUSER\n0:EXIT");
    printf("\n\n-> SELECT MENU :");
    scanf("%c", &switch_value_login);
    getchar();
    switch (switch_value_login)
    {
    case '1':
        //로그인 확인으로 이동

        system("clear");

        ui_login_check(switch_value);
        //*switch_value = '2';
        break;

    case '2':
        system("clear");
        //로그인 찾기로 이동
        printf("ui_find_user\n");
        //ui_find_user(*switch_value);
        *switch_value = '1';
        break;

    case '3': //로그인 회원가이;ㅂ으로 이동
        system("clear");
        ui_signup(switch_value);
        printf("ui_signup\n");
        break;

    case '4':
        //set nouser role을 비유저로 적용
        system("clear");
        //ui_login_check(*switch_value);
        printf("login B user\n");
        *switch_value = '2';
        break;

    default:
        printf("%c\n", switch_value_login);
        printf("%c\n", *switch_value);
        exit(0);
        break;
    }

    printf("\n\n");
}


int ui_main_window(char *switch_value)
{

    char switch_value_main;
    while (1)
    {

        if (switch_value_main == '7')
        {
            system("clear");
            *switch_value = '3'; //마이페이지로
            break;
        }
        else if (switch_value_main == '8')
        {
            system("clear");
            *switch_value = '2'; //메인
            break;
        }
        else if (switch_value_main == '9')
        {
            system("clear");
            *switch_value = '1'; //로그아웃
            break;
        }
        else if (switch_value_main == '0')
        {
            system("clear");
            *switch_value = '0'; //종료
            break;
        }
        ui_basic_form_top("MAIN");

        // print_list_product();
        print_product_list(phead, 0);

        printf("                              ★★ MENU ★★\n1:SEARCH\n2:SORT\n3:DETAIL\n4:PREVIOUS\n5:NEXT\n7:MYPAGE\n8:MAIN\n9:LOGOUT\n0:EXIT\n\n");
        printf("-> SELECT MENU :");

        scanf("%c", &switch_value_main);

        getchar();
        switch (switch_value_main)
        {
        case '1': //search
            //ui_product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);
            ui_product_search(&switch_value_main); //�뜝�럥�뿰�뼨轅명�ｉ뇡�쉻�삕�굢占� scanf
            break;
        case '2': //sort
            system("clear");
            printf("sort window\n");
            //ui_sort
            break;
        case '3': //detail
            system("clear");
            ui_product_detail(&switch_value_main);
            //ui_product_detail(PRODUCT *phead, PRODUCT_DETAIL *dhead, int product_id);
            break;
        case '4': //previous
                  //set nouser role
            system("clear");
            printf("previous\n");
            *switch_value = '2';
            break;
        case '5': //next
            system("clear");
            printf("next\n");
            *switch_value = '2';
            break;
        }
    }
}

int ui_mypage(char *switch_value)
{

    char switch_value_mypage;

    while (1)
    {

        if (switch_value_mypage == '7')
        {
            system("clear");
            *switch_value = '3';
            break;
        }
        else if (switch_value_mypage == '8')
        {
            system("clear");
            *switch_value = '2';
            break;
        }
        else if (switch_value_mypage == '9')
        {
            system("clear");
            *switch_value = '1';
            break;
        }
        else if (switch_value_mypage == '0')
        {
            system("clear");
            *switch_value = '0';
            break;
        }
        ui_basic_form_top("MYPAGE");
        ui_basic_form_bottom();
        printf("\n");
        printf("ID       : ABCD\n");
        printf("PASSWORD : ****\n");
        printf("NICKNAME : WOW \n");
        printf("REALNAME : WOW \n");

        ui_basic_form_bottom();
        printf("\n                              ★★ MENU ★★\n1:REVISING INFO\n2:BUYING LIST\n3:BUCKET LIST\n4:MEMBER LIST\n5:SALES LIST\n6:STOCK LIST\n7:MYPAGE\n8:MAIN\n9:LOGOUT\n0:EXIT\n\n");
        printf("-> Select Menu :");
        scanf("%c", &switch_value_mypage);
        getchar();
        switch (switch_value_mypage)
        {
        case '1': //revising info
            system("clear");
            printf("revising info\n");
            //ui_product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail); ;
            break;
        case '2': //BUYING LIST
                  //ui_order_list(ORDER *ohead, PRODUCT *phead);
            system("clear");
            ui_order_list(switch_value);
            break;
        case '3': //STOCK LIST
            system("clear");
            ui_stock_list(switch_value);
            break;
        case '4': //MEMBER LIST
                  //ui_member_list()
                  //set nouser role
            system("clear");
            printf("MEMBERLIST\n");
            break;
        case '5': //SALES LIST
            system("clear");
            printf("SALESLIST\n");
            //ui_sales_list()
            break;
        }
    }
}

int ui_product_search(char *switch_value)
{

    char switch_value_search;

    while (1)
    {
        if (switch_value_search == '7')
        {
            system("clear");
            *switch_value = '7';
            break;
        }
        else if (switch_value_search == '8')
        {
            system("clear");
            *switch_value = '8';
            break;
        }
        else if (switch_value_search == '9')
        {
            system("clear");
            *switch_value = '9';
            break;
        }
        else if (switch_value_search == '0')
        {
            system("clear");
            *switch_value = '0';
            break;
        }

        ui_basic_form_top("SEARCH");
        //printf("\n                              SEARCH\n\n");
        print_list_product(element_product, element_column_product, arr);

        printf("                           ★★ SEARCH MENU ★★\nA) PRODUCT_ID :  (ex: 123456)\n");
        printf("B) MODEL : (ex: HYUNDAI)\n");
        printf("C) OEM : (ex: 0,1,2n");
        printf("D) GAS_MILLEGE : (ex: 22.)\n");
        printf("E) FUEL : (ex: 0,1,2)\n");
        printf("F) PRICE : (ex: 2000 4000)\n");
        printf("G) Search Start\n");
        printf("\n");

        ui_basic_form_bottom();
        printf("\n                              ★★ MENU ★★\n3:DETAILS\n4:PREVIOUS\n5:NEXT\n7:MYPAGE\n8:MAIN\n9:LOGOUT\n0:EXIT\n\n");
        printf("-> Select Menu :");
        scanf("%c", &switch_value_search);
        getchar();
        switch (switch_value_search)
        {

        case 'A': //Name
            system("clear");
            printf("scanf A\n");
            //scanf(%s,name)
            break;
        case 'B': //Brand
            system("clear");
            printf("scanf B\n");
            //scanf(%s,brand);
            break;
        case 'C': //Engine
            system("clear");
            printf("scanf C\n");
            //scanf(%s,engine);
            break;
        case 'D': //kind
            system("clear");
            printf("scanf D\n");
            // scanf(%s,kind);
            break;
        case 'E': //price
            system("clear");
            printf("scanf E\n");
            printf("scanf E2\n");
            //  scanf(%d,lowprce);
            //  scanf(%d,highprice);
            break;
        case 'F': //GAS
            system("clear");
            printf("scanf E\n");
            //  scanf(%d,lowprce);
            //  scanf(%d,highprice);
            break;
        case 'G': //search_start
            system("clear");
            printf("scanf start\n");
            //   int product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);
            break;
        case '3': //detail
            system("clear");
            ui_product_detail(&switch_value_search);
            break;
        case '4': //previous
            break;
        case '5': //next
            system("clear");
            ui_product_detail(&switch_value_search);
            break;
        }
    }
}

int ui_product_detail(char *switch_value)
{

    char switch_value_detail;
    while (1)
    {
        //printf("\n                              DETAILS\n");

        if (switch_value_detail == '7')
        {
            system("clear");
            *switch_value = '7';
            break;
        }
        else if (switch_value_detail == '8')
        {
            system("clear");
            *switch_value = '8';
            break;
        }
        else if (switch_value_detail == '9')
        {
            system("clear");
            *switch_value = '9';
            break;
        }
        else if (switch_value_detail == '0')
        {
            system("clear");
            *switch_value = '0';
            break;
        }
        //scanfswitch_value_login
        ui_basic_form_top("DETAILS");
        print_list_product(element_detail, element_column_detail, arr_detail);

        printf("                              ★★ Menu ★★\n1:APPLY PURCHASING\n7:MYPAGE\n8:MAIN\n9:LOGOUT\n0:EXIT\n\n");
        printf("-> Select Menu :");
        scanf("%c", &switch_value_detail);
        getchar();
        switch (switch_value_detail)
        {
        case '1': //APPLY PURCHASING
            system("clear");
            ui_purchase();
            break;
        }
    }
}

int ui_purchase()
{

    char switch_value_purchase;
    ui_basic_form_top("PURCHASE");
    //  printf("\n                              PURCHASE\n\n");

    ui_basic_form_bottom();
    printf("\n");
    printf("\nA) YOUR ID : (ex: sonata)\n");
    printf("B) YOUR PW : (ex: HYUNDAI)\n");
    printf("C) CHECK PW : (ex: Digeal\n");
    printf("D) PHONENUMBER: (ex: SUV)\n");
    printf("E) NICKNAME : (ex: 2000 4000\n");
    printf("F) REALNAME : (ex: 2000 4000\n");
    printf("G) WHAT IS YOUR FIRST SCHOOL NAME: (ex:hyocheon)\n");
    printf("X) REGISTER\n");
    printf("Y) GO LOGIN STATE\n");
    printf("Z) EXIT\n");
    printf("+++++++++++++++++++++++++++\n");
    printf("Select AND INSERT INFO  : (ex: A SONATA)\n");
    ui_basic_form_bottom();

    printf("\n                              ★★ MENU ★★\n1:PURCHASING\n0:EXIT\n\n");
    printf("-> SELECT MENU :");

    scanf("%c", &switch_value_purchase);
    getchar();
    /*if(switch_value_purchase == '7'){
                *switch_value = '3';
                break;
        }
        else if(switch_value_purchase == '8'){
            *switch_value = '2';
            break;
        }
        else if (switch_value_purchase == '9'){
            *switch_value = '1';
            break;
        }
        else if(switch_value_purchase == '0'){
            *switch_value = '0';
            break;
        }*/
    //scanfswitch_value_login
    switch (switch_value_purchase)
    {
    case '1': //PURCHASING
              //purchase(ORDER **ohead, ORDER **otail, PRODUCT *phead, int user_id, int product_id);
        system("clear");
        printf("purchase\n");
        break;
    case '0': //exit
        printf("exit\n");
        break;
    }
}

int ui_order_list(char *switch_value)
{

    char switch_value_order;

    while (1)
    {

        if (switch_value_order == '7')
        {
            system("clear");

            *switch_value = '3';
            break;
        }
        else if (switch_value_order == '8')
        {
            system("clear");
            *switch_value = '2';
            break;
        }
        else if (switch_value_order == '9')
        {
            system("clear");
            *switch_value = '1';
            break;
        }
        else if (switch_value_order == '0')
        {
            system("clear");
            *switch_value = '0';
            break;
        }
        ui_basic_form_top("MYPAGE_ADMIN_STOCKLIST");
        //printf("\n                              MYPAGE_ADMIN_STOCKLIST\n\n");

        print_list_product(element_order, element_column_order, arr_order);

        printf("\n                              ★★ MENU ★★\n1:SEARCH\n2:SORT\n3:DETAIL\n4:PREVIOUS\n5:NEXT\n7:MAIN\n8:MYPAGE\n9:LOGOUT\n0:EXIT\n\n");
        printf("-> SELECT MENU :");

        //嶺뚮∥���占쎈��

        //scanfswitch_value_login

        scanf("%c", &switch_value_order);
        getchar();
        switch (switch_value_order)
        {
        case '1': //search
                  //ui_product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);
            system("clear");
            ui_product_search(&switch_value_order);
            break;
        case '2': //sort
            system("clear");
            printf("sort window\n");
            //ui_sort
            break;
        case '3': //detail
            system("clear");
            ui_product_detail(&switch_value_order);
            //ui_product_detail(PRODUCT *phead, PRODUCT_DETAIL *dhead, int product_id);
            break;
        case '4': //previous
                  //set nouser role
            system("clear");
            printf("previous\n");
            *switch_value = '2';
            break;
        case '5': //next
            system("clear");
            printf("next\n");
            *switch_value = '2';
            break;
        }
    }
}

int ui_stock_list(char *switch_value)
{

    char switch_value_stock;

    while (1)
    {

        if (switch_value_stock == '7')
        {
            system("clear");
            *switch_value = '3';
            break;
        }
        else if (switch_value_stock == '8')
        {
            system("clear");
            *switch_value = '2';
            break;
        }
        else if (switch_value_stock == '9')
        {
            system("clear");
            *switch_value = '1';
            break;
        }
        else if (switch_value_stock == '0')
        {
            *switch_value = '0';
            break;
        }
        ui_basic_form_top("MYPAGE_ADMIN_STOCKLIST");
        printf("\n                              MYPAGE_ADMIN_STOCKLIST\n\n");
        print_list_product(element_stock, element_column_stock, arr_stock);

        printf("\n                              ★★ MENU ★★\n1:SEARCH\n2:SORT\n3:DETAIL\n4:PREVIOUS\n5:NEXT\n7:MAIN\n8:MYPAGE\n9:LOGOUT\n0:EXIT\n\n");
        printf("-> SELECT MENU :");

        scanf("%c", &switch_value_stock);
        getchar();
        switch (switch_value_stock)
        {
        case '1': //search
            //ui_product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);
            ui_product_search(&switch_value_stock);
            break;
        case '2': //sort
            printf("sort window\n");
            //ui_sort
            break;
        case '3': //detail
            ui_product_detail(&switch_value_stock);
            //ui_product_detail(PRODUCT *phead, PRODUCT_DETAIL *dhead, int product_id);
            break;
        case '4': //previous
            printf("previous\n");
            *switch_value = '2';
            break;
        case '5': //next
            printf("next\n");
            *switch_value = '2';
            break;
        }
    }
}

int ui_login_check(char *switch_value)
{

    char switch_value_login_check;

    ui_basic_form_top("LOGIN_CHECK");
    //      printf("\n                              LOGIN\n\n");

    ui_basic_form_bottom();
    printf("\n");
    printf("\nA) YOUR ID : (ex: sonata)\n");
    printf("B) YOUR PW : (ex: HYUNDAI)\n");
    printf("C) LOGIN : (ex: HYUNDAI)\n");
    printf("9) GO BAC : (ex: Digeal\n");
    printf("0) EXIT: (ex: SUV)\n");
    /* printf("E) NICKNAME : (ex: 2000 4000\n");
        printf("F) REALNAME : (ex: 2000 4000\n");
        printf("G) WHAT IS YOUR FIRST SCHOOL NAME: (ex:hyocheon)\n");*/

    ui_basic_form_bottom();
    printf("\n");
    printf("-> SELECT MENU :");

    scanf("%c", &switch_value_login_check);
    getchar();

    switch (switch_value_login_check)
    {

    case 'A': //Name
        printf("scanf A\n");
        //scanf(%s,name)
        system("clear");
        break;
    case 'B': //Brand
        printf("scanf B\n");
        system("clear");
        //scanf(%s,brand);
        break;
    case 'C': //Engine
        printf("scanf C\n");
        *switch_value = '2';
        system("clear");
        //scanf(%s,engine);
        break;
    case '9':
        printf("GO BACK");
        system("clear");
        *switch_value = '1';
        break;
    default:
        printf("exit");
        system("clear");
        *switch_value = '0';
        break;
    }

    //*switch_value = '2';
}
/*int ui_find_user(*switch_value){}
    *switch_value = '1';
}*/

int ui_signup(char *switch_value)
{
    char switch_value_sign_up;

    ui_basic_form_top("SIGN UP");
    //      printf("\n                              SIGN_UP\n\n");

    //signup(USER_HEAD,USER_TAIL);
    ui_basic_form_bottom();
    printf("\n");
    printf("\nA) YOUR ID : (ex: sonata)\n");
    printf("B) YOUR PW : (ex: HYUNDAI)\n");
    printf("C) CHECK PW : (ex: Digeal\n");
    printf("D) PHONENUMBER: (ex: SUV)\n");
    printf("E) ADDR : (ex: 2000 4000\n");
    printf("G) REGISTER\n");
    printf("9) GO LOGIN STATE\n");
    printf("0) EXIT\n");

    /* printf("E) NICKNAME : (ex: 2000 4000\n");
        printf("F) REALNAME : (ex: 2000 4000\n");
        printf("G) WHAT IS YOUR FIRST SCHOOL NAME: (ex:hyocheon)\n");*/

    ui_basic_form_bottom();
    scanf("%c", &switch_value_sign_up);
    getchar();
    printf("-> SELECT MENU :");
    switch (switch_value_sign_up)
    {

    case 'A': //Name
        printf("scanf A\n");
        //scanf(%s,name)
        system("clear");
        break;
    case 'B': //Brand
        printf("scanf B\n");
        //scanf(%s,brand);
        system("clear");
        break;
    case 'C': //Engine
        printf("scanf C\n");
        *switch_value = '2';
        //scanf(%s,engine);
        system("clear");
        break; //Name
    case 'D':  //Brand
        printf("scanf B\n");
        //scanf(%s,brand);
        system("clear");
        break;
    case 'E': //Engine
        printf("scanf C\n");
        *switch_value = '2';
        //scanf(%s,engine);
        system("clear");
        break; //Name
        printf("scanf A\n");
        //scanf(%s,name)
        system("clear");
        break;
    case 'G': //Brand
        printf("scanf B\n");
        *switch_value = '2';
        system("clear");
        break;
    case '9':
        printf("GO BACK");
        *switch_value = '1';
        system("clear");
        break;
    default:
        printf("exit");
        *switch_value = '0';
        system("clear");
        break;
    }

    //   *switch_value = '2';
}

int ui_basic_form_top(char *page_name)
{

    for (int i = 0; i < 5; i++) // 5번 반복. 바깥쪽 루프는 세로 방향
    {
        for (int j = 0; j < 72; j++) // 5번 반복. 안쪽 루프는 가로 방향
        {
            if (i == 0 || i == 4)
                printf("-");
            else if (i == 2)
            {
                if (j == 0 || j == 71)
                    printf("*");

                else
                {
                    int item_size = strlen(page_name);
                    if (j < (72 - item_size + 1) / 2)
                    {
                        printf(" ");
                    }
                    else if (j == (72 - item_size + 1) / 2)
                    {
                        printf("%s", page_name);
                    }
                    else if (j < (72 - item_size))
                    {
                        printf(" ");
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            else
            {
                if (j == 0 || j == 71)
                    printf("*");
                else
                    printf(" ");
                // 별 출력
            }
        }
        printf("\n"); // 가로 방향으로 별을 다 그린 뒤 다음 줄로 넘어감
    }
}


int ui_basic_form_bottom()
{
    for (int i = 0; i < 72; i++)
        printf("=");
}