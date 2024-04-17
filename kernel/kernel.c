#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#include "system.h"
#include "share_mem.h"

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

void print_minios(char* str);

int main() {
    print_minios("[MiniOS SSU] Hello, World!");

    char *input;

    while(1) {
        // readline을 사용하여 입력 받기
        input = readline("커맨드를 입력하세요(종료:exit) : ");
        printf("%s\n", input);
        if (strcmp(input,"exit") == 0) {
            break;
        }

	else if (strcmp(input,"minisystem") == 0){
            minisystem();
        }

	else if (strcmp(input, "login") == 0) {
	    login();
	}

	else if (strcmp(input, "os_week5") == 0) {
	    if(os_week5_hw() == 1)
	    {
		    fprintf(stderr, "Launch os_week5_hw Falied");
	    	    return 1;
	    }
	}
        
	else if (strcmp(input, "os_week6") == 0) {
	    if(os_week6_hw() == 1)
	    {
		    fprintf(stderr, "Launch os_week6_hw Falied");
	            return 1;
	    }
	}
	else if (strcmp(input, "os_week7") == 0) {
	    if(os_week7_hw() == 1)
	    {
		    fprintf(stderr, "Launch os_week7_hw Failed");
		    return 1;
	    }
	}
        else 
	{
		printf("%s\n", input);
		system(input);
	}
	free(input);
    }
    
    print_minios("[MiniOS SSU] MiniOS Shutdown........");

    return(1);
}

void print_minios(char* str) {
        printf("%s\n",str);
}
