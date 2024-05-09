#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	char* pathname = argv[1];
	struct stat st;

	int fd = open(pathname, O_RDWR | O_EXCL);
	if(fd == -1){
		perror("open failed");
		exit(1);
	}
	stat(pathname, &st);

	char* buf = (char*)malloc(st.st_size * sizeof(char));
	int arr[128] = {};

	read(fd, buf, st.st_size);
	close(fd);

	for(int i = 0; i < st.st_size; i++){
		arr[buf[i]]++;
	}

	for(int i = 0; i < 128; i++){
		if(arr[i] != 0){
			if(i == ' '){ 
				printf("Space has been %d times\n", arr[i]);
			}else if(i == '\n'){
				printf("NL has been %d times\n", arr[i]);
			}else if(i == '	'){
				printf("TAB has been %d times\n", arr[i]);
			}else{
				printf("%c has been %d times\n", i, arr[i]);
			}
		}
	}
	
	free(buf);

	return 0;
}
