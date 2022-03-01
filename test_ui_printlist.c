#include<stdio.h>
#include <string.h>
#include <math.h>
#include "ui_printlist.h"
#include "ui_printlist_ex.h"

int main(){
printf("\nproduct\n");
print_list_product(element_product,element_column_product,arr);
printf("\nuser\n");
print_list_product(element_user,element_column_user,arr_user);
printf("\nstock\n");
print_list_product(element_stock,element_column_stock,arr_stock);
printf("\norder\n");
print_list_product(element_order,element_column_order,arr_order);
printf("\ndetail\n");
print_list_product(element_detail,element_column_detail,arr_detail);

}
