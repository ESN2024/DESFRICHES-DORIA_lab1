#include "system.h"
#include "sys/alt_stdio.h"
#include "alt_types.h"
#include "io.h"
#include <stdlib.h>
#include <unistd.h>
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"

#define DELAI 70000

volatile int val;

static void irqhandler_bp_key1(void* context, alt_u32 id)
{

    //Enable led chaser
    __uint8_t led = 0x01;
    while(led!=0x80)
    {
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, led);
        usleep(DELAI);
        led = led << 1;
    }
    led = 0x01;
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0x01); //RAZ
}

int main()
{
    //allumage d'une led à la fois
    alt_printf("Exec main()\n");

    //Configuration du bp key 1
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE, 0x01);
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0x01); //Enable interrupt

    //ISR Registration
    alt_irq_register(PIO_1_IRQ, NULL, irqhandler_bp_key1);

    while(1)
    {}
    
}