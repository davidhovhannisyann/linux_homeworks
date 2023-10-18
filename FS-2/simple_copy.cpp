#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

#define BUF 100

int main(int argc, char** argv){
    if(argc < 3){
		std::cerr << "Error : File Paths Are Not Given" << std::endl;
		exit(1);
	}
	char* read_path = argv[1];
	char* write_path = argv[2];
	int rfile = open(read_path, O_RDONLY);
	int wfile = open(write_path, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if(rfile < 0 || wfile < 0){
		std::cerr << strerror(errno) << std::endl;
		exit(errno);
	}
	char *buf = new char[BUF + 1];
	int read_file = 0;
    int write_file = 0;
	while(true){
		read_file = read(rfile, buf, BUF);
		if(read_file < 0){
			std::cerr << strerror(errno) << std::endl;
			exit(errno);
		}
		if(read_file == 0){
			break;
		}
        write_file = write(wfile, buf, BUF);
        if(write_file < 0){
			std::cerr << strerror(errno) << std::endl;
			exit(errno);
		}
	}
	int close_read = close(rfile);
    int close_write = close(wfile);
	if(close_read < 0 || close_write < 0){
		std::cerr << strerror(errno) << std::endl;
	}

	delete[] buf;
	return 0;
}