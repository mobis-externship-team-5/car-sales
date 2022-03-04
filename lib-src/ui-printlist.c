#include "math.h"
#include <stdio.h>
#include <string.h>
#include "ui-printlist.h"
//int print_list_product(char element[][6][20],char element_column[][6][20],int arr[6]){
	


/*int print_list_7(char element[][7][20],char element_column[][7][20],int arr[7]){

        int page_no = 0;
        int chart_length = 66;
        int element_size = 0;
        int arr_size = 7;

        ui_printlist_printline('=');
        set_column_size(arr,chart_length,arr_size,element_column,1,page_no);
        ui_printlist_printline('-');
        set_column_size(arr,chart_length,arr_size,element,3,page_no);
        ui_printlist_printline('-');
        printf("\n                                   %d/10                           \n",page_no+1);
        ui_printlist_printline('=');



}
*/

int printspace_string(char* element,int arr_num){
	int item_size = strlen(element);//의사이즈 까지
        ui_printlist_space_bar(arr_num - item_size -1);
	printf("%s",element);
	if(item_size<arr_num)
        printf(" ");
	if(item_size != 0 || arr_num == 6)
        printf("|");
        else
        printf(" ");

        return 0;
}

int printspace_int(int element,int arr_num){
	
	char s1[20];
        sprintf(s1, "%d",element);
        int item_size = strlen(s1);
	ui_printlist_space_bar(arr_num - item_size -1);
	printf("%d",element);
        if(item_size<arr_num)
        printf(" ");
        if(item_size != 0 || arr_num == 6)
        printf("|");
        else
        printf(" ");

        return 0;
}

int printspace_double(double element,int arr_num){
	char s1[20];
	sprintf(s1, "%.2f",element );
        int item_size = strlen(s1);
	ui_printlist_space_bar(arr_num- item_size -1);
	printf("%2.2f",element);
        if(item_size<arr_num)
        printf(" ");
        if(item_size != 0 || arr_num == 6)
	printf("|");
        else
        printf(" ");

        return 0;
}

int set_column_size(int arr[],int chart_length,int arr_size,char element[][6][20],int element_size,int page_no){

	for(int i = page_no*10; i< page_no*10 +1; i++){

		printf("|");
		for(int j = 0; j< arr_size; j++){
			int item_size = strlen(element[i][j]);//의사이즈 까지
			ui_printlist_space_bar(arr[j] - item_size -1);
			printf("%s",element[i][j]);
			if(item_size<arr[j])
			printf(" ");
			if(item_size != 0 || j == arr_size)	
			printf("|");
			else
			printf(" ");
		}	
		printf("\n");
	}

        return 0;
}
/*int set_column_size7(int arr[],int chart_length,int arr_size,char element[][7][20],int element_size,int page_no){




        for(int i = page_no*10; i< page_no*10 +element_size; i++){
                printf("|");
                for(int j = 0; j< arr_size; j++){
                        int item_size = strlen(element[i][j]);//의사이즈 까지
                        ui_printlist_space_bar((arr[j] - item_size+1)/2);
                        printf("%s",element[i][j]);
                        ui_printlist_space_bar(arr[j] - ((arr[j] - item_size+1)/2) - item_size);
                        printf("|");
                }
                printf("\n");
        }
}
*/
int ui_printlist_space_bar(int num){
	for(int i = 0; i<num; i++){
		printf(" ");

	}

        return 0;
}

int ui_printlist_printroof(char garo,char sero){
    for (int i = 0; i < 5; i++)    // 5번 반복. 바깥쪽 루프는 세로 방향
    {
        for (int j = 0; j < 72; j++)    // 5번 반복. 안쪽 루프는 가로 방향
        {   if(i==0 || i ==4)
            printf("%c",garo);
            else{

            if(j==0 || j==71)
            printf("%c",sero);
            else
            printf(" ");
                // 별 출력

            }

        }
        printf("\n");              // 가로 방향으로 별을 다 그린 뒤 다음 줄로 넘어감
    }
        return 0;
}

int ui_printlist_printline(char a){
    for(int i = 0; i< 72;i++)
        printf("%c",a);
    printf("\n");

    return 0;
}

