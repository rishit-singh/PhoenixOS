#include "terminal.h"
#include "HAL/serial.h"

#include "stdlib.h"
#include "logger.h"
#include "memory/gdt.h"

terminal_t terminal;

extern void load_gdt();

void kernelMain(stivale2_struct_t* bootloader_data)
{
    const char* str = "PhoenixOS!\n";
    
    terminalInitialize(&terminal, bootloader_data);
    terminalWrite(&terminal, str, 11);
    serialInitialize();
    
    load_gdt();
    PH_LOG_TRACE("Hello, %s!", "World");

    char c_standard[20];

    itoa(__STDC_VERSION__, c_standard, 10);
    for (int i = 0; i < 20; i++)
    {
        if (c_standard[i] == '\0') break;
        serialSendb(COM1, c_standard[i]);
    }

    for (;;) PH_ASM("hlt");
}