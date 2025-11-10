#include "kernel/types.h"
#include "user/user.h"

#define MAX_NAME_LEN 100

int main(void) {
    char name[MAX_NAME_LEN];

    printf("Enter your name: ");
    gets(name, MAX_NAME_LEN);
    name[strcspn(name, "\n")] = '\0';

    printf("Hello, %s!\n", name);
    exit(0);
}
