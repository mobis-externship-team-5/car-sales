	char element_product[3][6][20]={
        {"111111","SONATA 2020","HYUNDAI","22.8","DIGEAL","1000won"},
        {"222222","LAY 2121","KIA","22.4","EV","2000WON"},
        {"3333333","G80 2020","GENESIS","22,1","HYBRID","10000WON"}
	};
        char element_column_product[1][6][20]={
        {"ID","MODEL","OEM","GAS_MILLEGE","FUEL","PRICE"}
	};
        int arr_product[] = {5,17,11,12,10,10}; // 65

	
	char element_user[3][6][20]={
        {"1234","SONATA","H3YUNDAI","DIGEAL","SUV","10n"},
        {"23422","LAY","K3IA","333EV","1012345665","200"},
        {"23","G830","G33ENESIS","asdfqwerq","1012345678","0WON"}
        };
	char element_column_user[1][6][20]={
        {"USER_ID","NAME","PASSWORD","ADDR","PHONE","ROLE"}
        };	
        int arr_user[] = {10,9,11,18,12,5};
	

	char element_stock[3][6][20]={
        {"SONATA","10n","","","",""},
        {"LAY","200","","","",""},
        {"G80","30","","","",""}
        };
        char element_column_stock[1][6][20]={
        {"MODEL","QUANTITY","","","",""}
        };
        int arr_stock[] = {35,34,0,0,0,0};
	
	char element_order[3][6][20]={
        {"1234","SONATA","H3YUNDAI","DIGEAL","",""},
        {"23422","LAY","K3IA","333EV","",""},
        {"23","G830","G33ENESIS","asdfqwerq","",""}
        };
        char element_column_order[1][6][20]={
        {"ORDER_NUM","DATE","USER_ID","PRICE","PRODUCT_ID",""}
        };
        // int arr_order[] = {15,22,15,15,0,0}; // 67 로 맞추기
        int arr_order[] = {9,23,13,11,11,0}; // 다 챙워져 있거나 하나가 없으면 66 두 개일때는 67 3개 일때는 68 
	
	char element_detail[3][6][20]={
        {"123443","SONATA SE","BLUE","COMPACT","1000C",""},
        {"234223","LAY NEW","BLACK","MEDIUM","2000C",""},
        {"234334","G80 NEW","WHILE","TRUCK","3300C",""}
        };
        char element_column_detail[1][6][20]={
        {"PRODUCT_ID","MODEL_NAME","COLOR","SIZE","CC",""}
        };
        int arr_detail[] = {13,20,9,14,10,0};

	/*char element_order[3][6][10]={
        {"1234","SONATA","H3YUNDAI","DIGEAL","",""},
        {"23422","LAY","K3IA","333EV","",""},
        {"23","G830","G33ENESIS","asdfqwerq","",""}
        };
        char element_column_user[1][7][10]={
        {"USER_ID","NAME","PASSWORD","ADDR","PHONE","ROLE"}
        };
        int arr_user[] = {8,5,12,20,13,5};
*/
