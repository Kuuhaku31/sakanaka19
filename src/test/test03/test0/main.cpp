
#include "version_controller.h"

#include <stdio.h>

int
main()
{
    printf("Hello, World!\n");
    uint32_t version = ReadVersion();
    printf("Version: %d\n", version);
    return 0;
}
