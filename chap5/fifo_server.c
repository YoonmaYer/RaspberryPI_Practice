#include <stdio.h>
#include <fcntl.h>
#include <unistd.h> /* read(), close(), unlink() 등의 시스템 콜을 위한 헤더 파일 */
#include <sys/stat.h>

#define FIFOFILE "fifo"

int main(int argc, char **argv) {
    int n, fd;
    char buf[BUFSIZ];

    unlink(FIFOFILE);   // Remove old FIFO file

    if(mkfifo(FIFOFILE, 0666) < 0) {    // Create new FIFO file
            perror("mkfifo()");
            return -1;
    }

    if((fd = open(FIFOFILE, O_RDONLY)) < 0) {   // Open FIFO
        perror("open()");
        return -1;
    }

    while((n = read(fd, buf, sizeof(buf))) > 0) // FIFO로부터 데이터를 받아온다
    {
        printf("%s", buf);
    }

    close(fd);
    return 0;
}