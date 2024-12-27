#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>

#define MSQKEY 51234

struct msgbuf {
    long mtype; // msg type: int value over 0(zero)
    char mtext[BUFSIZ]; // msg content: char value over 1 byte
};

int main(int argc, char **argv) {
    key_t key;
    int n, msqid;
    struct msgbuf mb;

    key = MSQKEY;
    /* Create channel of MSG Queue*/
    if((msqid = msgget(key, IPC_CREAT | IPC_EXCL | 0666)) < 0) {
        perror("msgget()");
        return -1;
    }

    /* Get data from the MSG Queue */
    while((n = msgrcv(msqid, &mb, sizeof(mb), 0, 0)) > 0) {
        switch (mb.mtype)
        /* If `mtype` is 1, get the data and print it on the screen. */
        {
        case 1:
            write(1, mb.mtext, n);
            break;
        /* If 'mtype' is 2, remove the channel's MSG Queue. */
        case2:
            if(msgctl(msqid, IPC_RMID, (struct msqid_ds *) 0) < 0) {
                perror("msgctl()");
                return -1;
            }
            break;
        }
    }

    return 0;
}