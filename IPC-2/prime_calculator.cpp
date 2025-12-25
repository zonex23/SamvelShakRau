#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>

using namespace std;


bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return false;
    }
    return true;
}


int find_nth_prime(int n) {
    int count = 0;
    int num = 2;
    while (true) {
        if (is_prime(num)) {
            count++;
            if (count == n) {
                return num;
            }
        }
        num++;
    }
}

int main() {
    int pipe_parent_to_child[2], pipe_child_to_parent[2];

    
    if (pipe(pipe_parent_to_child) == -1 || pipe(pipe_child_to_parent) == -1) {
        cerr << "Pipe creation failed!" << endl;
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        return 1;
    }

    if (pid == 0) { 
        close(pipe_parent_to_child[1]);  
        close(pipe_child_to_parent[0]);  

        int m;
        read(pipe_parent_to_child[0], &m, sizeof(m));
        close(pipe_parent_to_child[0]);  

        cout << "[Child] Calculating " << m << "-th prime number..." << endl;
        int result = find_nth_prime(m);

        
        write(pipe_child_to_parent[1], &result, sizeof(result));
        close(pipe_child_to_parent[1]);  

        exit(0);
    } else {  
        close(pipe_parent_to_child[0]);  
        close(pipe_child_to_parent[1]);  

        string input;
        while (true) {
            cout << "[Parent] Please enter the number (or 'exit' to quit): ";
            cin >> input;

            if (input == "exit") {
                cout << "[Parent] Exiting..." << endl;
                break;
            }

            int m = stoi(input);
            cout << "[Parent] Sending " << m << " to the child process..." << endl;

            write(pipe_parent_to_child[1], &m, sizeof(m));
            close(pipe_parent_to_child[1]);  

            cout << "[Parent] Waiting for the response from the child process..." << endl;

            int result;
            read(pipe_child_to_parent[0], &result, sizeof(result));
            cout << "[Parent] Received calculation result of prime(" << m << ") = " << result << "..." << endl;
        }

        
        wait(NULL);
        close(pipe_child_to_parent[0]);  
    }

    return 0;
}
