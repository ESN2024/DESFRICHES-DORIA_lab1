#include "system.h"
#include "sys/alt_stdio.h"
#include "alt_types.h"
#include "io.h"
#include <stdlib.h>
#include <unistd.h>
#include "altera_avalon_pio_regs.h"

#define DELAI 1000000

int main()
{
    //allumage d'une led à la fois
    while(1)
    {
        for (__uint8_t i=0; i<8; i++)
        {
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, 1 << i);
            usleep(DELAI);
        }
    }
    
}
