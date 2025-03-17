#include "crosstable.h"
#include "automation.h"

/* put here the initalization */
void setup(void)
{
    // Wait PLC Engine gets ready
    while (PLC_EngineStatus < 2) {
        fputc('*', stderr);
        sleep(1);
    }
    // TPX4120 FastIO Configuration
    doWrite_PLC_FastIO_Ena(0x000000FF);
    doWrite_PLC_FastIO_Dir(0x000000F0);
    // Insert your start-up code here
    // .....
}

/* put here the operation made every 100ms */
void loop(void)
{

}


