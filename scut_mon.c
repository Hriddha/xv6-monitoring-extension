#include "types.h"
#include "stat.h"
#include "user.h"

// Helper function: Prints a number with manual padding to keep columns straight
void print_padded_int(int n, int width) {
    int temp = n;
    int digits = (n <= 0) ? 1 : 0;
    while (temp > 0) {
        digits++;
        temp /= 10;
    }
    // Print leading spaces
    for (int i = 0; i < (width - digits); i++) {
        printf(1, " ");
    }
    printf(1, "%d", n);
}

int main() {
    char *syscall_names[] = {
        "", "fork", "exit", "wait", "pipe", "read", "kill", "exec",
        "fstat", "chdir", "dup", "getpid", "sbrk", "sleep", "uptime",
        "open", "write", "mknod", "unlink", "link", "mkdir", "close", "getcounts"
    };

    int cycles = 15;
    while(cycles > 0) {
        printf(1, "\033[2J\033[H"); // Clear screen

        printf(1, "====================================================\n");
        printf(1, "     SCUT MONITOR: KERNEL OBSERVABILITY DASHBOARD    \n");
        printf(1, "====================================================\n");
        printf(1, "  ID | SYSCALL NAME | GLOBAL (System) | LOCAL (Self) \n");
        printf(1, "----------------------------------------------------\n");

        for(int i = 1; i <= 22; i++) {
            int g_count = getcounts(-i); 
            int l_count = getcounts(i);  
            
            if(g_count >= 0) {
                // Print ID (Manual 2-space padding)
                if(i < 10) printf(1, "  "); else printf(1, " ");
                printf(1, "%d | %s", i, syscall_names[i]);
                
                // Pad Name column
                int name_len = strlen(syscall_names[i]);
                for(int s = 0; s < (12 - name_len); s++) printf(1, " ");
                
                printf(1, " |   ");
                print_padded_int(g_count, 8); // Manual padding for Global
                printf(1, "    |   ");
                print_padded_int(l_count, 8); // Manual padding for Local
                printf(1, "   \n");
            }
        }

        printf(1, "====================================================\n");
        printf(1, " Cycles left: %d | \n", cycles);
        
        sleep(200);
        cycles--;
    }
    exit();
}