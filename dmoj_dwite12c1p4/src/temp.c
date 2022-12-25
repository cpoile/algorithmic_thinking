
#include <printf.h>

void change_buf(char buf[], int *pos) {
    buf[(*pos)++] = 'h';
    buf[(*pos)++] = 'e';
    buf[(*pos)++] = 'l';
    buf[(*pos)++] = 'l';
    buf[(*pos)++] = 'o';
    buf[(*pos)++] = '\0';
}

int main() {
    char buf[10];
    int pos = 0;
    change_buf(buf, &pos);

    printf("%s , pos: %d\n", buf, pos);
}
