#include "stdint.h"
#include "util.h"
#include "interrupts/idt.h"
#include "vga.h"
#include "timer.h"

uint64_t ticks;
const uint32_t freq = 100;
// we have selected 100Hz as the interrupt frequency here
// as is implemented below, the IRQ0 will fire at 100 times a second

uint64_t getTicks(){
    return ticks;
}

uint32_t getFreq(){
    return freq;
}

void onIrq0(struct InterruptRegisters *regs){
    ticks += 1;
}

void initTimer(){
    ticks = 0;
    irq_install_handler(0,&onIrq0);

    //PIT frequency is 119318.16666 Mhz
    //we will divide this by 'freq' to get the interrupts at a required frequency
    uint32_t divisor = 1193180/freq;

    //0011 0110
    //the above binary maps to the following
    //Bits 6-7: 00 -> Select channel 0
    //Bits 4-5: 11 -> Access mode: lobyte/hibyte
    //Bits 1-3: 011 -> Mode 3 (square wave generator)
    //Bit 0: 0 -> Binary counting
    outPortB(0x43,0x36);
    outPortB(0x40,(uint8_t)(divisor & 0xFF));
    outPortB(0x40,(uint8_t)((divisor >> 8) & 0xFF));
    //the above set of data selects the PIT command port and writes the necessary
    //data into it
    //learn more @ https://wiki.osdev.org/Programmable_Interval_Timer
}
