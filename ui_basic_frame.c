#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int ui_basic_form_top();
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
int main(void)
{
    printf("let go");
/*
    USER current_user;

    PRODUCT *HEAD, *TAIL; // 파일로부터 불러온 모든 상품 리스트
    PRODUCT *SHEAD, *STAIL; // 모든 상품 리스트에서 검색한 상품들만 저장된 리스트
    PRODUCT_DETAIL *DETAIL_HEAD, *DETAIL_TAIL;
    USER *USER_HEAD, *USER_TAIL;
*/
    // load_func();
    // sava_func();

    char switch_value;
  //  int* page;
   // *switch_value = '1';
	printf("input\n");
   
	
scanf("%c",&switch_value);
getchar();
	while(1){
        switch(switch_value){

            case '1':
                printf("login window\n\n");
                ui_login(&switch_value);//
                break; //로그인 화면으로
            case '2':
                printf("main window\n\n");
                ui_main_window(&switch_value);
                break; //메인 화면으로
            case '3':
                printf("mypage window\n\n");
                ui_mypage(&switch_value);//마이페이지로
                break;//
            case '0':
        	printf("PROGRAM END");//프로그램 엔드
	        exit(0);
                break;//
            
        }

    }
    return 0;
}

int ui_login(char *switch_value){
    
    char switch_value_login; 
    ui_basic_form_top();
    printf("\n                              LOGIN\n\n");

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
printf("\n\n-> SELECT MENU :\n");
        scanf("%c", &switch_value_login);
	getchar();
        switch(switch_value_login){
            case '1':
            //로그인 확인으로 이동
            ui_login_check();
            printf("ui_login_check\n");
            *switch_value = '2';
            break;
            
            case '2':
            //로그인 찾기로 이동
            printf("ui_find_user\n");
            //ui_find_user(*switch_value);
            *switch_value = '1';
            break;
            
            case '3'://로그인 회원가이;ㅂ으로 이동
            ui_signup();
            printf("ui_signup\n");
            *switch_value = '2';
            break;
            
            case '4':
            //set nouser role을 비유저로 적용
            //ui_login_check(*switch_value);
           printf("login B user\n");
		*switch_value = '2';
            break;
		
	    default:
		printf("%c\n",switch_value_login);
		printf("%c\n",*switch_value);
		exit(0);
		break;


        }
    
}

int ui_main_window(char *switch_value){
    
    char switch_value_main; 
	while(1){
    ui_basic_form_top();

    ui_basic_form_bottom();

	if(switch_value_main == '7'){
            *switch_value = '3';//마이페이지로
            break;
        }
        else if(switch_value_main == '8'){
            *switch_value = '2';//메인
            break;
        }
        else if (switch_value_main == '9'){
            *switch_value = '1';//로그아웃
            break;
        }
        else if(switch_value_main == '0'){
            *switch_value = '0';//종료
            break;
        }
ui_basic_form_top();
     printf("welcome! sir WOW (LEVEL? ADMIN) \n                              MAIN\n\n");


    ui_basic_form_bottom();
printf("\n ID |   NAME   |    BRAND   |    ENGINE    |   KIND    |   PRICE  \n");
        printf("------------------------------------------------------------------\n");
        printf(" 01 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 02 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 03 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 04 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 05 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 06 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 07 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 08 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 09 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 10 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf("\n                                   1/10                           \n");

    ui_basic_form_bottom();
    printf("\n                              ★★ MENU ★★\n1:SEARCH\n2:SORT\n3:DETAIL\n4:PREVIOUS\n5:NEXT\n7:MYPAGE\n8:MAIN\n9:LOGOUT\n0:EXIT\n\n");
printf("-> SELECT MENU :");

        scanf("%c", &switch_value_main);

        getchar();
        switch(switch_value_main){
            case '1'://search
            //ui_product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);
            ui_product_search(&switch_value_main);//�뜝�럥�뿰�뼨轅명�ｉ뇡�쉻�삕�굢占� scanf
            break;
            case '2'://sort
            printf("sort window\n");
            //ui_sort
            break;
            case '3'://detail
            ui_product_detail(&switch_value_main);
            //ui_product_detail(PRODUCT *phead, PRODUCT_DETAIL *dhead, int product_id);
            break;
            case '4'://previous
            //set nouser role
            printf("previous\n");
            *switch_value = '2';
            break;
            case '5'://next
            printf("next\n");
            *switch_value = '2';
            break;
            
        }
    }
} 

int ui_mypage(char *switch_value){
    
    char switch_value_mypage; 
    
    while(1){
        ui_basic_form_top();
     printf("\n                              MYPAGE\n\n");
    ui_basic_form_bottom();
        printf("\n");
        printf("ID       : ABCD\n");
        printf("PASSWORD : ****\n");
        printf("NICKNAME : WOW \n");
        printf("REALNAME : WOW \n");

    ui_basic_form_bottom();
printf("\n                              ★★ Menu ★★\n1:REVISING INFO\n2:BUYING LIST\n3:BUCKET LIST\n4:MEMBER LIST\n5:SALES LIST\n6:STOCK LIST\n7:MYPAGE\n8:MAIN\n9:LOGOUT\n0:EXIT\n\n");
printf("-> Select Menu :");


    ui_basic_form_bottom();
	if(switch_value_mypage == '7'){
            *switch_value = '3';
            break;
        }
        else if(switch_value_mypage == '8'){
            *switch_value = '2';
            break;
        }
        else if (switch_value_mypage == '9'){
            *switch_value = '1';
            break;
        }
        else if(switch_value_mypage == '0'){
            *switch_value = '0';
            break;
        }
        printf("ui_mypage\n");
    scanf("%c", &switch_value_mypage);
        getchar();
        switch(switch_value_mypage){
            case '1'://revising info
            printf("revising info\n");
            //ui_product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail); ;
            break;
            case '2'://BUYING LIST
            //ui_order_list(ORDER *ohead, PRODUCT *phead);
            ui_order_list(switch_value);
            break;
            case '3'://STOCK LIST
            ui_stock_list(switch_value);
            break;
            case '4'://MEMBER LIST
            //ui_member_list()
            //set nouser role
            printf("MEMBERLIST\n");
            break;
            case '5'://SALES LIST
            printf("SALESLIST\n");
            //ui_sales_list() 
            break;
        }
    }
}

int ui_product_search(char *switch_value){
    
    char switch_value_search; 

    while(1){
    if(switch_value_search == '7'){
            *switch_value = '7';
            break;
        }
        else if(switch_value_search == '8'){
            *switch_value = '8';
            break;
        }
        else if (switch_value_search == '9'){
            *switch_value = '9';
            break;
        }
        else if(switch_value_search == '0'){
            *switch_value = '0';
            break;
        }

        ui_basic_form_top();
printf("\n                              SEARCH\n\n");
ui_basic_form_bottom();
printf("\n ID |   NAME   |    BRAND   |    ENGINE    |   KIND    |   PRICE  \n");
        printf("------------------------------------------------------------------\n");
        printf(" 01 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 02 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 03 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 04 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 05 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 06 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 07 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 08 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 09 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 10 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf("\n                                   1/10                           \n");

ui_basic_form_bottom();
        printf("\nA) Name : SONATA (ex: sonata)\n");
        printf("B) Brand : (ex: HYUNDAI)\n");
        printf("C) Engine : (ex: Digeal\n");
        printf("D) Kind : (ex: SUV)\n");
        printf("E) Price : (ex: 2000 4000)\n");
        printf("G) Search Start\n");
        printf("7) GO MAIN\n");
        printf("8) MyPage\n");
        printf("9) LOGOUT\n");
        printf("0) EXIT\n");
        printf("\n");

        printf("\n");

ui_basic_form_bottom();
printf("\n                       ★★ SEARCH MENU ★★\nA:NAME\nB:BRAND\nC:ENGINE\nD:FUEL\nE:PRICE\nF:GAS MILEGE\nG:SEARCH START\n\n");
printf("\n                              ★★ MENU ★★\n3:DETAILS\n4:PREVIOUS\n5:NEXT\n7:MYPAGE\n8:MAIN\n9:LOGOUT\n0:EXIT\n\n");
printf("-> Select Menu :");
    scanf("%c", &switch_value_search);
        getchar();
    switch(switch_value_search){

        case 'A'://Name
        printf("scanf A\n");
        //scanf(%s,name)
        break;
        case 'B'://Brand
        printf("scanf B\n");
        //scanf(%s,brand);
        break;
        case 'C'://Engine
        printf("scanf C\n");
        //scanf(%s,engine);
        break;
        case 'D'://kind
        printf("scanf D\n");
       // scanf(%s,kind);
        break;
        case 'E'://price
        printf("scanf E\n");
        printf("scanf E2\n");
      //  scanf(%d,lowprce);
      //  scanf(%d,highprice);
        break;
        case 'F'://GAS
        printf("scanf E\n");
        //  scanf(%d,lowprce);
      //  scanf(%d,highprice);
        break;
        case 'G'://search_start
        printf("scanf start\n");
     //   int product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);
        break;
        case '3'://detail
        ui_product_detail(&switch_value_search);
        break;
        case '4'://previous
        break;
        case '5'://next
        ui_product_detail(&switch_value_search);
        break;
        
    }
    }
}

int ui_product_detail(char *switch_value){
    
    char switch_value_detail; 
    ui_basic_form_top();
printf("\n                              DETAILS\n");


ui_basic_form_bottom();
     

        printf("\nName (ex: sonata)\n");
        printf("Brand  (ex: HYUNDAI)\n");
        printf("Engine  (ex: Digeal\n");
        printf("Kind  (ex: SUV)\n");
        printf("Price  (ex: $2000 $4000)\n");
        printf("DATE  (ex: 2022-02-26)\n");
        printf("ABLE PARTs \n");
        printf("ABLE COLOR \n");
        printf("COMMENTS \n");
        printf("SIZE \n");
        printf("Fuel efficiency \n");
        printf("\n");

ui_basic_form_bottom();
printf("\n                              ★★ Menu ★★\n1:APPLY PURCHASING\n7:MYPAGE\n8:MAIN\n9:LOGOUT\n0:EXIT\n\n");
printf("-> Select Menu :");

    while(1){
        
        if(switch_value_detail == '7'){
                *switch_value = '7';
                break;
            }
            else if(switch_value_detail == '8'){
                *switch_value = '8';
                break;
            }
            else if (switch_value_detail == '9'){
                *switch_value = '9';
                break;
            }
            else if(switch_value_detail == '0'){
                *switch_value = '0';
                break;
            }
            printf("ui_product_detail\n");
        //scanfswitch_value_login
        scanf("%c", &switch_value_detail);
        getchar();
        switch(switch_value_detail){
            case '1'://APPLY PURCHASING
            ui_purchase();
            break;
        }
    }
}
int ui_purchase(){
    
    char switch_value_purchase; 
    ui_basic_form_top();
      printf("\n                              PURCHASE\n\n");


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
        switch(switch_value_purchase){
            case '1'://PURCHASING
            //purchase(ORDER **ohead, ORDER **otail, PRODUCT *phead, int user_id, int product_id);
            printf("purchase\n");
            break;
            case '0'://exit
		printf("exit\n");
		break;
	}
}

int ui_order_list(char *switch_value){
    
    char switch_value_order; 


    while(1){

    
        if(switch_value_order == '7'){
            *switch_value = '3';
            break;
        }
        else if(switch_value_order == '8'){
            *switch_value = '2';
            break;
        }
        else if (switch_value_order == '9'){
            *switch_value = '1';
            break;
        }
        else if(switch_value_order == '0'){
            *switch_value = '0';
            break;
        }
ui_basic_form_top();
      printf("\n                              MYPAGE_ADMIN_STOCKLIST\n\n");

ui_basic_form_bottom();
        printf("\n ID |  NAME    |    BRAND   |    ENGINE    |   KIND    |   PRICE   |  STATE  \n");        printf("------------------------------------------------------------------\n");
        printf(" 01 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won   |  RELEASE\n");
        printf(" 02 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won   |  ORDER\n");
        printf(" 03 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won   |  APPLY\n");
        printf(" 04 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won  \n");
        printf(" 05 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 06 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 07 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 08 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 09 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 10 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf("\n                                   1/10                           \n");
ui_basic_form_bottom();


printf("\n                              ★★ MENU ★★\n1:SEARCH\n2:SORT\n3:DETAIL\n4:PREVIOUS\n5:NEXT\n7:MAIN\n8:MYPAGE\n9:LOGOUT\n0:EXIT\n\n");
printf("-> SELECT MENU :");

    //嶺뚮∥���占쎈��

    //scanfswitch_value_login
    
        scanf("%c", &switch_value_order);
	getchar();
        switch(switch_value_order){
            case '1'://search
            //ui_product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);
            ui_product_search(&switch_value_order);
           break;
            case '2'://sort
            printf("sort window\n");
            //ui_sort
            break;
            case '3'://detail
            ui_product_detail(&switch_value_order);
            //ui_product_detail(PRODUCT *phead, PRODUCT_DETAIL *dhead, int product_id);
            break;
            case '4'://previous
            //set nouser role
            printf("previous\n");
            *switch_value = '2';
            break;
            case '5'://next
            printf("next\n");
            *switch_value = '2';
            break;
            
        }
    }
}

int ui_stock_list(char *switch_value){
    
    char switch_value_stock; 

    while(1){
     ui_basic_form_top();
      printf("\n                              MYPAGE_ADMIN_STOCKLIST\n\n");

ui_basic_form_bottom();
        printf("\n ID |  NAME    |    BRAND   |    ENGINE    |   KIND    |   PRICE   |  STATE  \n");        printf("------------------------------------------------------------------\n");
        printf(" 01 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won   |  RELEASE\n");
        printf(" 02 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won   |  ORDER\n");
        printf(" 03 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won   |  APPLY\n");
        printf(" 04 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won  \n");
        printf(" 05 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 06 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 07 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 08 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 09 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf(" 10 |  sonata  |   HYUNDAI  |    DIGEAL    |    SUV    |  1000won \n");
        printf("\n                                   1/10                           \n");
ui_basic_form_bottom();

printf("\n                              ★★ MENU ★★\n1:SEARCH\n2:SORT\n3:DETAIL\n4:PREVIOUS\n5:NEXT\n7:MAIN\n8:MYPAGE\n9:LOGOUT\n0:EXIT\n\n");
printf("-> SELECT MENU :");
    
        if(switch_value_stock == '7'){
            *switch_value = '3';
            break;
        }
        else if(switch_value_stock == '8'){
            *switch_value = '2';
            break;
        }
        else if (switch_value_stock == '9'){
            *switch_value = '1';
            break;
        }
        else if(switch_value_stock == '0'){
            *switch_value = '0';
            break;
        }
    
        scanf("%c", &switch_value_stock);
	getchar();
        switch(switch_value_stock){
            case '1'://search
            //ui_product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);
            ui_product_search(&switch_value_stock);
           break;
            case '2'://sort
            printf("sort window\n");
            //ui_sort
            break;
            case '3'://detail
            ui_product_detail(&switch_value_stock);
            //ui_product_detail(PRODUCT *phead, PRODUCT_DETAIL *dhead, int product_id);
            break;
            case '4'://previous
           printf("previous\n");
            *switch_value = '2';
            break;
            case '5'://next
            printf("next\n");
            *switch_value = '2';
            break;
            
        }
    }
}


int ui_login_check(){

char switch_value_login_check;

        ui_basic_form_top();
      printf("\n                              LOGIN\n\n");


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
    
scanf("%c", &switch_value_login_check);
       getchar();
/*    switch(switch_value_login_check){

        case 'A'://Name
        printf("scanf A\n");
        //scanf(%s,name)
        break;
        case 'B'://Brand
        printf("scanf B\n");
        //scanf(%s,brand);
        break;
        case 'C'://Engine
        printf("scanf C\n");
        *switch_value = '2';
        //scanf(%s,engine);
        break;
        case '9':
        printf("GO BACK");
        *switch_value = '1';
        break;
        case '0':
        printf("exit");
        *switch_value = '0';
        break;

        }
  */  

    //*switch_value = '2';
}
/*int ui_find_user(*switch_value){}
    *switch_value = '1';
}*/
int ui_signup(){
char switch_value_sign_up;

        ui_basic_form_top();
      printf("\n                              SIGN_UP\n\n");


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
/*    scanf("%c", &switch_value_sign_up);
        getchar();
    switch(switch_value_sign_up){

        case 'A'://Name
        printf("scanf A\n");
        //scanf(%s,name)
        break;
        case 'B'://Brand
        printf("scanf B\n");
        //scanf(%s,brand);
        break;
        case 'C'://Engine
        printf("scanf C\n");
        *switch_value = '2';
        //scanf(%s,engine);
        break; case 'A'://Name
        printf("scanf A\n");
        //scanf(%s,name)
        break;
        case 'D'://Brand
        printf("scanf B\n");
        //scanf(%s,brand);
        break;
        case 'E'://Engine
        printf("scanf C\n");
        *switch_value = '2';
        //scanf(%s,engine);
        break; case 'A'://Name
        printf("scanf A\n");
        //scanf(%s,name)
        break;
        case 'G'://Brand
        printf("scanf B\n");
        *switch_value = '2';
        break;
        case '9':
        printf("GO BACK");
        *switch_value = '1';
        break;
        case '0':
        printf("exit");
        *switch_value = '0';
        break;

        }
    
*/
 //   *switch_value = '2';
}

int ui_basic_form_top(){
    for (int i = 0; i < 5; i++)    // 5번 반복. 바깥쪽 루프는 세로 방향
    {
        for (int j = 0; j < 66; j++)    // 5번 반복. 안쪽 루프는 가로 방향
        {   if(i==0 || i ==4)
            printf("-");
            else{

            if(j==0 || j==65)
            printf("*");
            else
            printf(" ");
                // 별 출력

            }

        }
        printf("\n");              // 가로 방향으로 별을 다 그린 뒤 다음 줄로 넘어감
    }

}
int ui_basic_form_bottom(){
    for(int i = 0; i< 66;i++)
        printf("=");

}


