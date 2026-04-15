#include "types.h"
#include "stat.h"
#include "user.h"


int main(){
    char *syscall_names[] = {
    "", "fork", "exit", "wait", "pipe", "read", "kill", "exec",
    "fstat", "chdir", "dup", "getpid", "sbrk", "sleep", "uptime",
    "open", "write", "mknod", "unlink", "link", "mkdir", "close", "getcounts"
    };

    int cycles = 20; // Monitor for 20 refreshes
    while(cycles > 0) {
       // Clear screen (ANSI escape code)
    printf(1, "\033[2J\033[H"); 

    printf(1, "====================================================\n");
    printf(1, "     SCUT MONITOR: KERNEL OBSERVABILITY DASHBOARD    \n");
    printf(1, "====================================================\n");
    printf(1, "  ID | SYSCALL NAME | GLOBAL (System) | LOCAL (Self) \n");
    printf(1, "----------------------------------------------------\n");

    for(int i = 1; i <= 22; i++) {
      int g_count = getcounts(-i); 
      int l_count = getcounts(i);  
      
      if(g_count > 0) {
        
        printf(1, "  %d  | %s", i, syscall_names[i]);
        
        // Manual spacing/padding for the table alignment
        int name_len = strlen(syscall_names[i]);
        for(int s = 0; s < (12 - name_len); s++) printf(1, " ");
        
        printf(1, " |      %d       |      %d      \n", g_count, l_count);
      }
    }

    printf(1, "====================================================\n");
    printf(1, "Refreshing every 2 seconds... [Ctrl+C to stop]\n");
        
        sleep(200);
        cycles--;
    }
    printf(1, "Monitoring session complete.\n");
    exit();






}