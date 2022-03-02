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

int ui_basic_form_top(char *page_name);
int ui_basic_form_bottom();
int ui_basic_form_up();

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



int err_code;

USER cur_user;

USER *uhead, *utail;    /* 사용자 연결 리스트 */
PRODUCT *phead, *ptail; /* 상품 연결 리스트 */
PRODUCT *Sphead, *Sptail; /* 상품 검색  리스트 */
STOCK *sthead, *sttail;   /* 재고 연결 리스트 */

LPHASH pdhash; /* 상품 상세설명 해시 */
PRODUCT_DETAIL *cur_product_detail;


int main(void)
{
	char switch_value; // 메뉴 번호
	int user_role;    
	/* 변수 초기화 */
	uhead = utail = NULL;
	phead = ptail = NULL;
	sthead = sttail = NULL;
	Sphead = Sptail = NULL;
	err_code = hashCreate(&pdhash);
	if (ERR_HASH_OK != err_code)
	{
		return 0;
	}

	/* 구조체 데이터 로드 */
	load_product(&phead, &ptail, PRODUCT_FILE);
	load_product_detail(&pdhash, PRODUCT_DETAIL_FILE);

	// 파일로부터 데이터 로드 후 결과 출력
	//	print_list_product(phead,1,element_column_product,arr_product); // phead, page_no
	//	print_list_product(phead,0,element_column_product,arr_product); // phead, page_no
	//	print_product_detail_list(pdhash);

	// [start] 필요한 만큼 데이터 입력이 끝나시면, start~end 블럭 지워주시면 됩니다!

	// loop 만큼 상품과 상세정보를 입력합니다.
	/*	for(int i=0; i<2; i++) {
		insert_product(&phead, &ptail);
		insert_product_detail(ptail->product_id, &pdhash);
		}
	 */
	// 상품과 상세정보 추가 후 결과
	//	print_product_list(phead, 0); // phead, page_no
	print_product_detail_list(pdhash);

	// 0) EXIT 메뉴를 통해 프로그램을 정상종료 할 경우 입력했던 상품 목록들이 파일에 저장됩니다.

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
				printf("-- PROGRAM END --"); //프로그램 엔드

				/* 구조체 데이터 저장 */
				save_product(phead, PRODUCT_FILE);
				save_product_detail(pdhash, PRODUCT_DETAIL_FILE);

				exit(0);
				break;
			default:
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
	printf("                                |                               \n");
	printf("         1.LOGIN                |                               \n");
	printf("         2.FINDIDPW             |        4.NONUSER              \n");
	printf("         3.REGISTER             |        5.ROOT                 \n");
	printf("                                |                               \n");
	printf("                                |                               \n");
	ui_basic_form_bottom();
	printf("\n                            ★★ MENU ★★\n 1 : LOGIN\n 2 : FINDIDPW\n 3 : REGISTER\n 4 : NONUSER\n 5 : ROOT\n 0 : EXIT");
	printf("\n\n-> SELECT MENU :");
	scanf("%c", &switch_value_login);
	getchar();
	system("clear");    
	switch (switch_value_login)
	{
		case '1':
			//로그인 확인으로 이동
			ui_login_check(switch_value, user_role);
			//*switch_value = '2';
			break;

		case '2':
			//로그인 찾기로 이동
			printf("ui_find_user\n");
			//ui_find_user(*switch_value);
			*switch_value = '1';
			break;

		case '3': //로그인 회원가이;ㅂ으로 이동
			ui_signup(switch_value, user_role);
			printf("ui_signup\n");
			break;

		case '4':
			//set nouser role을 비유저로 적용
			//ui_login_check(*switch_value);
			*user_role =0;
			printf("login B user\n");
			*switch_value = '2';
			break;
		case '5':
			// set nouser role을 비유저로 적용
			system("clear");
			// ui_login_check(*switch_value);
			*user_role = 2;
			printf("login B user\n");
			*switch_value = '2';
			break;
		case '0':
			*switch_value ='0';
			break;
		default:
			printf("CHOOSE ALRIGHT MENU NUMBER!\n");
			*switch_value = '1';
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
		print_list_product(phead,page_no_main,element_column_product,arr_product); // phead, page_no
		if(*user_role !=0){
			printf("                              ★★ MENU ★★\n 1 : SEARCH\n 2 : SORT\n 3 : DETAIL\n 4 : PREVIOUS\n 5 : NEXT\n 7 : MYPAGE \n 8 : MAIN \n 9 : LOGOUT \n 0 : EXIT\n\n");

			printf("-> SELECT MENU :");

			scanf("%c", &switch_value_main);

			getchar();
			switch (switch_value_main)
			{
				case '1': //search
					//ui_product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);
					ui_product_search(&switch_value_main, user_role); //�뜝�럥�뿰�뼨轅명�ｉ뇡�쉻�삕�굢占� scanf
					break;
				case '2': //sort
					printf("sort window\n");
					//ui_sort
					break;
				case '3': //detail
					printf("INPUT PRODUCT ID YOU WANT TO SEE : ");
					scanf("%d",&find_detail);
					getchar();
					system("clear");
					ui_product_detail(&switch_value_main, user_role,find_detail);
					//ui_product_detail(PRODUCT *phead, PRODUCT_DETAIL *dhead, int product_id);
					break;
				case '4': //previous
					//set nouser role
					printf("previous\n");
					page_no_main--;
					if(page_no_main <0)
						page_no_main = 0;
					*switch_value = '2';
					break;
				case '5': //next
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
					printf("CHOOSE ALRIGHT MENU NUMBER!\n");
					break;
			}
		system("clear");
		}else{
			printf("                              ★★ MENU ★★\n 1 : SEARCH\n 2 : SORT\n 3 : DETAIL\n 4 : PREVIOUS\n 5 : NEXT\n 8 : LOGIN\n 9 : MAIN\n 0 : EXIT\n\n");
			printf("-> SELECT MENU :");

			scanf("%c", &switch_value_main);

			getchar();
			switch (switch_value_main)
			{
				case '1': // search
					// ui_product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);
					ui_product_search(&switch_value_main,user_role); //�뜝�럥�뿰�뼨轅명�ｉ뇡�쉻�삕�굢占� scanf
					break;
				case '2': // sort
					printf("sort window\n");
					// ui_sort
					break;
				case '3': // detail
					printf("INPUT PRODUCT ID YOU WANT TO SEE : ");
					scanf("%d",&find_detail);
					getchar();
					ui_product_detail(&switch_value_main,user_role,find_detail);
					// ui_product_detail(PRODUCT *phead, PRODUCT_DETAIL *dhead, int product_id);
					break;
				case '4': //previous
					//set nouser role
					printf("previous\n");
					page_no_main--;
					if(page_no_main <0)
						page_no_main = 0;
					*switch_value = '2';
					break;
				case '5': //next
					printf("next\n");
					page_no_main++;
					*switch_value = '2';

				case '8': ///change to 9
					switch_value_main = '9';
					break;
				case '9': ///change to 8
					switch_value_main = '8';
					break;
				case '0':
					break;
				default:
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
		printf("ID       : ABCD\n");
		printf("PASSWORD : ****\n");
		printf("NICKNAME : WOW \n");
		printf("REALNAME : WOW \n");

		ui_basic_form_bottom();
		if(*user_role !=2){
			printf("\n                              ★★ MENU ★★\n 1 : REVISING INFO\n 2 : BUYING LIST\n 3 : BUCKET LIST\n 7 : MYPAGE\n 8 : MAIN\n 9 : LOGOUT\n 0 : EXIT\n\n");
			printf("-> SELECT MENU :");
			scanf("%c", &switch_value_mypage,user_role);
			getchar();
			system("clear");
			switch (switch_value_mypage)
			{
				case '1': // revising info
					printf("revising info\n");
					// ui_product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail); ;
					break;
				case '2': // BUYING LIST
					// ui_order_list(ORDER *ohead, PRODUCT *phead);
					ui_order_list(switch_value,user_role);
					break;
				case '3': // BUCKET LIST
					printf("wish listn");
					//ui_stock_list(switch_value);
					break;
				case '7':
				case '8':
				case '9':
				case '0':
					break;
				default:
					printf("CHOOSE ALRIGHT MENU NUMBER!\n");
					break;

			}
		}else{
			printf("\n                              ★★ MENU ★★\n 1 : REVISING INFO\n 2 : BUYING LIST\n 3 : BUCKET LIST\n 4 : MEMBER LIST\n 5 : SALES LIST\n 6 : STOCK LIST\n 7 : MYPAGE\n 8 : MAIN\n 9 : LOGOUT\n 0 : EXIT\n\n");
			printf("-> SELECT MENU :");
			scanf("%c", &switch_value_mypage);
			getchar();
			system("clear");
			switch (switch_value_mypage)
			{
				case '1': // revising info
					printf("revising info\n");
					// ui_product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail); ;
					break;
				case '2': // BUYING LIST
					// ui_order_list(ORDER *ohead, PRODUCT *phead);
					ui_order_list(switch_value,user_role);
					break;
				case '3': // STOCK LIST
					printf("wish list");
					break;
				case '4': // MEMBER LIST
					// ui_member_list()
					// set nouser role
					printf("MEMBERLIST\n");
					break;
				case '5': // SALES LIST
					printf("SALESLIST\n");
					// ui_sales_list()
					break;
				case '6': // STOCK LIST
					ui_stock_list(switch_value,user_role);
					break;
				case '7':
				case '8':
				case '9':
				case '0':
					break;
				default:        
					printf("CHOOSE ALRIGHT MENU NUMBER!\n");
					break;
			}
		}
	}
	return 0;
}

int ui_product_search(char *switch_value, int *user_role)
{

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

			print_list_product(NULL,page_no_search,element_column_product,arr_product); // phead, page_no

			printf("                           ★★ SEARCH MENU ★★\n");
			printf(" A) MODEL : \n");
			printf(" B) OEM : \n");
			printf(" C) GAS_MILLEGE:  \n");
			printf(" D) FUEL : \n");
			printf(" E) PRICE : \n");

		}else if(Sphead==NULL){

			print_list_product(phead,page_no_search,element_column_product,arr_product); // phead, page_no

			printf("                           ★★ SEARCH MENU ★★\n");
			printf(" A) MODEL : \n");
			printf(" B) OEM : \n");
			printf(" C) GAS_MILLEGE :  \n");
			printf(" D) FUEL : \n");
			printf(" E) PRICE :\n");

		}else{
			print_list_product(Sphead,page_no_search,element_column_product,arr_product); // phead, page_no

			printf("                           ★★ SEARCH MENU ★★\n");
			if(switch_value_search== 'A')
				printf(" A) MODEL : %s\n",Sphead->model);
			else

				printf(" A) MODEL : \n");
			if(switch_value_search== 'B')
				printf(" B) OEM : %d\n",Sphead->oem);
			else
				printf(" B) OEM : \n");
			if(switch_value_search== 'C')
				printf(" C) GAS_MILLEGE :  %2.2f\n",Sphead->gas_mileage);
			else
				printf(" C) GAS_MILLEGE :  \n");
			if(switch_value_search== 'D')
				printf(" D) FUEL : %d\n",Sphead->fuel);
			else
				printf(" D) FUEL : \n");

			if(switch_value_search== 'E')
				printf(" E) PRICE : %d - %d\n",Sphead->price-10,Sphead->price +10);
			else
				printf(" E) PRICE :\n");

		}

		printf("\n\n");

		ui_basic_form_bottom();
		if(*user_role != 0 ){
			printf("\n                              ★★ MENU ★★\n 1 : RESET\n 3 : DETAILS\n 4 : PREVIOUS\n 5 : NEXT\n 7 : MYPAGE\n 8 : MAIN\n 9 : LOGOUT\n 0 : EXIT\n\n");
			printf("-> SELECT MENU :");
			scanf("%c", &switch_value_search);
			getchar();

			switch (switch_value_search)
			{

				case 'A': //Name
					start_search =1;
					product_search(phead,&Sphead,&Sptail,user_role,1);
					//scanf(%s,name)
					break;
				case 'B': //Brand
					//scanf(%s,brand);
					start_search =1;
					product_search(phead,&Sphead,&Sptail,user_role,2);
					break;
				case 'C': //Engine
					start_search =1;
					product_search(phead,&Sphead,&Sptail,user_role,5);
					//scanf(%s,engine);
					break;
				case 'D': //kind
					product_search(phead,&Sphead,&Sptail,user_role,4);
					start_search =1;
					// scanf(%s,kind);
					break;
				case 'E': //price
					start_search =1;
					product_search(phead,&Sphead,&Sptail,user_role,3);
					//  scanf(%d,lowprce);
					//  scanf(%d,highprice);
					break;
				case '1': //reset
					start_search =0;
					break;
				case '3': //detail
					printf("INPUT PRODUCT ID YOU WANT TO SEE : ");
					scanf("%d",&find_detail);	
					getchar();
					ui_product_detail(&switch_value_search, user_role,find_detail);
					break;
				case '4': //previous
					//set nouser role
					printf("previous\n");
					page_no_search--;
					if(page_no_search <0)
						page_no_search = 0;
					break;
				case '5': //next
					printf("next\n");
					page_no_search++;
				case '7':
				case '8':
				case '9':
				case '0':
					break;
				default:
					printf("CHOOSE ALRIGHT MENU NUMBER!\n");
					break;
			}
			system("clear");

		}else{
			printf("\n                              ★★ MENU ★★\n 3 : DETAILS\n 4 : PREVIOUS\n 5 : NEXT\n 9 : MAIN\n 0 : EXIT\n\n");
			printf("-> SELECT MENU :");
			scanf("%c", &switch_value_search);
			getchar();
			switch (switch_value_search)
			{

				case 'A': // Name
					printf("scanf A\n");
					// scanf(%s,name)
					break;
				case 'B': // Brand
					printf("scanf B\n");
					// scanf(%s,brand);
					break;
				case 'C': // Engine
					printf("scanf C\n");
					// scanf(%s,engine);
					break;
				case 'D': // kind
					printf("scanf D\n");
					// scanf(%s,kind);
					break;
				case 'E': // price
					printf("scanf E\n");
					printf("scanf E2\n");
					//  scanf(%d,lowprce);
					//  scanf(%d,highprice);
					break;
				case 'F': // GAS
					printf("scanf E\n");
					//  scanf(%d,lowprce);
					//  scanf(%d,highprice);
					break;
				case 'G': // search_start
					printf("scanf start\n");
					//   int product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);
					break;
				case '3': // detail
					printf("INPUT PRODUCT ID YOU WANT TO SEE : ");
					scanf("%d",&find_detail);
					getchar();
					ui_product_detail(&switch_value_search,user_role,find_detail);
					break;
				case '4': // previous
					break;
				case '5': // next
					//ui_product_detail(&switch_value_search,user_role);
					break;
				case '9':
					switch_value_search = '8';
					break;
				case '0':
					break;
				default:
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
		product_search_ID(phead,&Sphead,&Sptail,find_detail);
		print_product_list_in_detail(Sphead);	
		find_product_detail(pdhash,0,&cur_product_detail);
		ui_basic_form_bottom();
		if(*user_role != 0){
			printf("\n                              ★★ MENU ★★\n 1 : APPLY PURCHASING\n 7 : MYPAGE\n 8 : MAIN\n 9 : LOGOUT\n 0 : EXIT\n\n");
			printf("-> SELECT MENU :");
			scanf("%c",&switch_value_detail);
			getchar();
			system("clear");
			switch (switch_value_detail)
			{
				case '1': // APPLY PURCHASING
					ui_purchase();
					break;
				case '7':
				case '8':
				case '9':
				case '0':
					break;
				default:
					printf("%c",switch_value_detail);
					printf("CHOOSE ALRIGHT MENU NUMBER!\n");
					break;
			}
		}else{
			printf("                              ★★ MENU ★★\n 1 : APPLY PURCHASING\n 8 : LOGIN \n 9 : MAIN\n 0 : EXIT\n\n");
			printf("-> SELECT MENU :");
			scanf("%c", &switch_value_detail);
			getchar();
			system("clear");
			switch (switch_value_detail)
			{
				case '1': // APPLY PURCHASING
					ui_purchase();
					break;
				case '8':
					switch_value_detail = '9';
					break;
				case '9':
					switch_value_detail = '8';
					break;
				case '0':
					break;
				default:
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
	printf("\n A) YOUR ID : (ex: HELOO123)\n");
	printf(" B) PHONENUMBER: (ex: 010123456)\n");
	printf(" C) ADDRESS : (ex: SUWON HOMAESIL)\n");
	printf("\n");
	ui_basic_form_bottom();
	printf("                                        ★★ APPLYING CONSULTING MENU ★★\n A) YOUR ID : (ex: HELOO123)\n");
	printf(" B) PHONENUMBER:  (ex: 010123456)\n");
	printf(" C) ADDRESS : (ex: SUWON HOMAESIL)\n");
	printf("\n");
	printf("\n                              ★★ MENU ★★\n 1 : PURCHASING\n 0 : EXIT\n\n");
	printf("-> SELECT MENU :");

	scanf("%c", &switch_value_purchase);
	getchar();
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
			// purchase(ORDER **ohead, ORDER **otail, PRODUCT *phead, int user_id, int product_id);
			printf("purchase\n");
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

		//print_list_product(element_order, element_column_order, arr_order);

		printf("\n                              ★★ MENU ★★\n 1 : SEARCH\n 2 : SORT\n 3 : DETAIL\n 4 : PREVIOUS\n 5 : NEXT\n 7 : MYPAGE\n 8 : MAIN\n 9 : LOGOUT\n 0 : EXIT\n\n");
		printf("-> SELECT MENU :");
		//嶺뚮∥���占쎈��

		//scanfswitch_value_login

		scanf("%c", &switch_value_order);
		getchar();
		switch (switch_value_order)
		{
			case '1': // search
				// ui_product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);
				ui_product_search(&switch_value_order,user_role);
				break;
			case '2': // sort
				printf("sort window\n");
				// ui_sort
				break;
			case '3': // detail
				printf("INPUT PRODUCT ID YOU WANT TO SEE : ");
				scanf("%d",&find_detail);
				ui_product_detail(&switch_value_order,user_role,find_detail);
				// ui_product_detail(PRODUCT *phead, PRODUCT_DETAIL *dhead, int product_id);
				break;
			case '4': // previous
				// set nouser role
				printf("previous\n");
				//*switch_value = '2';
				break;
			case '5': // next
				printf("next\n");
				//*switch_value = '2';
				break;
			case '7':
			case '8':
			case '9':
			case '0':
				break;
			default:
				printf("CHOOSE ALRIGHT MENU NUMBER!\n");
				break;
		}
		system("clear");
	}
	return 0;
}

int ui_stock_list(char *switch_value, int *user_role)
{
	int find_detail;
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
		// print_list_product(element_stock, element_column_stock, arr_stock);


		printf("\n                              ★★ MENU ★★\n 1 : SEARCH\n 2 : SORT\n 3 : DETAIL\n 4 : PREVIOUS\n 5 : NEXT\n 7 : MYPAGE\n 8 : MAIN\n 9 : LOGOUT\n 0 : EXIT\n\n");
		printf("-> SELECT MENU :");

		scanf("%c", &switch_value_stock);
		getchar();
		switch (switch_value_stock)
		{
			case '1': // search
				// ui_product_search(PRODUCT *phead, PRODUCT **shead, PRODUCT **stail);
				ui_product_search(&switch_value_stock,user_role);
				break;
			case '2': // sort
				printf("sort window\n");
				// ui_sort
				break;
			case '3': // detail
				printf("INPUT PRODUCT ID YOU WANT TO SEE : ");
				scanf("%d",&find_detail);
				ui_product_detail(&switch_value_stock,user_role,find_detail);
				// ui_product_detail(PRODUCT *phead, PRODUCT_DETAIL *dhead, int product_id);
				break;
			case '4': // previous
				printf("previous\n");
				//*switch_value = '2';
				break;
			case '5': // next
				printf("next\n");
				//*switch_value = '2';
				break;
			case '7':
			case '8':
			case '9':
			case '0':
				break;
			default:
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
	//      printf("\n                              LOGIN\n\n");

	ui_basic_form_bottom();
	printf("\n");
	printf("\n A) YOUR ID : (ex:HELLO123)\n");
	printf(" B) YOUR PW : (ex: 32654ZX)\n");
	printf(" C) LOGIN : \n");
	printf(" 9) GO BACK : \n");
	printf(" 0) EXIT: \n");
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

		case 'A': // Name
			printf("scanf A\n");
			// scanf(%s,name)
			break;
		case 'B': // Brand
			printf("scanf B\n");
			// scanf(%s,brand);
			break;
		case 'C': // Engine
			printf("scanf C\n");
			*user_role = 1;
			*switch_value = '2';
			// scanf(%s,engine);
			break;
		case '9':
			printf("GO BACK\n");
			*user_role = 0;
			*switch_value = '1';
			break;
		default:
			printf("exit\n");
			*switch_value = '1';
			break;
	}
	system("clear");
	//*switch_value = '2';
	return 0;
}
/*int ui_find_user(*switch_value){}
 *switch_value = '1';
 }*/

int ui_signup(char *switch_value,int* user_role)
{
	char switch_value_sign_up;

	ui_basic_form_top("SIGN UP");
	//      printf("\n                              SIGN_UP\n\n");

	//signup(USER_HEAD,USER_TAIL);
	ui_basic_form_bottom();
	printf("\n");
	printf("\n A) YOUR ID : (ex: HELLO1234)\n");
	printf(" B) YOUR PW : (ex: 123456)\n");
	printf(" C) CHECK PW : (ex: 123456\n");
	printf(" D) PHONENUMBER: (ex: 01012345678)\n");
	printf(" E) ADDR : (ex: SUWON HOMAESIL)\n");
	printf(" G) REGISTER\n");
	printf(" 9) GO LOGIN STATE\n");
	printf(" 0) EXIT\n");
	/* printf("E) NICKNAME : (ex: 2000 4000\n");
	   printf("F) REALNAME : (ex: 2000 4000\n");
	   printf("G) WHAT IS YOUR FIRST SCHOOL NAME: (ex:hyocheon)\n");*/

	ui_basic_form_bottom();
	scanf("%c", &switch_value_sign_up);
	getchar();
	printf("-> SELECT MENU :");
	switch (switch_value_sign_up)
	{
		case 'A': // Name
			printf("scanf A\n");
			// scanf(%s,name)
			break;
		case 'B': // Brand
			printf("scanf B\n");
			// scanf(%s,brand);
			break;
		case 'C': // Engine
			printf("scanf C\n");
			// scanf(%s,engine);
			break; // Name
		case 'D':  // Brand
			printf("scanf B\n");
			// scanf(%s,brand);
			break;
		case 'E': // Engine
			printf("scanf C\n");
			// scanf(%s,engine);
			break; // Name
		case 'G': // Brand
			printf("scanf B\n");
			*user_role = '1';
			*switch_value = '2';
			break;
		case '9':
			printf("GO BACK\n");
			*user_role = '0';
			*switch_value = '1';
			break;
		default:
			printf("exit\n");
			*switch_value = '0';
			break;
	}
	system("clear");
	return 0;
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


