#ifndef UI_PRINTLIST_H
#define UI_PRINTLIST_H
int ui_printlist_printline(char a);
int ui_printlist_printroot(char garo,char sero);
int ui_printlist_space_bar(int num);
int printspace_string(char* element,int arr_num);
int printspace_int(int element,int arr_num);
int printspace_double(double element,int arr_num);

int set_column_size(int arr[],int chart_length,int arr_size,char element[][6][20],int element_size,int page_no);
//int set_column_size_7(int arr[],int chart_length,int arr_size,char element[][7][20],int element_size,int page_no);


//int print_list_7(char element[][7][20],char element_column[][7][20],int arr[]);
#endif 
