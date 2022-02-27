#ifndef FILE_IO_H
#define FILE_IO_H

/* 파일의 모든 내용을 불러들이기 */
// 구조체 수 만큼 호출
int load_func(void** head, void **tail, char *filename);

/* 구조체 내용을 파일에 저장 */
int save_func(void** head, char *filename);

#endif