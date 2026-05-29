#include "../stdlib/stdio.h"
#include "../commands/help.h"
#include "../commands/clear.h"
#include "../commands/greet.h"
#include "../commands/uptime.h"
#include "../commands/hexdump.h"

#include "../util.h"

#define SHELL_BUFFER_SIZE 256

char shellBuffer[SHELL_BUFFER_SIZE];
int shellIndex = 0;

void* adr;

void shell_execute(const char* cmd){
    
    if(strcmp(cmd, "help") == 0){
        help();
    }
    else if(strcmp(cmd, "clear") == 0){
        clear();
    }
    else if(strcmp(cmd, "greet") == 0){
        greet();
    }
    else if(strcmp(cmd, "uptime") == 0){
        printf("%lds\n\n", uptime());
    }
    else if(strcmp(cmd, "hexdump") == 0){
        hexdump(adr, 128);
    }
    else{
        printf("Unknown command: %s\n", cmd);
    }
}

void shell_input(char c){

    if(c == '\n'){

        putc('\n');

        shellBuffer[shellIndex] = '\0';

        shell_execute(shellBuffer);

        shellIndex = 0;

        printf("\n> ");
    }
    else if(c == '\b'){

        if(shellIndex > 0){
            shellIndex--;

            // visual backspace
            putc('\b');
            putc(' ');
            putc('\b');
        }
    }
    else{

        if(shellIndex < SHELL_BUFFER_SIZE - 1){

            shellBuffer[shellIndex++] = c;

            putc(c);
        }
    }
}

void shell_init(void* addr){

    shellIndex = 0;

    void* adr = addr;

    for(int i = 0; i < SHELL_BUFFER_SIZE; i++){
        shellBuffer[i] = '\0';
    }

    printf("> ");
}