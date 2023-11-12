#include <iostream>
#include <unistd.h>
#include <vector>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <cstring>
using namespace std;

void do_command(char** cmd){
    char* command = cmd[0];
    struct tms start_st, end_st;
    
    clock_t start, end;

    start = times(&start_st);

    int pid = fork();    
    if(pid < 0){
        cout << "Failed to create process" << endl;
        exit(errno);
    }

    if(pid == 0){
        int executed = execvp(command, cmd);
        cout << strerror(errno) << endl;
        exit(errno);
    }
    else{
        wait(nullptr);
        end = times(&end_st);
        double time = (double)(end - start);
        cout << "Command completed with " << errno << " exit code and took " << time << " seconds "<< endl;
    }
}

int main(int argc, char** argv){

    char* cmd_args[argc - 1];
    int i = 0;

    for(i = 0; i < argc - 2; i++){
        cmd_args[i] = argv[i + 1];
    }

    cmd_args[i + 1] = NULL;
    
    do_command(cmd_args);

}