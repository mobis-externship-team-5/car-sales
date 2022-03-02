#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

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
