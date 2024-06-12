#include <sys/types.h>
#include <sys/wait.h>
#include "errors.h"

int main(int argc, char *argv[])
{
    int status;
    char line[128];
    int seconds;
    pid_t pid;
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
            pid = fork();
            if(pid == (pid_t)-1){
                errno_abort("Fork");
            }

            if(pid == (pid_t)0){
                /*
                 *  자식 프로세스에서는 기다린 후에 메시지를 출력한다.
                 **/
                sleep(seconds);
                printf("(%d) %s\n", seconds, message);
            }
            else{
                /*
                 *  부모 프로세스에서는 waitpid()를 호출하여
                 *  이미 종료된 자식 프로세스를 확인한다.
                 **/

                do {
                    pid = waitpid((pid_t)-1, NULL, WNOHANG);
                    if(pid == (pid_t)-1){
                        errno_abort("Wait for child");
                    }
                } while (pid != (pid_t)0);

                // printf("pid: %d", pid);
            }
        }
    }
}