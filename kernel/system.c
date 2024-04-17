#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

#include "system.h"
#include "share_mem.h"


/* os_week_6 */
#define BUFFER_SIZE 25
#define WRITE_END 1
#define READ_END 0

/* os_week_7 */
#define NUM_THREAD 50
#define TOTAL_POINTS 1000000

int circle_points = 0;
int per_th_work = TOTAL_POINTS / NUM_THREAD;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
/*=================================================*/


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

/*=============os_week_7=============*/
int check_in_circle(const double* x, const double* y)
{
	double dis = sqrt(pow(*x, 2) + pow(*y, 2));
	if (dis > 1.0) return 0;
	else return 1;
}

void* task()
{
	double x, y;
	int is_in_circle;
	unsigned int seed = time(NULL) + pthread_self();
	for (int i = 0; i < per_th_work; i++)
	{
		x = ((double)rand_r(&seed) / RAND_MAX) * 2.0 - 1.0;
		y = ((double)rand_r(&seed) / RAND_MAX) * 2.0 - 1.0;

		is_in_circle = check_in_circle(&x, &y);
		pthread_mutex_lock(&mutex);
		circle_points += is_in_circle;
		pthread_mutex_unlock(&mutex);
	}
}

int os_week7_hw()
{
	circle_points = 0;
	double estimated_pi;
	pthread_t thread[NUM_THREAD];
	for (int i = 0; i < NUM_THREAD; i++)
	{
		if (pthread_create(&thread[i], NULL, task, NULL) != 0)
		{
			fprintf(stderr, "thread create failed");
			return 1;
		}
	}

	for (int i = 0; i < NUM_THREAD; i++)
		pthread_join(thread[i], NULL);

	printf("Number of thread : %d\n", NUM_THREAD);
	printf("Points in circle : %d, Total points : %d\n", circle_points, TOTAL_POINTS);

	estimated_pi = 4 * ((double)circle_points / (double)TOTAL_POINTS);

	printf("Estimated pi = %.4lf\n", estimated_pi);
}
