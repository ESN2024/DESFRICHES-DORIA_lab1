#include "system.h"
#include "sys/alt_stdio.h"
#include "alt_types.h"
#include "io.h"
#include <stdlib.h>
#include <unistd.h>
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"

#define DELAI 30000

volatile __uint8_t cadence;
volatile __uint8_t led = 0x01;

static void irqhandler_bp_key1(void* context, alt_u32 id)
{
    while(led!=0x80)
    {
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, led);
        usleep(DELAI/cadence);
        led = led << 1;
    }
    led = 0x01;
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0x01); //RAZ
}

static void irqhandler_switchs(void* context, alt_u32 id)
{
    cadence = IORD_ALTERA_AVALON_PIO_DATA(PIO_2_BASE)+1;
    alt_printf("Combinaison = %x\n", IORD_ALTERA_AVALON_PIO_DATA(PIO_2_BASE));
    alt_printf("Cadence = %x\n", cadence);

    //RAZ
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_2_BASE, 0x0F);
}

int main()
{
    //allumage d'une led à la fois
    alt_printf("Exec main()\n");

    //Configuration du bp key 1
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE, 0x01);
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0x01); //Enable interrupt

    //Configuration des switches
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_2_BASE, 0x0F); // Les 4 premiers switchs uniquement
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_2_BASE, 0x0F); // 
    //ISR Registration
    alt_irq_register(PIO_1_IRQ, NULL, irqhandler_bp_key1);
    alt_irq_register(PIO_2_IRQ, NULL, irqhandler_switchs);

    while(1)
    {}
    
}