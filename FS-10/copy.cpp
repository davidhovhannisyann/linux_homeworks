#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <cstring>
#include <unistd.h>
#include <vector>
using namespace std;

#define BUF_SIZE 100

int main(int argc, char** argv){
    if(argc < 2){
        cout << "Source File Path is Not Given" << endl; // Check if file path is given
        exit(1);
    }
    if(argc < 3){
        cout << "Destination File Path is Not Given" << endl; // Check if file path is given
        exit(1);
    }
    char* src_path = argv[1];
    char* dest_path = argv[2];
    int src_fd = open(src_path, O_RDONLY);
    int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(src_fd < 0 || dest_fd < 0){
        cerr << strerror(errno) << endl;
        exit(errno);
    }
    vector<int> byte_vec;

    struct stat stat_buffer; 
    int file_info = stat(src_path, &stat_buffer); // Get file information
    if(file_info  < 0){
        cerr << strerror(errno) << endl;
        exit(1);
    }

    int file_length = stat_buffer.st_size;
    
    int byte_count = 0;
    while(byte_count <= file_length){
        int byte_jmp = lseek(src_fd, 0, SEEK_HOLE);
        if(byte_jmp < 0){
            cerr << strerror(errno) << endl;
            exit(errno);
        }

        if(byte_jmp == file_length){
            byte_vec.push_back(byte_jmp);
            break;
        }
        byte_vec.push_back(byte_jmp);
        byte_count += byte_jmp;
        
        byte_jmp = lseek(src_fd, 0, SEEK_DATA);
        if(byte_jmp < 0){
            cerr << strerror(errno) << endl;
            exit(errno);
        }
        byte_vec.push_back(byte_jmp);
        byte_count += byte_jmp;
    }
    
    
    char* buffer = new char[BUF_SIZE];
    int count;
    for(int i = 0; i < byte_vec.size(); i++){
        count = 0;
        while(count < byte_vec[i]){
            int read_bytes = read(src_fd, buffer, BUF_SIZE);
            if(read_bytes < 0){
                cerr << strerror(errno) << endl;
                exit(errno);
            }

            int written_bytes = write(dest_fd, buffer, read_bytes);
            if(read_bytes < 0){
                cerr << strerror(errno) << endl;
                exit(errno);
            }
            count += read_bytes;
        }
    }

    int total_bytes = 0;
    for(int i = 0; i < byte_vec.size(); i++){
        total_bytes += byte_vec[i];
    }

    int hole_bytes = 0;
    for(int i = 1; i < byte_vec.size(); i += 2){
        hole_bytes += byte_vec[i];
    }

    int data_bytes = 0;
    for(int i = 0; i < byte_vec.size(); i += 2){
        data_bytes += byte_vec[i];
    }

    cout << "Successfully copied " << total_bytes << "bytes ( data: " << data_bytes << ", hole: " << hole_bytes << ")" << endl;

    int closed = close(src_fd);
    if(closed < 0){
        cerr << strerror(errno) << endl;
        exit(errno);
    }
    closed = close(src_fd);
    if(closed < 0){
        cerr << strerror(errno) << endl;
        exit(errno);
    }

    delete[] buffer;
}