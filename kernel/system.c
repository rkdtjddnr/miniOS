#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#include "system.h"
#include "share_mem.h"

#define BUFFER_SIZE 25
#define WRITE_END 1
#define READ_END 0

void minisystem()
{
    printf("minisystem\n");
}

void login()
{
    printf("User ID : 0\n");
    printf("User : ROOT user\n");
}

int os_week5_hw()
{
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
	    kill(getpid(), SIGKILL);
    }
    else
    {
	    int ret;
	    int status;
	    const char* type = "produecer";
	    const char* message = "Hello World!";
	    printf("====== Parent Process ======\n");
	    printf("Insert %s.....\n", message); 
	    insert_chr_to_shm(ptr, message);
	    check_ptr(type, ptr);
	    ret = waitpid(pid, &status, 0);
	    printf("child_complete\n");
	    //print_minios("[MiniOS SSU] MiniOS Shutdown.......");
    }
    
    return 0;
}

int os_week6_hw()
{
    pid_t pid;
    int fd[2];
    char write_msg[BUFFER_SIZE] = "OS_week6!";
    char read_msg[BUFFER_SIZE];

    if(pipe(fd) == -1)
    {
	    fprintf(stderr, "Pipe Falied");
	    return 1;
    }
    pid = fork();
    if(pid < 0)
    {
	    fprintf(stderr, "Fork Falied");
	    return 1;
    }
    else if(pid > 0)
    {
	    int ret;
	    int status;
	    close(fd[READ_END]);
	    printf("write [%s] to pipe, pid : %d\n", write_msg, getpid());
	    write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
	    close(fd[WRITE_END]);
	    ret = waitpid(pid, &status, 0);
	    printf("child_complete\n");
    }
    else
    {
	    close(fd[WRITE_END]);
	    read(fd[READ_END], read_msg, BUFFER_SIZE);
	    printf("read [%s] from pipe, pid : %d\n", read_msg, getpid());
	    close(fd[READ_END]);
	    kill(getpid(), SIGKILL);
    }
}
