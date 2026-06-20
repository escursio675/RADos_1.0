#include "vga.h"
#include "stdint.h"
#include "gdt/gdt.h"
#include "interrupts/idt.h"
#include "timer.h"
#include "kmalloc.h"
#include "stdlib/stdio.h"
#include "keyboard.h"
#include "multiboot.h"
#include "memory.h"
#include "util.h"
//include headers

#include "commands/help.h"
#include "commands/uptime.h"
#include "commands/clear.h"
#include "commands/greet.h"
#include "commands/hexdump.h"
//include commands

#include "shell/shell.h"
//include the shell

void kmain(uint32_t magic, struct multiboot_info* bootInfo);

void kmain(uint32_t magic, struct multiboot_info* bootInfo){

    printf("Loading drivers...\n");

    initGdt();
    print("GDT is done!\r\n");

    initIdt();
    print("IDT is done!\r\n");

    initTimer();
    print("Timers are done!\r\n");

    initKeyboard();
    print("Keyboard is done!\r\n");
    //initialize drivers

    print("All drivers successfully initialized!!!\n\n");

    greet();

    shell_init(bootInfo);
    //initialize the shell
    

    for(;;);
    //hang the OS indefinitely
}
