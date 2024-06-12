#include "errors.h"

int main(int argc, char *argv[])
{
    int seconds;
    char line[128];
    char message[64];

    while(1){
        printf("Alarm> ");
        if(fgets(line, sizeof(line), stdin) == NULL) exit(0);
        if(strlen(line)<=1) continue;

        /*
         *  입력 받은 라인을 초(%d)와 메시지(%64[^\n])로 나눈다.
         *  메시지는 64 문자까지 구성한다.
         *  초는 공백으로 구분한다.
         **/

         if(sscanf(line, "%d %64[^\n]", &seconds, message) <2){
            fprintf(stderr, "Bad command\n");
         }
         else {
            sleep(seconds);
            printf(" (%d) %s\n", seconds, message);
         }
    }
}