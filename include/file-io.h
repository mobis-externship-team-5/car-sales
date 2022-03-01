#ifndef FILE_IO_H
#define FILE_IO_H

#define ERR_FILE_OK         0 /* 함수 성공 상수값 */
#define ERR_FILE_OPEN   -9000 /* 파일 오픈 오류 코드 */


/* 파일의 모든 내용을 불러들이기 */
// 구조체 수 만큼 호출
int load_data(void** head, void **tail, const char *filename);

/* 구조체 내용을 파일에 저장 */
int save_data(void* head, const char *filename);

#endif