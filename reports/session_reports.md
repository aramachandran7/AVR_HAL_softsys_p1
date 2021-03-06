
## Docs on meetings with Manu

**session 5**

*questions*
- UART data API design 
    - how do we use it for sending data on telemetry? 
    - how do we use it for sending text back to terminal? 
        - do we write a library for this? 
    - what belongs to state?  
        - seperate data-in and data-out flag?
        - 


- DATA API DESIGN: 
    - recognize that a single clean DATA API can be shared between SPI, UART, I2C, even CAN, ADC
        - is this too much abstraction lol 
    - we need a good way to create structures / allocate space + data type based on user preference, probably not within the state struct but where?
    - we use an enum to indicate what type of data 
        - is it a good idea to exert this level of control over how users interface with data? 
- 

*answers*

*todo*
- building + flashing test
- complete libraries + drivers for ADC 
- complete libraries + drivers for UART 
- write basic blinky libs 

**session 4**

*questions*
- timer ISR code could be cleaned up it's soooo nasty
- smartest way to implement runtime error handling (error bit / interrupt of different peripherals)? 
    - implement error display / LED flash library? 
    - check for error diagnosis bit (or dedicated byte) within state? 
- buildchain questions? 
    - use avr-gcc to compile deps or just gcc 
    - header file deps? 
    - why doens't `make` straight work? 
- what about the enviornment var header file? Does each directory have its own, how do the drivers know which Env constants file to pull in? 
- toolchain switching for STM32?? 
- UART driver + lib 
    - clear data in registers for UART? 
- env constants file 
- line 11-14 of timer_library.c

*answers*
- use relative paths 


*todo*
- timer reset 
- uart driver + lib + data handling 
- so much debugging holy shit
- update relative paths for header files


**session 3**

*questions*
- high level questions: 
    - where do we define the state and state update functions so that we can reuse code but also avoid importing library in the driver? It has to be written in and imported from driver right? 
- types of vars to pass into low level API 
    - uint8_t vs int8_t vs otherwise? shouldn't matter right?
- state API `get_state()` return? 
- check first ISR
- include ISR in header file? 
- does `MAX_AVR_TIMERS` need to just be MAX_TIMERS? 
- worth implementing a reset timer function? 


- what about updating state from ISR? 

*answers*
- probably implement state and state managmenet at a library level 
    - libraries update and maintain state
    - State structs can be specific to MCU type 
- universalize the initialization (of things like timers) with register settings stored in .h files for timer1 vs timer0
- uint8_t
- hooks
- split getstate into 2 operations

*todo*
- 16 bit support for timer1
- change state API get and set bit 
- change to uint8_t where possible
- set 1 timer from another full vertical prototype
- telemetry code 
- change caps enum types

**session 2**

*questions*

- init_process()? 
- where to define state + usage of extern within state
- how to convey optional extra modes cleanly+ memory smart
- use bitfield for state? 
- create an env constants header file for each file? 
    - is there a better way to store this data? 
    - is this the right way? `#include "../examples/ENV_CONSTANTS.h"` in every driver and lib file? 
- with some libs like timer, redundant inits - like raw, process, enum? 
- especially for simple libraries like timer where there's no I/O
- where do we define the interrupt function? 
- where do we define 

*answers*
- bitfields could certianly work, its a knowledge barrier for our team
- for certain cases we call other functions
- single access point function, all other functions call it for low level API
- array of pointer to timer structs <-- reduction of code duplication  
- eliminate in_use 
- https://stackoverflow.com/questions/14633987/how-can-i-force-a-compile-error-in-c
- state management API exposed publicly for getting not setting, declared above defined below 



Need to have / work on: 
- trace data flow with diagram
- add `ENV_CONSTANTS` to every low level driver 
- cleaner state management 
- state definition: 
    - dump in_use 
    - add enum 
    - add interrupt set bit(s)
- state API 
    - add state update fn 
    - add state expose fn
- write single entry point API 
- write timer ISR





**session 1**

*questions*

- Class structure with referencable attributes - 
    - How do we convey that a certain timer is in use (with minimal memory usage), so we don't overwrite previous settings? 
        - do we do that with registers? 
    - What about usage error handling? If a user desires a frequency that doesn't work with our prescalers how do we indicate that to them?   
- Consider usage of UART and timer simultaneously, where user inits uart before initing timer 
- do we store feature modes of operation as ints, enums etc? 
    - is there a benefit to one way or another? 
- how much does our code lock us in right now? How should our general driver structure change in the future? 

*answers*
- use enums 
- use state structs for every driver 
- interact with those state structs to perform checks from a library level 
- header files
- assume perfect usage rn

### some old junk ideas + observations 

**Ideas**

- Drivers are `stupid` and the libraries are smart. The libraries include the logic on how to implement the drivers correctly
Think of the drivers as an internal interface that should hardly ever be exposed to the outside (you can use at your own risk.) 
- So libraries check for certain registers for usage of items, and call the necessary driver functions. They provide the enum typing and return the appropriate error statements. 

- We should also enable the ability for libraries to interface with different driver types (chip-specific, or software drivers for simulation, etc)

**Notes / observations**

- Writing the drivers will be easy but the libraries will be harder because we need to understand all usage cases for each the MCU features
- There should be great docs for the libraries but driver docs can be sparse. 
