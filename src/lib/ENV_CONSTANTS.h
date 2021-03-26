#ifndef ENV_CONSTANTS_H
#define ENV_CONSTANTS_H

/*
to be imported by the every example file and used 

*/

/*  Defines  */
#define FCLK 4000000

typedef enum mcu_type { STM, ATMEGA16M1, SOFTWARE } mcu_type; 

mcu_type MCU = ATMEGA16M1; 

#endif