#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	int fd;
       	size_t size;
       	char string[] = "IFMITO. 3.008.2.24.\n";
       	if((fd = open("myfile", O_WRONLY|O_CREAT, 0666)) < 0) {
	       	printf("Ошибка при открытии файла\n");
	       	exit(-1);
       	}
	size = write(fd,string,20);
	if(size != 20){
		printf("Не удалось записать всю строку");
		exit(-1);
	}
	else
		printf("Строка записана в файл \"myfile\"\n");
	printf("В файл с дескриптором %d записано %ld байт\n", fd, size);
	if(close(fd) < 0){
		printf("Не удается заерыть файл с дескриптором %d\n", fd);
		exit(-1);
       	}
       	return 0;
}
