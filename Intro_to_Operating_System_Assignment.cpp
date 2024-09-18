#include <iostream>
#include <unistd.h>  // For fork(), getpid(), sleep(), kill()
#include <csignal>   // For kill()

using namespace std;

int main() {
    pid_t pids[4];  // Array to store PIDs of child processes

    // Create 4 child processes
    for (int i = 0; i < 4; ++i) {
        pids[i] = fork();  

        if (pids[i] == 0) {
            // In the child process
            cout << "Child process " << i << " started with PID " << getpid() << endl;
            while (true) {
                sleep(1);  
            }
        } else if (pids[i] > 0) {
            cout << "Started process " << i << " with PID " << pids[i] << endl;
        } else {
            cerr << "Fork failed!" << endl; //used for error messages 
            return 1;
        }
    }

    // Let processes run for 10 seconds
    sleep(10);

    // Kill child processes
    for (int i = 0; i < 4; ++i) {
        cout << "Killing process with PID " << pids[i] << endl;
        kill(pids[i], SIGTERM);  // Terminate process
    }

    return 0;
}
