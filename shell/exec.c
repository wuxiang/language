#include <stdio.h>
#include <unistd.h>

int main()
{
    char* arg[2];
    arg[0] = "ssh.sh";
    arg[1] = NULL;
    //execlp("~/language/shell/ssh.sh", "./ssh.sh", NULL);
    execv("/home/wuxiang/language/shell/ssh.sh", arg);
    return 0;
}
