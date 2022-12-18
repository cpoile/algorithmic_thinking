#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <inttypes.h>
#include <malloc.h>
#endif

#ifdef __APPLE__
#include <stdint.h>
#include <stdlib.h>
#endif

#ifdef __linux__
#include <stdint.h>
#include <stdlib.h>
#endif

int main(void) {
    puts("hello!");
}
