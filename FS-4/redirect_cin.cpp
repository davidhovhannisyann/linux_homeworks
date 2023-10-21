#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <cstring>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 100

void initialize(int argc, char** argv){
    if(argc < 2){ 
        cout << "File Path Is Not Given" << endl; // Check if File Path is given
        exit(1);
    }
    char* path = argv[1]; // Get Path File from command line argument
    int file_desc = open(path, O_RDWR); // Open file
    if(file_desc < 0){ // Check if file is opened correctly
        cerr << "OPEN() FAILED: " << strerror(errno) << endl;
        exit(errno);
    }
    int new_cin = dup2(file_desc,0); // Move file descripttor to standart stdin input 
    int closed = close(file_desc); // CLose file
    if(closed < 0){
        cerr << "OPEN() FAILED: " << strerror(errno) << endl; // Check file is closed
        exit(errno);
    }
}

int main(int argc, char** argv){

    initialize(argc, argv); // Set standart cin to file

    string input;
    cin >> input; // read file to input
    
    std::string reversed(input.size() + 1, 'a'); // variable to store reversed string in

    int n = input.size(); // reverse string characters
    for(int i = 0; i <= n; i++){
        reversed[i] = input[n - i];
    }
    reversed[n + 1] = '\0'; // Set last element to '\0' so cout will know where to stop
    
    cout << reversed << endl; // print output to the console

    return 0;
}