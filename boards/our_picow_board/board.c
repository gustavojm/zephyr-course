#include <zephyr/init.h>
#include <zephyr/kernel.h>


/* Initialize drivers or something related to the board */
static int board_our_picow_board_init(void) {    
    printk("*************** INIT FROM MY BOARD *************** \n");
    return 0;
}

SYS_INIT(board_our_picow_board_init, PRE_KERNEL_2,
	 CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
