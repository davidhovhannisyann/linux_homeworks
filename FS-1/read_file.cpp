#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

#define BUF 100

int main(int argc, char** argv){
	if(argc < 2){
		std::cerr << "Error : File Path is Not Given" << std::endl;
		exit(1);
	}
	char* path = argv[1];
	int file_desc = open(path, O_RDONLY);
	if(file_desc < 0){
		std::cerr << strerror(errno) << std::endl;
		exit(errno);
	}
	char *buf = new char[BUF + 1];
	int read_file = 0;
	while(true){
		read_file = read(file_desc, buf, BUF);
		if(read_file < 0){
			std::cerr << strerror(errno) << std::endl;
			exit(errno);
		}
		if(read_file == 0){
			break;
		}
		buf[BUF] = '\0';
		std::cout << buf;
	}
	int close_file = close(file_desc);
	if(close_file < 0){
		std::cerr << strerror(errno) << std::endl;
	}

	delete[] buf;
	return 0;
}