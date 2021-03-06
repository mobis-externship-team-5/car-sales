#ifndef USER_H
#define USER_H


enum USER_ROLE {
    GUEST = 0,
    CUSTOMER = 1,
    ADMIN = 2
};

typedef struct user_t {
    char user_id[20];
    char name[20];
    char password[20];
    char addr[50];
    char phone[20];
    enum USER_ROLE role;

    struct user_t *next;
} USER;

/* 사용자 기능 */
// 고객 계정 생성 (관리자는 미리 생성된 계정 사용)
int signup(USER **uhead, USER **utail);

// 아이디와 패스워드를 입력 받아
// 파일의 내용과 비교하는 연산 (사용자 정보가 파일에 저장되어 있는지 확인)
int login(USER *uhead, USER **current_user);

// 현재 사용자 변수 초기화 시키기
// 현재 유저 = NULL
int logout(USER *current_user);

// 등록된 회원인지 아닌지 판별
int find_user(USER *uhead, char *user_id);

// [관리자] 회원 리스트 출력
int print_all_user(USER *uhead);

int load_user(USER **uhead, USER **utail, const char *filename);

int save_user(USER *uhead, const char *filename);


int print_list_user(USER *uhead, int page_no,char element_column[][6][20],int arr[6]);
int user_search(USER *uhead, USER **shead, USER **stail,int *user_role, int opt2);
//int user_search_ID(USER *uhead,USER **uhead,USER **utail,int user_id);
int user_copy(USER *origin,USER *copy);

int get_user_sales_info(USER *uhead, int *total_user);


#endif
