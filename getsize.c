#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
 {
    (void)argc;
    
    struct stat buf;

    stat(argv[1], &buf);

    printf("%d\n", (int)buf.st_size);
 }