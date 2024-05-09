#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[]){

	char* pathname = argv[1];
	struct stat stat1;

	int fd = open(pathname, O_RDWR);
	if(fd == -1){
		perror("open failed");
		exit(1);
	}

	stat(pathname, &stat1);
	char* buf = (char*)malloc(stat1.st_size * sizeof(char));
	char* buf2 = (char*)malloc(100);
	read(fd, buf, stat1.st_size);
	close(fd);
	printf("%s", buf);

	scanf("%[^\n]", buf2);
	int len = strlen(buf2);

	fd = open(pathname, O_RDWR | O_APPEND);
	write(fd, buf2, len);
	close(fd);
	
	
	
	return 0;
}
