#include <stdio.h>
#include <string.h>

#define MAX_INPUT 100

int good_echo();

int main()
{
    good_echo();

    return 0;
}

int good_echo()
{
    char buff[MAX_INPUT];

    if (stdin == NULL || stdout == NULL) {
        perror("Error opening stdio");
        return -1;
    }

    while(fgets(buff, MAX_INPUT, stdin)) {
        // printf("%s", buff);
        fputs(buff, stdout);

        if (strlen(buff) < MAX_INPUT - 1 || buff[MAX_INPUT-2] == '\n')
            break;
    }

    return 0;
}

