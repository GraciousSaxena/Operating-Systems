#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char* argv[]){
	char *file = argv[1];
	int fd;
	struct flock lock;
	printf("Opening file\n");
	fd = open(file, O_RDONLY, 777);
	printf("Locking File\n");
	memset(&lock, 0, sizeof(lock));
	lock.l_type = F_WRLCK;
	fcntl(fd, F_SETLKW, &lock);
	printf("The file has been locked\n");
	printf("Press Enter to unlock");
	getchar();
	printf("Releasing Lock");
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLKW, &lock);
	close(fd);
	return 0;
}



