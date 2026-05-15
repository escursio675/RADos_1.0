#include "help.h"
#include "../vga.h"

void help(){
    print("\nWelcome to RADos! The Commands List is:\r\n");
    print("\nhelp\tprint the Commands List(Hint: You are using it right now :)");
    print("\nuptime\tgenerate the uptime since last boot up in seconds");
    print("\nclear\tclear the text off of the screen");
    print("\ngreet\tgenerate a message from the developers");
    print("\nhexdump\tshow memory information");
}