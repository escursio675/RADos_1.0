/* Link.ld -- Linker script for the kernel - ensure everything goes in the */
/*            Correct place.  */
/*            Original file taken from Bran's Kernel Development */
/*            tutorials: http://www.osdever.net/bkerndev/index.php. */

ENTRY(_start)
SECTIONS
{
    . = 0x00100000;
    /* the starting address that the kernel loads into = 1MB
     * everything below this address being reserved for BIOS, VGA etc*/

    .multiboot ALIGN(4K): {
        *(.multiboot)
    }

    .note.gnu.build-id ALIGN(4K): {
        *(.note.gnu.build-id)
    }

    .boot ALIGN(4K) : {
        *(.boot)
    }
    /*low physical memory sections ~1MB
     * consists of the multiboot header which must be present in the first few KBs for GRUB to locate it
     * the .boot code that runs before paging
     * and the 4K byte page alignment boundary*/

    /* note that the x86 paging system requires alignment of pages to 4096 byte memory blocks, ie, 4K bytes
     * this is used to implement different permissions in the different pages*/


	
    . += 0xC0000000;
    /* the higher half, ie, the kernel begins here
     * it occupies ~1GB of virtual memory and is maintained separately from user programs*/

    .text ALIGN(4K): AT(ADDR(.text) - 0xC0000000){
        *(.text)
    }
    /* subtract addr of .text from  0xC0000000 to locate the actual physical address
     * defines the executable code*/



    .rodata ALIGN(4K): AT(ADDR(.rodata) - 0xC0000000){
        *(.rodata)
    }
    /*defines the readonly data section*/

    .data ALIGN(4K): AT(ADDR(.data) - 0xC0000000){
        *(.data)
    }
    /*global variables*/

    .bss ALIGN(4K): AT(ADDR(.bss) - 0xC0000000){
        *(COMMON)
        *(.bss)
    }
    /* uninitialized global variables
     * use COMMON to denote such variables accross multiple object files and merge them here*/

    _kernel_end = .;
    /* symbol for end-of-kernel memory
     * not implemented in the kernel as of yet*/

}
