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

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int ui_basic_form_top(char *page_name);
int ui_basic_form_bottom();
int ui_basic_form_up();

int ui_product_revice_user(char *switch_value, int *user_role);
int ui_login(char *switch_value, int *user_role);
int ui_main_window(char *switch_value, int *user_role);
int ui_mypage(char *switch_value, int *user_role);
int ui_product_search(char *switch_value, int *user_role);
int ui_product_detail(char *switch_value, int *user_role,int find_detail);
int ui_purchase();
int ui_order_list(char *switch_value, int *user_role);
int ui_stock_list(char *switch_value, int *user_role);
int ui_login_check(char *switch_value, int *user_role);
int ui_signup(char *switch_value, int *user_role);
int ui_user_list(char *switch_value, int *user_role);
int ui_sales_list(char* switch_value, int* user_role);


int err_code;

USER *cur_user; // 현재 로그인한 사용자
PRODUCT *cur_product; // 사용자가 확인 중인 상MEN품

USER *uhead, *utail;    /* 사용자 연결 리스트 */
USER *Suhead, *Sutail;    /* 사용자 연결 리스트 */
PRODUCT *phead, *ptail; /* 상품 연결 리스트 */
STOCK *sthead, *sttail; /* 재고 연결 리스트 */
STOCK *Ssthead, *Ssttail; /* 재고 연결 리스트 */
ORDER *ohead, *otail;   /* 주문 연결 리스트 */
PRODUCT *Sphead, *Sptail; /* 상품 검색  리스트 */


LPHASH pdhash;
PRODUCT_DETAIL *cur_product_detail;


int main(void)
{
   char switch_value; // 메뉴 번호
   int user_role;
  
   /* 변수 초기화 */
   uhead = utail = NULL;
   Suhead = Sutail = NULL;
   phead = ptail = NULL;
   sthead = sttail = NULL;
   ohead = otail = NULL;
   Sphead = Sptail = NULL;

   err_code = hashCreate(&pdhash);
   if (ERR_HASH_OK != err_code)
   {
      return 0;
   }

   /* 구조체 데이터 로드 */
   load_user(&uhead, &utail, USER_FILE);
   load_product(&phead, &ptail, PRODUCT_FILE);
   load_product_detail(&pdhash, PRODUCT_DETAIL_FILE);
   load_stock(&sthead, &sttail, STOCK_FILE);
   load_order(&ohead, &otail, ORDER_FILE);

   while(1){   
      system("clear");
      printf("-- PROGRAM START --\n\n");
      printf("START LOGIN:1\nEXIT:0\n");
      printf("-> SELECT MENU : ");

      //while(switch_value == '1' || switch_value == '0'){
      scanf("%c", &switch_value);
      clean_stdin();
      if(switch_value =='1' || switch_value == '0')
         break;
      system("clear");
      printf("CHOOSE ALRIGH MENU\n");
   }
   
   while (1)
   {
      system("clear");
      switch (switch_value)
      {
         case '1':
            ui_login(&switch_value, &user_role);
            break;                   //로그인 화면으로
         case '2':
            ui_main_window(&switch_value, &user_role);
            break; //메인 화면으로
         case '3':
            ui_mypage(&switch_value, &user_role); //마이페이지로
            break;                    //
         case '0':
            printf("-- PROGRAM END --\n\n"); //프로그램 엔드

            /* 구조체 데이터 저장 */
            save_user (uhead, USER_FILE);
            save_product(phead, PRODUCT_FILE);
            save_product_detail(pdhash, PRODUCT_DETAIL_FILE);
            save_stock(sthead, STOCK_FILE);
            save_order(ohead, ORDER_FILE);
            exit(0);
            break;
         default:
            switch_value = '0';
            printf("CHOOSE ALRIGHT MENU NUMBER!\n");
            break;

      }
   }
   return 0;



}

int ui_login(char *switch_value, int *user_role)
{
   char switch_value_login;
   ui_basic_form_top("LOGIN");
   ui_basic_form_bottom();
   printf("\n");
   printf("                                     |                               \n");
   printf("                                     |                               \n");
   printf("                                                                     \n");
   printf("                                 1.LOGIN                             \n");
   printf("                                 2.NON-USER                          \n");
   printf("                              	 3.REGISTER                          \n");
   printf("                                                                     \n");
   printf("                                     |                               \n");
   printf("                                     |                               \n");
   ui_basic_form_bottom();
   printf("\n                               ★★ MENU ★★\n 1 : LOGIN\n 2 : NON-USER\n 3 : REGISTER  \n 0 : EXIT");
   printf("\n\n-> SELECT MENU :");
   scanf("%c", &switch_value_login);
   clean_stdin();
   system("clear");    
   switch (switch_value_login)
   {
      case '1':
         //로그인 확인으로 이동
         ui_login_check(switch_value, user_role);
         //*switch_value = '2';
         break;
      case '2':
         *user_role = 0;
         *switch_value = '2';
         break;
      case '3':
         ui_signup(switch_value, user_role);
break;

      case '0':
         *switch_value ='0';
         break;
      default:
            *switch_value = '0';
      printf("CHOOSE ALRIGHT MENU NUMBER!\n");

         break;
   }

   return 0; 
}

int ui_main_window(char *switch_value, int *user_role)
{
   char switch_value_main;
   int page_no_main = 0;
   int find_detail;
   while (1)
   {

      if (switch_value_main == '7' && *user_role != 0)
      {   system("clear");
         *switch_value = '3'; //마이페이지로
         break;
      }
      else if (switch_value_main == '8')
      {   system("clear");
         *switch_value = '2'; //메인
         break;
      }
      else if (switch_value_main == '9')
      {   system("clear");
         *switch_value = '1'; //로그아웃
         break;
      }
      else if (switch_value_main == '0')
      {   system("clear");
         *switch_value = '0'; //종료
         break;
      }
      ui_basic_form_top("MAIN");

      // print_list_product();
      print_list_product(phead,page_no_main,element_column_product,arr_product,DISABLE); // phead, page_no
      if(*user_role !=0){
         printf("                              ★★ MENU ★★\n 1 : SEARCH\n 2 : DETAIL\n 3 : PREVIOUS LIST\n 4 : NEXT LIST\n 7 : MYPAGE \n 8 : MAIN \n 9 : LOGOUT \n 0 : EXIT\n\n");

         printf("-> SELECT MENU :");

         scanf("%c", &switch_value_main);

         clean_stdin();
         switch (switch_value_main)
         {
            case '1': //search
               system("clear");
               ui_product_search(&switch_value_main, user_role);
               break;
            case '2': //detail
               printf("INPUT PRODUCT ID YOU WANT TO SEE : ");
               scanf("%d",&find_detail);
               clean_stdin();

               // 해당되는 아이디의 상품이 존재하는지 검색: cur_product를 설정하기 위함
               err_code = find_product(phead, &cur_product, find_detail);
               if (ERR_PRODUCT_OK != err_code) {
                  system("clear");
                  ui_main_window(switch_value, user_role);
               }

               system("clear");
               err_code = find_product(phead, &cur_product, find_detail);
               if (ERR_PRODUCT_OK != err_code) {
                  *switch_value = '2'; //    
               }else{
                  ui_product_detail(&switch_value_main, user_role,find_detail);
               }
               break;
            case '3': //previous
               //set nouser role
               printf("previous\n");
               page_no_main--;
               if(page_no_main <0)
                  page_no_main = 0;
               *switch_value = '2';
               break;
            case '4': //next
               printf("next\n");
               page_no_main++;
               *switch_value = '2';
               break;
            case '7':
            case '8':
            case '9':
            case '0':
               break;
            default:
            *switch_value = '0';
               printf("CHOOSE ALRIGHT MENU NUMBER!\n");
               break;
         }
         system("clear");
      }else{
         printf("                              ★★ MENU ★★\n 1 : SEARCH\n 2 : DETAIL\n 3 : PREVIOUS LIST\n 4 : NEXT LIST\n 8 : LOGIN\n 9 : MAIN\n 0 : EXIT\n\n");
         printf("-> SELECT MENU :");

         scanf("%c", &switch_value_main);

         clean_stdin();
         switch (switch_value_main)
         {
            case '1': // search
               system("clear");

               ui_product_search(&switch_value_main,user_role);
               break;
            case '2': // detail
               printf("INPUT PRODUCT ID YOU WANT TO SEE : ");
               scanf("%d",&find_detail);
               clean_stdin();
               system("clear");

               err_code = find_product(phead, &cur_product, find_detail);
               if (ERR_PRODUCT_OK != err_code)
               {
                  printf("THERE's NO PRODUCT\n");
                  ui_main_window(switch_value, user_role);
               }
               else
               {
                  ui_product_detail(&switch_value_main,user_role,find_detail);
               }
               break;
            case '3': //previous
               //set nouser role
               printf("previous\n");
               page_no_main--;
               if(page_no_main <0)
                  page_no_main = 0;
               *switch_value = '2';
               break;
            case '4': //next
               printf("next\n");
               page_no_main++;
               *switch_value = '2';
               break;

            case '8': ///change to 9
               switch_value_main = '9';
               break;
            case '9': ///change to 8
               switch_value_main = '8';
               break;
            case '0':
               break;
            default:
            *switch_value = '0';
               printf("CHOOSE ALRIGHT MENU NUMBER!\n");
               break;
         }
         system("clear");
      }
   }
   return 0;
}

int ui_mypage(char *switch_value, int *user_role)
{

   char switch_value_mypage;
    int page_no_order = 0;

   while (1)
   {

      if (switch_value_mypage == '7')
      {   system("clear");
         *switch_value = '3';
         break;
      }
      else if (switch_value_mypage == '8')
      {   system("clear");
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
      printf("ID       : %s \n",cur_user->user_id);
      printf("PASSWORD : ");for(int lenpw =0; lenpw<strlen(cur_user->password);lenpw++)printf("*");
      printf("\nPHONENUMBER : %s \n",cur_user->phone);
      printf("ADDRESS : %s \n",cur_user->addr);

      ui_basic_form_bottom();
      if(*user_role !=2){
         printf("\n                              ★★ MENU ★★\n 1 : REVISING INFO\n 2 : ORDER LIST\n 7 : MYPAGE\n 8 : MAIN\n 9 : LOGOUT\n 0 : EXIT\n\n");
         printf("-> SELECT MENU :");
         scanf("%c", &switch_value_mypage);
         clean_stdin();
         system("clear");
         switch (switch_value_mypage)
         {
            case '1': // revising info
               ui_product_revice_user(&switch_value_mypage,user_role);
               break;
            case '2': // ORDER LIST
               ui_order_list(&switch_value_mypage,user_role);
               break;
            case '3': // BUCKET LIST
            case '7':
            case '8':
            case '9':
            case '0':
               break;
            default:
            *switch_value = '0';
               printf("CHOOSE ALRIGHT MENU NUMBER!\n");
               break;

         }
      }else{
         printf("\n                              ★★ MENU ★★\n 1 : REVISING INFO\n 2 : ORDER LIST\n 3 : USER LIST (you can see all users)\n 4 : SALES LIST (you can see how much cars are sold)\n 5 : STOCK LIST (you can manage stocks)\n 7 : MYPAGE\n 8 : MAIN\n 9 : LOGOUT\n 0 : EXIT\n\n");
         printf("-> SELECT MENU :");
         scanf("%c", &switch_value_mypage);
         clean_stdin();
         system("clear");
         switch (switch_value_mypage)
         {
            case '1': // revising info
               ui_product_revice_user(&switch_value_mypage,user_role);
               break;
            case '2': // BUYING LIST
               // ui_order_list(ORDER *ohead, PRODUCT *phead);
               ui_order_list(&switch_value_mypage,user_role);
               break;
            case '3': // 
               ui_user_list(&switch_value_mypage,user_role);
               break;
            case '4': // SALES LIST
               ui_sales_list(&switch_value_mypage, user_role);
               break;
            case '5': // STOCK LIST
               ui_stock_list(&switch_value_mypage,user_role);
               break;
            case '7':
            case '8':
            case '9':
            case '0':
               break;
            default:        
            *switch_value = '0';
               printf("CHOOSE ALRIGHT MENU NUMBER!\n");
               break;
         }
      }
   }
   return 0;
}


int ui_product_search(char *switch_value, int *user_role)
{

      int price_min=0, price_max =0;
   char switch_value_search;
   int page_no_search =0;
   int start_search = 0;
   int find_detail =0;
   Sphead = Sptail = NULL;
   while (1)
   {

      if (switch_value_search == '7' && *user_role !=0)
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
      //print_list_product(element_product, element_column_product, arr_product);
      if(Sphead==NULL && start_search ==1){
         print_list_product(NULL,page_no_search,element_column_product,arr_product,DISABLE); // phead, page_no
         printf("                           ★★ SEARCH OPTION ★★\n");
         printf(" A) MODEL    : \n");
         printf(" B) OEM    : \n");
         printf(" C) GAS_MILLEGE   :  \n");
         printf(" D) FUEL   : \n");
         printf(" E) PRICE    : \n");

      }else if(Sphead==NULL){
         print_list_product(phead,page_no_search,element_column_product,arr_product,DISABLE); // phead, page_no
         printf("                           ★★ SEARCH OPTION ★★\n");
         printf(" A) MODEL    : \n");
         printf(" B) OEM    : \n");
         printf(" C) GAS_MILLEGE :  \n");
         printf(" D) FUEL   : \n");
         printf(" E) PRICE    :\n");

      }else{
         print_list_product(Sphead,page_no_search,element_column_product,arr_product,DISABLE); // phead, page_no

         printf("                           ★★ SEARCH OPTION ★★\n");
         if(switch_value_search== 'A')
            printf(" A) MODEL    : %s\n",Sphead->model);
         else

            printf(" A) MODEL    : \n");
         if(switch_value_search== 'B')
            printf(" B) OEM    : %d\n",Sphead->oem);
         else
            printf(" B) OEM    : \n");
         if(switch_value_search== 'C')
            printf(" C) GAS_MILLEGE  :  %2.2f\n",Sphead->gas_mileage);
         else
            printf(" C) GAS_MILLEGE  :  \n");
         if(switch_value_search== 'D')
            printf(" D) FUEL    : %d\n",Sphead->fuel);
         else
            printf(" D) FUEL    : \n");

            if(switch_value_search== 'E')
               printf(" E) PRICE    : %d ~ %d\n",price_min, price_max);
            else
               printf(" E) PRICE    :\n");

      }

      printf("\n\n");
      ui_basic_form_bottom();
      if(1){
         printf("\n                              ★★ MENU ★★\n 1 : RESET (reset search list)\n 2 : DETAILS (you can see details and purchase car)\n 3 : PREVIOUS LIST\n 4 : NEXT LIST\n 7 : MYPAGE\n 8 : MAIN\n 9 : LOGOUT\n 0 : EXIT\n\n");
         printf("-> choose SEARCH OPTION or MENU OPTION :");
         scanf("%c", &switch_value_search);
         clean_stdin();

         switch (switch_value_search)
         {

            case 'A': //Name
               start_search =1;
               page_no_search = 0;
               product_search(phead,&Sphead,&Sptail,user_role,1);
               //scanf(%s,name)
               break;
            case 'B': //Brand
               //scanf(%s,brand);
               start_search =1;
               page_no_search = 0;
               product_search(phead,&Sphead,&Sptail,user_role,2);
               break;
            case 'C': //Engine
               start_search =1;
               page_no_search = 0;
               product_search(phead,&Sphead,&Sptail,user_role,5);
               //scanf(%s,engine);
               break;
            case 'D': //kind
               product_search(phead,&Sphead,&Sptail,user_role,4);
               start_search =1;
               page_no_search = 0;
               // scanf(%s,kind);
               break;
                        case 'E': //price
                  start_search =1;
                  page_no_search = 0;
                  product_search_price(phead,&Sphead,&Sptail,user_role,&price_min,&price_max);
               //  scanf(%d,lowprce);
               //  scanf(%d,highprice);
               break;
            case '1': //reset
               start_search =0;
               Sphead=NULL;
               break;
            case '2': //detail
               printf("INPUT PRODUCT ID YOU WANT TO SEE : ");
               scanf("%d",&find_detail);   
               clean_stdin();
               system("clear");
               err_code = find_product(phead, &cur_product, find_detail);
               if (ERR_PRODUCT_OK != err_code) {
                  printf("THERE's no PRODUCT\n");
                  ui_main_window(switch_value, user_role);
               }else{
                  ui_product_detail(&switch_value_search, user_role,find_detail);
               }
               break;
            case '3': //previous
               //set nouser role
               printf("previous\n");
               page_no_search--;
               if(page_no_search <0)
                  page_no_search = 0;
               break;
            case '4': //next
               printf("next\n");
               page_no_search++;
            case '7':
            case '8':
            case '9':
            case '0':
               break;
            default:
            *switch_value = '0';
               printf("CHOOSE ALRIGHT MENU NUMBER!\n");
               break;
         }
         system("clear");
      }else{
         printf("\n                              ★★ MENU ★★\n 2 : DETAILS\n 3 : PREVIOUS\n 4 : NEXT\n 9 : MAIN\n 0 : EXIT\n\n");
         printf("-> SELECT MENU :");
         scanf("%c", &switch_value_search);
         clean_stdin();
         switch (switch_value_search)
                     {   case 'A': //Name
                                        start_search =1;
                              page_no_search = 0;
                                        product_search(phead,&Sphead,&Sptail,user_role,1);
                                        //scanf(%s,name)
                                        break;
                                case 'B': //Brand
                                        //scanf(%s,brand);
                                        start_search =1;
                              page_no_search = 0;
                                        product_search(phead,&Sphead,&Sptail,user_role,2);
                                        break;
                                case 'C': //Engine
                                        start_search =1;
                              page_no_search = 0;
                                        product_search(phead,&Sphead,&Sptail,user_role,5);
                                        //scanf(%s,engine);
                                        break;
                                case 'D': //kind
                                        product_search(phead,&Sphead,&Sptail,user_role,4);
                                        start_search =1;
                              page_no_search = 0;
                                        // scanf(%s,kind);
                                        break;
                              case 'E': //price
                              start_search =1;
                              page_no_search = 0;
                              product_search_price(phead,&Sphead,&Sptail,user_role,&price_min,&price_max);
                                        //  scanf(%d,lowprce);
                                        //  scanf(%d,highprice);
                                        break;
                                case '1': //reset
                                        start_search =0;
                                        break;
                                case '2': //detail
                                        printf("INPUT PRODUCT ID YOU WANT TO SEE : ");
                                        scanf("%d",&find_detail);
                                        clean_stdin();
                                        system("clear");
                                        err_code = find_product(phead, &cur_product, find_detail);
                                        if (ERR_PRODUCT_OK != err_code) {
                                                printf("THERE's no PRODUCT\n");
                                                ui_main_window(switch_value, user_role);
                                        }else{
                                                ui_product_detail(&switch_value_search, user_role,find_detail);
                                        }
                                        break;
                                case '3': //previous
                                        //set nouser role
                                        printf("previous\n");
                                        page_no_search--;
                                        if(page_no_search <0)
                                                page_no_search = 0;
                                        break;
                                case '4': //next
                                        printf("next\n");
                                        page_no_search++;


            case '9':
               switch_value_search = '8';
               break;
            case '0':
               break;
            default:
            *switch_value = '0';
               printf("CHOOSE ALRIGHT MENU NUMBER!\n");
               break;
         }
         system("clear");
      }
   }
   return 0;
}

int ui_product_detail(char *switch_value, int *user_role,int find_detail)
{

   char switch_value_detail;
   while (1)
   {

      if (switch_value_detail == '7' &&  *user_role != 0)
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
      ui_basic_form_bottom();
   printf("\n");   
   product_search_ID(phead,&Sphead,&Sptail,find_detail);
      print_product_list_in_detail(Sphead);   
      find_product_detail(pdhash,find_detail,&cur_product_detail);
      ui_basic_form_bottom();
      if(*user_role != 0){
         printf("\n                              ★★ MENU ★★\n 1 : APPLY PURCHASING\n 7 : MYPAGE\n 8 : MAIN\n 9 : LOGOUT\n 0 : EXIT\n\n");
         printf("-> SELECT MENU :");
         scanf("%c",&switch_value_detail);
         clean_stdin();
         system("clear");
         switch (switch_value_detail)
         {
            case '1': // APPLY PURCHASING
               ui_purchase();
               printf("PRESS ENTER ...");
               clean_stdin();
               switch_value_detail = '8';
               break;
            case '7':
            case '8':
            case '9':
            case '0':
               break;
            default:
            *switch_value = '0';
               printf("CHOOSE ALRIGHT MENU NUMBER!\n");
               break;
         }
      }else{
         printf("\n                              ★★ MENU ★★\n 8 : LOGIN \n 9 : MAIN\n 0 : EXIT\n\n");
         printf("-> SELECT MENU :");
         scanf("%c", &switch_value_detail);
         clean_stdin();
         system("clear");
         switch (switch_value_detail)
         {
            case '8':
               switch_value_detail = '9';
               break;
            case '9':
               switch_value_detail = '8';
               break;
            case '0':
               break;
            default:
            *switch_value = '0';
               printf("CHOOSE ALRIGHT MENU NUMBER!\n");
               break;
         }
      }
   }
   return 0;
}
int ui_purchase()
{

   char switch_value_purchase;
   ui_basic_form_top("PURCHASE");
   //  printf("\n                              PURCHASE\n\n");

   ui_basic_form_bottom();
   printf("\n");
   printf("\n YOUR NAME : %s\n",cur_user->name);
   printf(" PHONENUMBER : %s \n",cur_user->phone);
   printf(" ADDRESS     :%s \n",cur_user->addr);
   printf("\n");
   ui_basic_form_bottom();
   printf("\n                      ★★ APPLYING CONSULTING MENU ★★\n");
   printf("\n");
   printf("\n     YOUR INFO IS USED BUYING CAR IF YOU AGREE SELECT 1 NOT 0");
   printf("\n");
   printf("\n");
   printf("\n                              ★★ MENU ★★\n 1 : PURCHASING\n 0 : EXIT\n\n");
   printf("-> SELECT MENU :");

   scanf("%c", &switch_value_purchase);
   clean_stdin();
   system("clear");
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
      case '1': // PURCHASING
         cur_product->status = DISABLE; // ?  ?  ?   ?  ?   ?  ? ?
         purchase(&ohead, &otail, cur_user->user_id, cur_user->name, cur_product->price, cur_product->product_id);
         err_code = decrease_stock(&sthead, &sttail, cur_product->model); // ?   ? ?  ?   감소
         if (ERR_STOCK_OK != err_code) {
            printf("FAILELD, CONTACT AGENT :(\n");
         }else{
            printf("THANKYOU FOR PURCHASING!\n");
         }
         break;
      case '0': // exit
         break;

   }
   return 0;
}


int ui_order_list(char *switch_value, int *user_role)
{
   char switch_value_order;
   int find_detail;
   int page_no_order = 0;
   while (1)
   {

      if (switch_value_order == '7')
      {
         system("clear");
         *switch_value = '7';
         break;
      }
      else if (switch_value_order == '8')
      {
         system("clear");
         *switch_value = '8';
         break;
      }
      else if (switch_value_order == '9')
      {
         system("clear");
         *switch_value = '9';
         break;
      }
      else if (switch_value_order == '0')
      {
         system("clear");
         *switch_value = '0';
         break;
      }
      ui_basic_form_top("MYPAGE_ORDERLIST");
      //printf("\n                              MYPAGE_ADMIN_STOCKLIST\n\n");

      print_list_order(ohead, page_no_order, element_column_order, arr_order, *user_role, cur_user);

      printf("\n                              ★★ MENU ★★\n 1 : SEARCH\n 2 : DETAIL\n 3 : PREVIOUS\n 4 : NEXT\n 7 : MYPAGE\n 8 : MAIN\n 9 : LOGOUT\n 0 : EXIT\n\n");
      printf("-> SELECT MENU :");

      //scanfswitch_value_login

      scanf("%c", &switch_value_order);
      clean_stdin();
      switch (switch_value_order)
      {
         case '1': // search
            // ui_product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);
            system("clear");
            ui_product_search(&switch_value_order,user_role);
            break;
         case '2': // detail
            printf("INPUT PRODUCT ID YOU WANT TO SEE : ");
            scanf("%d",&find_detail);
            getchar();

            system("clear");
            err_code = find_product(phead, &cur_product, find_detail);
            if (ERR_PRODUCT_OK != err_code) {
               printf("THERE's no PRODUCT\n");
               ui_main_window(&switch_value_order, user_role);
            }else{
               ui_product_detail(&switch_value_order, user_role, find_detail);
               
            }// ui_product_detail(PRODUCT *phead, PRODUCT_DETAIL *dhead, int product_id);
            break;
         case '3': //previous
            //set nouser role
            printf("previous\n");
            page_no_order--;
            if(page_no_order <0)
               page_no_order = 0;
            break;
         case '4': //next
            printf("next\n");
            page_no_order++;
            break;
         case '7':
         case '8':
         case '9':
         case '0':
            break;
         default:
            *switch_value = '0';
            printf("CHOOSE ALRIGHT MENU NUMBER!\n");
            break;
      }
      system("clear");
      }
   return 0;
}

int ui_sales_list(char* switch_value, int* user_role)
{

        char switch_value_sales;
      int page_no_sales = 0;
      int total_price = 0, total_user = 0;
        //      print_product_list();
        ui_basic_form_top("TOTAL SALES");
        //      print_product_list();
        printf("\n");

      print_list_product(phead,page_no_sales,element_column_product,arr_product,ABLE);
        get_product_sales_info(phead, &total_price);
      get_user_sales_info(uhead, &total_user);

        printf("TOTAL CLIENT IS %d, SINCE NOW TOTAL SALES IS %d", total_user, total_price);
        printf("\n");
        ui_basic_form_bottom();
        // printf("\n                               ★★ MENU ★★  \n 1 : PREV\n 2 : NEXT\n 0 : MYPAGE\n\n");
        printf("\n                               ★★ MENU ★★  \n 7 : MYPAGE\n\n");
      printf("-> SELECT MENU :");
        scanf("%c", &switch_value_sales);
        clean_stdin();
        system("clear");


        //  printf("\n   int ui_purchase()
        switch (switch_value_sales)
        {
      // case '1':
      //    printf("previous\n");
      //    page_no_sales--;
      //    if (page_no_sales  < 0)
      //       page_no_sales = 0;
      //    break;
      // case '2': //next
      //    printf("next\n");
      //    page_no_sales++;
      //    break;

      case '7':

         break;
      default:
            *switch_value = '0';
         printf("CHOOSE ALRIGHT MENU NUMBER!\n");
         break;
        }
        return 0;
}

int ui_stock_list(char *switch_value, int *user_role)
{
   int find_detail;
   char switch_value_stock;
   int page_no_stock = 0;
   char temp_stock[20];
   while (1)
   {

      if (switch_value_stock == '7')
      {
         system("clear");
         *switch_value = '7';
         break;
      }
      else if (switch_value_stock == '8')
      {
         system("clear");
         *switch_value = '8';
         break;
      }
      else if (switch_value_stock == '9')
      {
         system("clear");
         *switch_value = '9';
         break;
      }
      else if (switch_value_stock == '0')
      {
         *switch_value = '0';
         break;
      }
      ui_basic_form_top("MYPAGE_ADMIN_STOCKLIST");
      // print_list_product(element_stock, element_column_stock, arr_stock);
      print_list_stock(sthead,page_no_stock,element_column_stock,arr_stock);
    
      printf("\n                              ★★ MENU ★★\n 1 : SEARCH\n 2 : INSERT STOCK\n 3 : PREVIOUS\n 4 : NEXT\n 7 : MYPAGE\n 8 : MAIN\n 9 : LOGOUT\n 0 : EXIT\n\n");
      printf("-> SELECT MENU :");

      scanf("%c", &switch_value_stock);
      clean_stdin();
      switch (switch_value_stock)
      {
         case '1': // search
            stock_search(sthead,&sthead,&sttail,user_role,1);

            // ui_product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);
            break;
         case '2': // INSERT STOCK
            printf("INPUT PRODUCT INFO YOU WANT TO INSERT\n\n");

            insert_product(&phead, &ptail);
            insert_product_detail(ptail->product_id, &pdhash);
            increase_stock(&sthead, &sttail, ptail->model);
            break;
         case '3': //previous
            //set nouser role
            printf("previous\n");
            page_no_stock--;
            if(page_no_stock <0)
               page_no_stock= 0;
            break;
         case '4': //next
            printf("next\n");
            page_no_stock++;
            break;
         case '7':
         case '8':
         case '9':
         case '0':
            break;
         default:
            *switch_value = '0';
            printf("CHOOSE ALRIGHT MENU NUMBER!\n");
            break;
      }
      system("clear");
   }
   return 0;
}


int ui_user_list(char *switch_value, int *user_role)
{
        int find_detail;
        char switch_value_user;
        int page_no_user = 0;
        int search_switch = 0;
   while (1)
        {

                if (switch_value_user == '7')
                {
                        system("clear");
                        *switch_value = '7';
                        break;
                }
                else if (switch_value_user == '8')
                {
                        system("clear");
                        *switch_value = '8';
                        break;
                }
                else if (switch_value_user == '9')
                {
                        system("clear");
                        *switch_value = '9';
                        break;
                }
                else if (switch_value_user == '0')
                {
                        *switch_value = '0';
                        break;
                }
                ui_basic_form_top("MYPAGE_ADMIN_USERLIST");
               if(search_switch == 0 )
      print_list_user(uhead,page_no_user,element_column_user,arr_user);
      if(search_switch == 1)
                print_list_user(Suhead,page_no_user,element_column_user,arr_user);
                printf("\n                              ★★ MENU ★★\n 1 : SEARCH\n 2 : PREVIOUS LIST\n 3 : NEXT LIST\n 7 : MYPAGE\n 8 : MAIN\n 9 : LOGOUT\n 0 : EXIT\n\n");
                printf("-> SELECT MENU :");

                scanf("%c", &switch_value_user);
                clean_stdin();
                switch (switch_value_user)
                {
                        case '1': // search
                                user_search(uhead,&Suhead,&Sutail,user_role,1);
            search_switch = 1;
                                // ui_product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);
                                break;
            
/*           case '2': // INSERT STOCK
                                printf("INPUT PRODUCT YOU WANT TO INSERT : ");
                                scanf("%s",temp_stock);
                                clean_stdin();
                                increase_stock(&sthead,&sttail,temp_stock);// ui_sort
                                break;
                        case '3': // detail
                                printf("INPUT PRODUCT ID YOU WANT TO SEE : ");
                                scanf("%d",&find_detail);
                                system("clear");
                                err_code = find_product(phead, find_detail, &cur_product);
                                if (ERR_PRODUCT_OK != err_code) {
                                        printf("THERE's no PRODUCT\n");
                                        ui_main_window(switch_value, user_role);
                                }else{
                                        ui_product_detail(&switch_value_stock, user_role,find_detail);
                                }// ui_product_detail(PRODUCT *phead, PRODUCT_DETAIL *dhead, int product_id);
                                break;
                      
      */   case '2': //previous
                                //set nouser role
                                printf("previous\n");
                                page_no_user--;
                                if(page_no_user <0)
                                        page_no_user = 0;
                                break;
                        case '3': //next
                                printf("next\n");
                                page_no_user++;
                                break;
                        case '7':
                        case '8':
                        case '9':
                        case '0':
                                break;
                        default:
            *switch_value = '0';
                                printf("CHOOSE ALRIGHT MENU NUMBER!\n");
                                break;
                }
                system("clear");
        }
        return 0;
}


int ui_login_check(char *switch_value,int* user_role)
{
   char switch_value_login_check;

   ui_basic_form_top("LOGIN_CHECK");

   ui_basic_form_bottom();
   printf("\n\n");

   printf("INPUT ID -> INPUT PASSWORD\n");
   printf(" \n");
   ui_basic_form_bottom();
   printf("\n");
   int chk = login(uhead, &cur_user);
   
   if(chk) { //prev page로
      *switch_value = '1';
      return 0;
   }
   *user_role = cur_user->role;

   ui_basic_form_bottom();
   printf("\n");
   printf("PRESS ENTER ....");
   clean_stdin();
   system("clear");
   *switch_value = '2';
   return 0;
}
/*int ui_find_user(*switch_value){}
 *switch_value = '1';
 }*/

int ui_signup(char *switch_value,int* user_role)
{
   char switch_value_sign_up;

   ui_basic_form_top("SIGN UP");
   ui_basic_form_bottom();
   printf("\n");
   printf("\n");
   printf("INPUT NAME -> INPUT ID -> INPUT PASSOWRD -> INPUT ADDRESS -> INPUT PHONENUMBER\n");
   printf("\n");
   printf("\n");
   ui_basic_form_bottom();
   printf("\n");
   //회원가입 실행
   signup(&uhead,&utail);

   ui_basic_form_bottom();
   printf("\n");
   printf("press Enter ....");
   clean_stdin();
   system("clear");
   return 0;
   //   *switch_value = '2';
}

int ui_product_revice_user(char *switch_value, int *user_role)
{
   char switch_value_revice_user;
   while (1)
   {
      if (switch_value_revice_user == '7' && *user_role !=0)
      {
         system("clear");
         *switch_value = '7';
         break;
      }
      else if (switch_value_revice_user == '8')
      {
         system("clear");
         *switch_value = '8';
         break;
      }
      else if (switch_value_revice_user== '9')
      {
         system("clear");
         *switch_value = '9';
         break;
      }
      else if (switch_value_revice_user == '0')
      {
         system("clear");
         *switch_value = '0';
         break;
      }
      ui_basic_form_top("REVISGNG INFO");

      printf("\n YOUR NAME  : %c%c%c(%s)\n",*(cur_user->name),'*',*(cur_user->name+(strlen(cur_user->name)-1)),cur_user->user_id);


      ui_basic_form_bottom();

      printf("\n                           ★★ REVISING MENU ★★ \n");

      printf(" A) PASSWORD    : %s\n",cur_user->password);
      printf(" B) PHONENUMBER : %s\n",cur_user->phone);
      printf(" C) ADDRESS     : %s\n",cur_user->addr);
      printf("\n\n");







      ui_basic_form_bottom();
      printf("\n                              ★★ MENU ★★ \n 7 : MYPAGE\n 8 : MAIN\n 9 : LOGOUT\n 0 : EXIT\n\n");
      printf("-> SELECT MENU :");
      scanf("%c", &switch_value_revice_user);
      clean_stdin();
      char tempstr[20];
      switch (switch_value_revice_user)
      {
   /*      case 'A': //Name
            printf("\n NAME TO CHANGE\n");
            scanf("%s",&tempstr);
            clean_stdin();
            strcpy(cur_user->name, tempstr);
            //memset(Suhead->name, tempstr, strlen(tempstr) * sizeof(char));

            break;
   */      case 'A': //PASSWORD
            //scanf(%s,brand);
            printf(" PW TO CHANGE\n");
            scanf("%s",tempstr);
            clean_stdin();
            strcpy(cur_user->password, tempstr);
            break;
         case 'B': //Engine

            printf(" PHONENUM TO CHANGE\n");
            scanf("%s",tempstr);
            clean_stdin();
            strcpy(cur_user->addr, tempstr);
            //scanf(%s,engine);
            break;
         case 'C': //kind
            printf(" ADDR TO CHANGE\n");
            scanf("%s",tempstr);
            clean_stdin();
            strcpy(cur_user->phone, tempstr);
            // scanf(%s,kind);
            break;
         case '7':
         case '8':
         case '9':
         case '0':
            break;

      }
      system("clear");
   }   
   return 0;
}


int ui_basic_form_top(char *page_name)
{

   for (int i = 0; i < 5; i++) // 5 ? 반복. 바깥 ? 루프?   ?   ? 방향
   {
      for (int j = 0; j < 72; j++) // 5 ? 반복. ?   ? 루프?    ? ? 방향
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
            //  ? 출력
         }
      }
      printf("\n"); //  ? ? 방향?   ? 별을 ?   그린 ?   ?  ?   줄로 ?  ?   ?
   }
   return 0;
}


int ui_basic_form_bottom()
{
   for (int i = 0; i < 72; i++)
      printf("=");
   return 0;
}