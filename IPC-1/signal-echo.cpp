#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <pwd.h>
#include <ucontext.h>
#include <cstring>

void signal_handler(int sig, siginfo_t* info, void* context) {
    if (sig == SIGUSR1) {
        
        pid_t sender_pid = info->si_pid;
        
        
        uid_t sender_uid = info->si_uid;
        
        
        struct passwd* pw = getpwuid(sender_uid);
        std::string username = "unknown";
        if (pw != NULL) {
            username = pw->pw_name;
        }
        
        
        ucontext_t* ucontext = (ucontext_t*)context;
        
        
        std::cout << "Received a SIGUSR1 signal from process " 
                  << sender_pid << " executed by " 
                  << sender_uid << " (" << username << ")." << std::endl;
        
        
        
        #if defined(__i386__) || defined(__i386) || defined(__i686__)
        void* eip = (void*)ucontext->uc_mcontext.gregs[REG_EIP];
        void* eax = (void*)ucontext->uc_mcontext.gregs[REG_EAX];
        void* ebx = (void*)ucontext->uc_mcontext.gregs[REG_EBX];
        
        std::cout << "State of the context: EIP = " << eip
                  << ", EAX = " << eax
                  << ", EBX = " << ebx << "." << std::endl;
        
        
        #elif defined(__x86_64__) || defined(__x86_64)
        void* rip = (void*)ucontext->uc_mcontext.gregs[REG_RIP];
        void* rax = (void*)ucontext->uc_mcontext.gregs[REG_RAX];
        void* rbx = (void*)ucontext->uc_mcontext.gregs[REG_RBX];
        
        std::cout << "State of the context: RIP = " << rip
                  << ", RAX = " << rax
                  << ", RBX = " << rbx << "." << std::endl;
        
        
        #else
        std::cout << "State of the context: Registers not available for this architecture." << std::endl;
        #endif
    }
}

int main() {
    std::cout << "Signal handler program started." << std::endl;
    std::cout << "My PID: " << getpid() << std::endl;
    std::cout << "Waiting for SIGUSR1 signal..." << std::endl;
    std::cout << "Send signal using: kill -SIGUSR1 " << getpid() << std::endl;
    std::cout << std::endl;
    
    
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = signal_handler;  
    sa.sa_flags = SA_SIGINFO;          
    
    
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        std::cerr << "Error: Cannot set signal handler" << std::endl;
        return 1;
    }
    
    
    while (true) {
        sleep(10);
        std::cout << "Program is still running... (PID: " << getpid() << ")" << std::endl;
    }
    
    return 0;
}
