#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>


#define PAGE_SIZE 4096

char* make_shm(const char* shm_name)
{
	int shm_fd;
	void* ptr;
	
	shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);

	ftruncate(shm_fd, PAGE_SIZE);

	ptr = (char*) mmap(0, PAGE_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	return ptr;
}

void unlink_shm(const char* shm_name)
{
	shm_unlink(shm_name);	
}

void insert_chr_to_shm(char* ptr, const char* message)
{
	sprintf(ptr, "%s", message);
	ptr += strlen(message);
}

void get_chr_from_shm(char* ptr)
{
	printf("%s\n", ptr);
}

void check_ptr(const char* type, char* ptr)
{
	printf("%s : 0x%p\n", type, ptr); 
}
