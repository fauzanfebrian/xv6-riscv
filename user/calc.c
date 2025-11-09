#include <kernel/types.h>
#include <user/user.h>

int getcmd(char* strPrint, int nPrint, char* buf, int nbuf) {
    write(2, strPrint, nPrint);
    memset(buf, 0, nbuf);
    gets(buf, nbuf);
    if (buf[0] == 0)  // EOF
        return -1;
    return 0;
}

void itoa(int n, char* s) {
    char* p = s;
    char tmp;
    char* q;

    // generate digits in reverse order
    do {
        *p++ = n % 10 + '0';
        n /= 10;
    } while (n > 0);

    *p = '\0';
    p--;

    // reverse the string
    for (q = s; q < p; q++, p--) {
        tmp = *q;
        *q = *p;
        *p = tmp;
    }
}

int main() {
    int p[2];
    if (pipe(p) < 0) {
        printf("pipe failed\n");
        exit(1);
    }

    int pid = fork();
    if (pid < 0) {
        printf("fork failed\n");
        exit(1);
    }

    if (pid == 0) {
        static char buf[100];

        getcmd("OP=", 3, buf, sizeof(buf));
        char op = buf[0];

        getcmd("A=", 2, buf, sizeof(buf));
        int A = atoi(buf);

        getcmd("B=", 2, buf, sizeof(buf));
        int B = atoi(buf);

        int result;

        if (op == '*') {
            result = A * B;
        } else if (op == '+') {
            result = A + B;
        } else if (op == '-') {
            result = A - B;
        } else {
            printf("Invalid operation!\n");
            exit(1);
        }

        char strResult[100];

        itoa(result, strResult);

        close(p[0]);
        printf("Child: Sending result to parent...\n");
        write(p[1], strResult, sizeof(strResult));
        close(p[1]);
        exit(0);
    } else {
        static char buf[100];

        close(p[1]);

        int n = read(p[0], buf, sizeof(buf));

        buf[n] = 0;

        printf("Parent: Received Result = %s\n", buf);

        close(p[0]);
        wait(0);
        exit(0);
    }
}
