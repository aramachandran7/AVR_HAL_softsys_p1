#ifndef ENV_CONSTANTS_H
#define ENV_CONSTANTS_H

/*
to be imported by the every example file and used 

*/

/*  Defines  */
#define FCLK int32_t 4000000

typedef enum mcu_type { STM, AVR, SOFTWARE } mcu_type; 

mcu_type MCU = AVR; 

#endif