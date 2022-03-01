#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

int signup(USER **uhead, USER **utail)
{
    FILE *fp;
    USER *temp, *comp;

    //유저 데이터를 불러옴
    fp = fopen("user.txt","w");
    if(fp==NULL) {
        printf("유저 데이터를 불러올 수 없습니다.\n");
    }

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

    printf("%s님 회원가입이 완료되었습니다.\n\n",temp->name);
    fwrite(temp,sizeof(USER),1,fp);
    fclose(fp);

    return 0;
}

int login(USER *uhead, USER *current_user) {
    USER *temp = (USER*)malloc(sizeof(USER));
    char id[20];
    char pw[20];
    int chk = 0;
    //아이디와 패스워드 입력
    while(1){
        printf("id : ");
        fets(id,19,stdin);
        id[strlen(id)-1]='\0';

        printf("password : ");
        fgets(pw,19,stdin);
        pw[strlen(pw)-1]='\0';

        //데이터 중 일치하는 아이디가 있는지 확인
        //로그인 시에는 최소 1개 이상의 데이터가 있다고 가정
        temp = uhead;
        while(temp!=NULL){
            if(strcmp(id,temp->user_id)==0 && strcmp(pw,temp->password)==0) {
                chk = 1;
                current_user = temp;
                break;
            }
            temp = temp->next;
        }
        if(chk) break;
        else {
            printf("아이디 또는 비밀번호가 일치하지 않습니다.\n");
        }
    }
    printf("로그인 성공\n\n");
    //관리자 및 비회원 구분 추가해야함.
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