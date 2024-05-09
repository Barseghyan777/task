#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	struct stat stat1;
	char* source_path = argv[1];
	char* dest_path = argv[2];


	int fd = open(source_path, O_RDONLY, 777);
	if(fd == -1){
		perror("open failed");
		exit(1);
	}
	stat(source_path, &stat1);
	char* str = (char*)malloc(stat1.st_size * sizeof(char));
	read(fd, str, stat1.st_size);
	close(fd);


	int fd2 = open(dest_path, O_WRONLY | O_CREAT | O_EXCL, 777);
	if(fd2 < 0){
		perror("open failed");
		exit(1);
	}
	write(fd2, str, stat1.st_size);
	close(fd);

	return 0;
}
