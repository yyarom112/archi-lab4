
#include <stdio.h>
#define SYS_WRITE 1
#define STDOUT 1
//#define PRINT_FD(stdio) (system(SYS_WRITE,stdio->_fileno,sizeof(stdio->_fileno)));
#define PRINT_FD_printf(stdio) (printf("%d\n", stdio->_fileno));

int main() {
    PRINT_FD_printf(stdin);
    PRINT_FD_printf(stdout);
    PRINT_FD_printf(stderr);
    return 0;
}

