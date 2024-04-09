#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <unistd.h>

#include "system.h"
#include "share_mem.h"

void print_minios(char* str);

int main() {
    print_minios("[MiniOS SSU] Hello, World!");

    char *input;

    while(1) {
        // readline을 사용하여 입력 받기
        input = readline("커맨드를 입력하세요(종료:exit) : ");

        if (strcmp(input,"exit") == 0) {
            break;
        }

        if (strcmp(input,"minisystem") == 0){
            minisystem();
        }

	if (strcmp(input, "login") == 0) {
	    login();
	}
        else system(input);
    }

    // 메모리 해제
    free(input);

    // OS_week5_HW
    pid_t pid;
    const char* shm_name = "miniOS";
    char* ptr = make_shm(shm_name);
    pid = fork();

    if(pid < 0)
    {
	    fprintf(stderr, "Fork Falied");
	    return 1;
    }
    else if (pid == 0) // child process
    {
	    const char* type = "consumer";
	    printf("====== Child Process ======\n");
	    check_ptr(type, ptr);
	    get_chr_from_shm(ptr);
	    unlink_shm(shm_name);
    }
    else
    {
	    const char* type = "produecer";
	    const char* message = "Hello World!";
	    printf("====== Parent Process ======\n");
	    printf("Insert %s.....\n", message); 
	    insert_chr_to_shm(ptr, message);
	    check_ptr(type, ptr);
	    wait(NULL);
	    printf("child_complete\n");
	    print_minios("[MiniOS SSU] MiniOS Shutdown.......");
    }



    // print_minios("[MiniOS SSU] MiniOS Shutdown........");

    return(1);
}

void print_minios(char* str) {
        printf("%s\n",str);
}
