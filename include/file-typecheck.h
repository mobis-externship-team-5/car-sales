#ifndef FILETYPECHECK_H
#define FILETYPECHECK_H


void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

#endif
