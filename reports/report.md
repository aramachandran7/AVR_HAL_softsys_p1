# AVR+ Hardware Abstraction Layer for Formula Vehicle Firmware

#### Team members: Adi Ramachandran | Course Assistant: Manu Patil | Prof: Steve Matsumoto

#### Background & Intentions

The objective of this project is to build a proof of concept for a hardware abstraction layer (HAL) interface for our Formula vehicle's firmware. The [current revision](https://drive.google.com/file/d/1YjOPOfT_ilDgR61rJebSrrztOiRnLg4-/view) of our Formula SAE electric vehicle has over 14 custom-designed printed circuit boards (PCB's), each handling some function of the car's performance. All of these PCB's use the [Atmega16m1](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7647-Automotive-Microcontrollers-ATmega16M1-32M1-64M1-32C1-64C1_datasheet.pdf) microcontroller (MCU), an automotive MCU based on an AVR chip architecture. Each of these PCB's runs chip-specific [firmware](https://github.com/olin-electric-motorsports/mkv-code) with the large amounts of shared register level code. 

The intention of this project is to build out an abstraction layer that virtualizes the low and register level code required to interface with MCU peripherals in a clean and intuitive interface. Beyond just an AVR HAL, we also designed our interface to be chip agnostic, in the case where our team decides to upgrade our selection of MCU to a chip like the STM32. 

#### What I did

To demonstrate a proof of concept for this system, I built 2 full AVR peripheral 'vertical stacks', for the UART peripheral and the timer peripheral, and wrote 2 simple peices of firmware `timer_sample.c` and `UART_sample.c` to test both 'verticals'. 

For context, a peripheral vertical stack includes a driver layer interface (that is chip architecture specific) along with a library layer interface (that is chip architecture agnostic), all for a single microcontroller peripheral. This could be a timer, an ADC (analog digital converter), the UART interface, LIN interface, etc. 

Here's an example of the simplified timer interface. 

```
|firmware| -->calls--> |timer_library|-->calls-->|timer_driver|
```

The end user / firmware engineer can simply import the required libraries and a constants file, and call functions within the intuitive library layer interace. 

#### Learning Goals

My learning goals were to get more comfortable with writing AVR firmware, understand the required use cases of fimrware on our Formula SAE team in order to build a set of intuitive API's that meets the team's needs, and get comfortable thinking about embedded system library architecture. 

#### Resources used

I've consulted heavily with Manu Patil, the course teaching assistant, to build this project in a way that will be useful for our Formula team in the long term. Manu has been an amazing resource over the course of this project. 

- For development of the Atmega16m1 drivers, I referenced the [datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/) heavily
- For development of the build system to compile and flash the firmware, this was a [great reference](https://gist.github.com/edwardhotchkiss/9378977)
- For referencing interrupts & interrupt vector names used this [webpage](http://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html) 

#### Major Design Decisions & Code

This entire project revolved around architectural decisions with the library interface, driver interface, etc. Here's just a few, presented as design questions/insights, and then as the  solutions. 

| Critical Design Question / Insight                                                                                                                                                                                                                   | Decision                                                                                                                                                                                                                                                                                                              |
|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Each MCU peripheral is initialized by the end user with some intended use.  Most MCU peripherals share operating modes and some fundamental data about their operation (like operating frequency or interrupt flags; this is largely chip agnostic.  | For every peripheral, define a state structure, that contains information about  the current operating mode of that state + other relevant information.                                                                                                                                                               |
| There exist `N` nearly identical peripherals supported by a single MCU. i.e. the Atmega16m1 has 2 timers, timer0 and timer1, whose behaviors are defined  by a different set of registers but otherwise are the same. *                              | Initialize an array of pointers to state structs, with the position in the array  referencing which peripheral out of `N` we are using.                                                                                                                                                                               |
| We only want state to be changed by at the driver level. The end user should  never directly be altering state, only referencing it, to do something like  check and clear the value of an interrupt flag.                                           | House the state API's at the lowest level of the 'vertical' - within the drivers. (Define the structs in the header file, write the API itself in the C files)  Ensure to only publicly expose the state access API and not the state change API. **                                                                  |
| To initialize a peripheral, we set registers based on a selection between  a finite set of operating modes for each peripheral.  Users may want to set the registers to custom values, or they may be inclined  to use our API.                      | At the driver level, we should define a high level `init()` function that invokes a  low level `raw_init()` function. Both functions will be exposed to the end user.  At the library level we can chip agnostic init() function that will call the                                                                   |
| The complexity of the build chain is affected by the need to support multiple different MCU's.                                                                                                                                                       | For the time being, we use a hand written `Make` file with `AVR-GCC` and  `avrdude` to compile and flash our code. Looking forwards, we are considering  more configurable alternatives to `Make` like `Bazel`, that would allow us to  automatically hot swap between an STM buildchain and an AVR one, for example. |
| General dependency management is also made more challenging by supporting multiple  MCU's. At a library level, importing drivers for different MCU's with overlapping API function names gets complicated.                                           | Currently, we only have verticals for the AVR. In the future, we will utilize  preprocessor includes extensively within all our import statements to only include and ultimatley compile the absolutely necessary header files required for our project based on our MCU.                                             |


*The `timer0` and `timer1` are also an 8 bit and 16 bit timer respectively. 
**This leads to some challenges down the line covered here: 
- How do we ensure state code won't be duplicated between different chip architectures (STM vs Atmega16m1)?
- If there are multiple very similar state API functions shared across different peripherals, how do we write that code only once in a state type agnostic manner, without severely increasing project complexity? 
    - Highly applicable to a function like `check_bit_and_clear_if_set()`, which is referring to a bit within a flag byte within the a timer state struct - but is truly applicable to all state structs that use flags. 

For some context, here's how we define the `timer0` state struct and array (in `AVR_timer_driver.h`), and below are the two functions that make up our public timer state API, in `AVR_timer_driver.c`. 

```
typedef struct {
    timer_output_mode timer_mode; 
    volatile uint8_t timer_flag; 
} timer_state_struct; 

timer_state_struct * UNIVERSAL_TIMER_STATE[MAX_AVR_TIMERS];  
```

```
timer_output_mode get_mode_timer(timer_state_struct * timer_state){
    return (*timer_state).timer_mode; // TODO: how do we return a copy that can't be edited? 
}

uint8_t check_bit_and_clear_if_set(short timer_num, uint8_t bit_to_check){
    // access bit 
    timer_state_struct * timer_state = UNIVERSAL_TIMER_STATE[timer_num]; 
    
    if (bit_is_set((*timer_state).timer_flag, bit_to_check)){
        // flip bit now
        (*timer_state).timer_flag &= ~_BV(bit_to_check); 
        return 1; 
    } else {
        return 0; 
    }
}
```

And lastly, to see our AVR HAL at work, check out this sample code. Excluding include statements and comments, the code takes only 20 lines to implement a timer incremented variable, sent out via UART at a baudrate of 9600 Hz. Clean, right?

```
mcu_type MCU = ATMEGA16M1; 

uint16_t freq_timer_1 = 20; 

int main(void){
    init_timer(0, CTC_MODE, freq_timer_1, 0); 
    init_UART(FULL_DUPLEX, STANDARD_8N1, 9600, 0); 

    uint8_t increment_var = 0; 

    while (1)
    {
        send_UART_from_first_byte(0); 
        if (check_bit_and_clear_if_set(0, TIMER_FLAG_CMP_A)){
            increment_var = (increment_var + 1) % 255; 
            data_RX_buffer[0] = increment_var; 
        }
    }
}
```

#### Reflection 
Overall, the project ended up on the lower bound of the goals identified in the proposal. The build chain process added development time, and building each vertical is an involved process that takes lots of considerations about usage and lots of datasheet references. 

While it compiled with `AVR-GCC`, I wasn't able to test the sample code provided on an actual Atmega16m1 MCU, because I didn't have access to the hardware - this is something I hope (& need) to do in the near future. 

I definetly achieved my learning goals - in one sense I was nicely exposed to every aspect of the firmware dev process - understanding how our team writes firmware (our general code structure), writing lots of register level code + getting a better understanding of two peripherals, making architectural design decisions, and diving a little into the build chain. 

#### Next steps & Vision for the Future 

I began this project with the intention to make headway, but not even get close to building out its full functionality. The original objective, and what continues to be the long term objective is to build out a general purpose HAL that meets the needs of our vehicle firmware. This is a goal that is both wide and deep - 1 vertical (library, driver, header and c files for both), for each peripheral, for each MCU, need to be supported (wide)- but each peripheral has many operating modes and levels functionality that can be indefinetly built into the API (deep). 

It's all about prioritizing what our Formula team needs. 

*At a high level, two things that should guide future development are:*
- Parallel Development 
    - Parallel development - writing actual firmware using this HAL, and building this HAL out at the same time, is the strongest way to develop the HAL so that it's useful & intuitive for actual development. 
- MCU Support 
    - In general, support for alternative chip architectures should be added as needed. However, adding in the first non-AVR MCU (probably STM) will force a number of design decisions to be made that will affect the addition of future MCU's. 

*These other facets of the project / design decisions need to be seriously considered as well:*
- `ENV_CONSTANTS.h` 
    - Defining some key constants in the ENV file and at the top of every firmware file was another design decison we made, in order to get compilation to work, but there may be a better solution to shared universal enviornmental constants than the `ENV_CONSTANTS.h` file. 
- State APIs
    - As mentioned above, the state API will need to be rewritten for each driver (i.e. the STM timer driver will need a state and state API just like the AVR one). 
        - Having a shared state setup between the same peripheral would be nice. 
    - The state API's in general also share numerous public and private functions like the `check_bit_and_clear_if_set()` function that don't make sense to duplicate between different states.
    - This includes finding a home for state-specific data - like the UART `data_TX_buffer`, and ensuring it can be shared by different MCU drivers.  
- Build chain
    - Upgrade to `Bazel`! `Make` is stopgap and will not work. Not sure about `Make.py`. 
- Use preprocessor directive include statements in all libraries!
    - This is huge! We only have to include and compile the drivers we actually need. 
- Error handling!
    - There needs to be an single library + driver vertical dedicated to error checking and error handling! MCU's expose error registers and checking those registers + visually indicating failures that the hardware automatically detects in the superloop, with a single function call, would be DOPE.
- RTOS suppport!
    - Our team is only 1 advanced firmware project away from incorporating an RTOS firmware structure to one of our boards. More thought needs to be put into writing our API's in a memory aware manner that work well in independent RTOS threads. 
- Generalized test procedures
    - As development of peripherals is picked up by newer members to the team, testing should become a larger focus for each perihperal vertical, and firmware test plans + scripts should be developed. 
    - How do we test that a single peripheral works on its own, and works when used with other peripherals? 
    - How do we 'break' the libraries? What are their explicit / implicit vunerabilities?  
    - Are there limitations on performance we should expect if using any one, or multiple verticals? 
- How does the new CAN library interface with this? 
- Some minor things 
    - Eliminate all usage of `short` and `int8_t`, and replace with `uint8_t` type, for clarity & memory efficiency
    - Add more clear, concise, less profane comments `//gdi, adi`
    - Consider using bitfields instead of flag bytes for clarity and memory efficiency

**However - Testing on actual hardware is the most immediate TODO!** 

Thanks for reading this the whole way through! You get a cookie! 

#### Links 

- [Trello Board](https://trello.com/b/evFEEQDQ/avr-hardware-abstraction-layer)
- [Github](https://github.com/aramachandran7/AVR_HAL_softsys_p1)
