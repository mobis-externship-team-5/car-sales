#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "ui-printlist.h"

int signup(USER **uhead, USER **utail){
    FILE *fp;
    USER *temp, *comp;

    temp = (USER*)malloc(sizeof(USER));

    //개인정보 입력
    printf("이름을 입력하세요(영문 20자 이내, 한글 10자 이내) : ");
    fgets(temp->name,19,stdin);
    temp->name[strlen(temp->name)-1]='\0';


    while(1){
        printf("사용할 ID를 입력하세요(영문 20자 이내, 한글 10자 이내) : ");
        fgets(temp->user_id,19,stdin);
        temp->user_id[strlen(temp->user_id)-1]='\0';

        //아이디 중복되는 부분 예외처리?
        int chk = 1;
        comp = *uhead;
        while(comp!=NULL){
            if(strcmp(comp->user_id,temp->user_id)==0) {
                chk = 0;
                break;
            }
            comp = comp->next;
        }
        if(chk) break;
        else {
            printf("중복된 ID입니다. 다시 입력하세요.\n");
        }
    }
    
    printf("패스워드를 입력하세요(영문 20자 이내, 한글 10자 이내) : ");
    fgets(temp->password,19,stdin);
    temp->password[strlen(temp->password)-1]='\0';


    printf("주소를 입력하세요(영문 50자 이내, 한글 25자 이내) : ");
    fgets(temp->addr,19,stdin);
    temp->addr[strlen(temp->addr)-1]='\0';


    printf("전화번호를 입력하세요 ex) 010-1234-5678 : ");
    fgets(temp->phone,19,stdin);
    temp->phone[strlen(temp->phone)-1]='\0';

    //링크리스트 편집
    if((*uhead)==NULL){
        *uhead = *utail = temp;
    }
    else {
        (*utail)->next = temp;
        *utail = temp;
    }
    printf("\n\n");
    printf("%s님 회원가입이 완료되었습니다.\n",temp->name);
    return 0;
}

int login(USER *uhead, USER **current_user) {
    USER *temp = (USER*)malloc(sizeof(USER));
    USER *guest = (USER*)malloc(sizeof(USER));
    char id[20];
    char pw[20];
    char gt;
    int chk = 0;
    //아이디와 패스워드 입력
    while(1){
        printf("YOUR ID : ");
        fgets(id,19,stdin);
        id[strlen(id)-1]='\0';

        printf("YOUR PASSWORD : ");
        fgets(pw,19,stdin);
        pw[strlen(pw)-1]='\0';

        //데이터 중 일치하는 아이디가 있는지 확인
        //로그인 시에는 최소 1개 이상의 데이터가 있다고 가정
        temp = uhead;
        while(temp!=NULL){
            if(strcmp(id,temp->user_id)==0 && strcmp(pw,temp->password)==0) {
                if(strcmp(id,"root")==0 && strcmp(pw,"root")==0){
                    (*current_user) = temp;
                    (*current_user)->role = ADMIN;
                    chk = 1; 
                    break;
                }
                (*current_user) = temp;
                (*current_user)->role = CUSTOMER;
                chk = 1;
                break;
            }
            temp = temp->next;
        }
        if(chk) break;
        else {
            printf("\nID or PW is wrong\n\n");
            printf("press Enter... ");
            getchar();
            return 1;
        }
    }
    if((*current_user)->role == CUSTOMER){
        printf("회원으로 로그인합니다.\n\n");
    }
    else if((*current_user)->role == ADMIN){   // ADMIN 이 따로 있기 때문에 지우든지 
        printf("관리자로 로그인합니다.\n\n");   // 아니면 switch value를 int로 리턴할건지
    }
    else if((*current_user)->role == GUEST){
        printf("비회원으로 로그인합니다.\n\n");
    }
    return 0;
}


int logout(USER *current_user) {
    printf("로그아웃 합니다.\n");
    current_user = NULL;
    return 0;
}


int find_user(USER *uhead, char *user_id) {
    USER *find;
    find = uhead;
    while(find!=NULL){
        if(strcmp(user_id,find->user_id)==0) {
            printf("해당 id의 유저는 %s 입니다.\n",find->name);
            return 1;
        }
        find = find->next;
    }
    printf("일치하는 유저가 없습니다.\n");
    return 0;
}


int print_all_user(USER *uhead) {
    USER *find;
    printf("-------- 유저 명단 리스트 --------\n");
    find = uhead;
    while(find!=NULL){
        printf("ID : %s         이름 : %s \n",find->user_id,find->name);
        find = find->next;
    }
    printf("-------- 유저 명단 리스트 --------\n\n");
    return 0;
}


int load_user(USER **uhead, USER **utail, const char *filename)
{
    FILE *fp;
    USER *new_user;

    if ((fp = fopen(filename, "r")) == NULL) {
        return 0;
    }

    while (1)
    {
        new_user = (USER*)malloc(sizeof(USER));

        if ((fread(new_user, sizeof(USER), 1, fp))) {
            if (*uhead == NULL)
            {
                *uhead = *utail = new_user;
            }
            else
            {
                (*utail)->next = new_user;
                *utail = new_user;
            }
        }
        else {
            free(new_user);
            break;
        }
    }

    fclose(fp);
    return 0;
}

int save_user(USER *uhead, const char *filename)
{
    FILE *fp;
    USER *cur;
    
    if ((fp = fopen(filename, "w")) == NULL) {
        return 0;
    }

    cur = uhead;
    while (cur)
    {
        fwrite(cur, sizeof(USER), 1, fp);
        cur = cur->next;
    }

    fclose(fp);
    return 0;
}




int user_search(USER *uhead, USER **shead, USER **stail,int *user_role, int opt2)
{
    int role = *user_role;
    USER *search, *smake;
    int opt = opt2;
    char m[100];

    search = uhead;
    *shead = NULL;
    if(opt==1){ // 紐⑤뜽紐낆쑝濡� 寃��깋
        printf("INPUT USER YOU WANT TO FIND: ");
        fgets(m,99,stdin);
        m[strlen(m)-1]='\0';
        while(search!=NULL){
            if(strcmp(m,search->name)==0) {
                smake = (USER*)malloc(sizeof(USER));
                user_copy(search,smake);
                if((*shead)==NULL){
                    *shead = *stail = smake;
                }
                else{
                    (*stail)->next = smake;
                    *stail = smake;
                }
            }
            search = search->next;
        }
    }
    else {
        printf("IT's WRONG. \n");
    }
    return 0;
}

int user_copy(USER *origin,USER *copy)
{
    strcpy(copy->user_id,origin->user_id);
    strcpy(copy->name,origin->name);
    strcpy(copy->password,origin->password);
    strcpy(copy->addr,origin->addr);
    strcpy(copy->phone,origin->phone);
    copy->role=origin->role;
    return 0;
}








int print_list_user(USER *uhead, int page_no,char element_column[][6][20],int arr[6]){
        USER *current = uhead;
        int chart_length = 72;
        int arr_size = 6;
//      ui_printlist_printroof('-','*');

        char temp_list[][15] = {"GUEST","CUSTOMER","ADMIN"};
        ui_printlist_printline('=');
        ui_printlist_printline('-');
        set_column_size(arr,chart_length,arr_size,element_column,1,0);
        ui_printlist_printline('-');

//�젙�닔�뒗 猷⑦듃 10�뀋�쑝濡� 吏쒕Ⅴ怨졼뀘�꽩
        for(int i=0; i<page_no*5;i++){
           if(current==NULL)
                        break;
                current=current->next;
        }
        int count = 0;
        while (current)
    {
        if(count == 5)
                break;
        printf("|");
        printspace_string(current->user_id,arr[0]);
        printspace_string(current->name,arr[1]);
        printspace_string(current->password,arr[2]);
        printspace_string(current->addr,arr[3]);
        printspace_string(current->phone,arr[4]);
	printspace_string(temp_list[current->role],arr[5]);
//printspace_string(user_status_str[current->status],arr[0]);
        printf("\n");

        current = current->next;
        count++;
        }
        ui_printlist_printline('-');
        printf("\n                                   %d/10                           \n",page_no+1);
        ui_printlist_printline('=');


}

int user_search_one(USER *uhead, USER **shead, USER **stail,int *user_role, int opt2,char m[100])
{
    int role = *user_role;
    USER *search, *smake;
    int opt = opt2;
    //char m[100];

    search = uhead;
    *shead = NULL;
    if(opt==1){ // 紐⑤뜽紐낆쑝濡� 寃��깋
        //printf("INPUT USER YOU WANT TO FIND: ");
        //fgets(m,99,stdin);
        //m[strlen(m)-1]='\0';
        while(search!=NULL){
            if(strcmp(m,search->name)==0) {
                smake = (USER*)malloc(sizeof(USER));
                user_copy(search,smake);
                if((*shead)==NULL){
                    *shead = *stail = smake;
                }
                else{
                    (*stail)->next = smake;
                    *stail = smake;
                    break;
                }
            }
            search = search->next;
        }
    }
    else {
        printf("IT's WRONG. \n");
    }
    return 0;
}

