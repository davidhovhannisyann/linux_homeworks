#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <errno.h>
using namespace std;

#define BUF_SIZE 100

int main(int argc, char** argv){
    if(argc < 2){
        cerr << "File Path Is Not Given" << endl;
        exit(1);        
    }
    const char* path = argv[1]; // Get the file path
    
    int file_desc = open(path, O_WRONLY); // Open the file
    if(file_desc  < 0){
        cerr << strerror(errno) << endl; // Check if file is opened 
        exit(1);
    }
    
    char* buffer = new char[BUF_SIZE];  
    for(int i = 0; i < BUF_SIZE; i++){ // Create a buffer, fill '\0's to write to file
        buffer[i] = '\0';
    }
    
    struct stat stat_buffer; 
    int file_info = stat(path, &stat_buffer); // Get file information
    if(file_info  < 0){
        cerr << strerror(errno) << endl;
        exit(1);
    }

    int file_length = stat_buffer.st_size; // Get file size in bytes
    
    int seeked_bytes = lseek(file_desc, 0, SEEK_SET); // Set cursor to the begining of the file(just in case)
    if(seeked_bytes < 0){
        cerr << strerror(errno) << endl;
        exit(1);
    }
    
    int writeen_bytes, count;
    while(count < file_length){ // Write '\0's to file
         writeen_bytes = write(file_desc, buffer, BUF_SIZE);
         if(writeen_bytes < 0){
             cerr << strerror(errno) << endl;
         }
         count += writeen_bytes;
    }

    int removed = unlink(path); // Remove file name from file system
    if(removed  < 0){
        cerr << strerror(errno) << endl;
        exit(1);
    }

    delete[] buffer;
    return 0;


}