#include "stdint.h"
#include "util.h"

void memset(void *dest, char val, uint32_t count){
    char *temp = (char*) dest;
    for (; count != 0; count --){
        *temp++ = val;
    }

}
//set the memory starting from address "dest" to "val"
//"count" number of times

void outPortB(uint16_t Port, uint8_t Value){
    asm volatile ("outb %1, %0" : : "dN" (Port), "a" (Value));
}
//function to write a byte of value into the port specified by "Port"
//dN->write to the dx register, a->write to the ax register
//volatile is used to ensure the compiler does not "optimize" this statement

char inPortB(uint16_t port){
    char rv;
    asm volatile("inb %1, %0" : "=a"(rv):"dN"(port));
    return rv;
}
//recieve a byte input from the input port "port"

//rv is the character we are writing to and is port the port we are reading from
//therfore the program reads from the port in the argument and returns rv which is the character read

int strcmp(const char* a, const char* b){

    while(*a && *b){

        if(*a != *b){
            return *a - *b;
        }

        a++;
        b++;
    }

    return *a - *b;
}
//compare two strings by returning the difference in their characters
