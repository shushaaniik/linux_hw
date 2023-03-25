#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <pwd.h>
#include <ucontext.h>
#include <cstring>

void sigusr1_handler(int signum, siginfo_t *info, void *context)
{
    pid_t sender_pid;
    uid_t sender_uid;
    struct passwd* sender_pw;
    ucontext_t* ucontext = reinterpret_cast<ucontext_t*>(context);

    sender_pid = info->si_pid;
    sender_uid = info->si_uid;
    sender_pw = getpwuid(sender_uid);

    printf("Received a SIGUSR1 signal from process %d executed by %d (%s).\n", 
           sender_pid, sender_uid, sender_pw->pw_name);
    printf("State of the context: EIP = 0x%llx, EAX = 0x%llx, EBX = 0x%llx.\n", 
           (unsigned long long)ucontext->uc_mcontext.gregs[REG_RIP], 
           (unsigned long long)ucontext->uc_mcontext.gregs[REG_RAX], 
           (unsigned long long)ucontext->uc_mcontext.gregs[REG_RBX]);
}

int main()
{
    struct sigaction action;

    // Set up the signal handler
    memset(&action, 0, sizeof(action));
    action.sa_sigaction = sigusr1_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_SIGINFO;
    if (sigaction(SIGUSR1, &action, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    // Enter the infinite loop
    while (1) {
        sleep(10);
    }

    return EXIT_SUCCESS;
}
