#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <cstring>
#include <unistd.h>
using namespace std;


int main(int argc, char** argv){
    if(argc < 2){
        cout << "File Path is Not Given" << endl; // Check if file path is given
        exit(1);
    }
    char* path = argv[1]; // Get Path File from command line argument 
    
    int file_desc = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); // Open file to write(create if doesn't exist)
    if(file_desc < 0){ // Check if file's opened successfully
        cerr << strerror(errno) << endl;
        exit(errno);
    }

    int new_fd =0; // Create a new descriptor for the file
    int duplicate = dup2(file_desc, new_fd); // Copy file descriptor to new descriptor
    if(duplicate < 0){ // Check 
        cerr << strerror(errno) << endl;
        exit(errno);
    }

    string str1 = "first line\n";
    string str2 = "second line\n";

    int written = write(file_desc, str1.c_str(), str1.size()); // write the 1st line to 1st descriptor
    if(written < 0){
        cerr << strerror(errno) << endl;
        exit(errno);
    }

    written = write(new_fd, str2.c_str(), str2.size()); // write the 2nd line to 2nd descriptor
    if(written < 0){
        cerr << strerror(errno) << endl;
        exit(errno);
    }

    int closed = close(file_desc); 
    
    return 0;
}