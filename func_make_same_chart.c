#include<stdio.h>
#include <string.h>
#include <math.h>
int ui_basic_form_bottom();
int print_space_bar(int num);
int set_column_size(int arr[],int chart_length,int arr_size,char element[][6][10],int element_size,int page_no);

int main(){
        char element[3][6][10]={
        {"01","SONATA","HYUNDAI","DIGEAL","SUV","1000won"},
        {"02","LAY","KIA","EV","SMALL","2000WON"},
        {"03","G80","GENESIS","HYBRID","MIDDLESUV","10000WON"}
        };
        int arr[] = {3,10,12,13,11,10};
        int page_no = 0;
        int chart_length = 66;
        int element_size = 0;
        int arr_size = 6;

        ui_basic_form_bottom();

        set_column_size(arr,chart_length,arr_size,element,element_size,page_no);

        printf("\n                                   1/10                           \n");
        ui_basic_form_bottom();



}
int set_column_size(int arr[],int chart_length,int arr_size,char element[][6][10],int element_size,int page_no){

        for(int i = page_no*10; i< page_no*10 +3; i++){
                printf("|");
                for(int j = 0; j< arr_size; j++){
                        int item_size = strlen(element[i][j]);//의사이즈 까지
                        print_space_bar((arr[j] - item_size+1)/2);
                        printf("%s",element[i][j]);
                        print_space_bar(arr[j] - ((arr[j] - item_size+1)/2) - item_size);
                        printf("|");
                }
                printf("\n");
        }
}

int print_space_bar(int num){
        for(int i = 0; i<num; i++){
                printf(" ");

}
}

int ui_basic_form_bottom(){
    for(int i = 0; i< 66;i++)
        printf("=");
    printf("\n");
}


