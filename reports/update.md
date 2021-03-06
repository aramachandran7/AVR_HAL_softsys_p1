# AVR Hardware Abstraction Layer Project 

## Team members: Adi Ramachandran | Course Assistant: Manu Patil | Prof: Steve Matsumoto

The objective of this project is to build a proof of concept for a hardware abstraction layer interface for our Formula team's firmware. 

To demonstrate the proof of concept, as a lower bound I will be building a simple peice of AVR firmware that uses 2 custom written microcontroller peripheral abstraction libraries from top to bottom. The upper bound / stretch goal will be implementing 3 full AVR peripheral 'vertical stacks', including one communication protocol (UART most likely), and writing sample firmware that successfully implements those peripherals via the vertical stacks.

For context, a peripheral vertical stack includes a driver layer interface (that is chip architecture specific) along with a library layer interface (that is chip architecture agnostic), all for a single microcontroller peripheral. This could be a timer, an ADC (analog digital converter), the UART interface, LIN interface, etc. 

The end user / firmware writer can simply import the required libraries and a constants file, call the intuitive library layer interace, and all the fine details (like register level programming) is abstracted away. 

My learning goals are to get more comfortable with writing AVR firmware, understand the required use cases of fimrware on our Formula SAE team in order to build a set of intuitive API's that meets their needs, and get comfortable thinking about embedded system library architecture. 

I've worked heavily with Manu, the course teaching assistant, to build this project in a way that will be useful for our Formula team in the long term. Manu is functionally the best resource for this project, and it's been amazing having him effectively oversee project progress. 

Right now I'm working on finalizing the peripheral vertical for just the Atmega 16m1 timer. This includes a state management API, interrupt handling, and enums for common timer modes. After this, I'll move to building, testing, and flashing a sample peice of firmware that uses just the timer peripheral vertical. And after that, I'll move to updating and completing the ADC and UART drivers and libraries. 

### Links 

- [Trello Board](https://trello.com/b/evFEEQDQ/avr-hardware-abstraction-layer)
- [Github](https://github.com/aramachandran7/AVR_HAL_softsys_p1)


# Proposal 

## Objectives

The objective of this project is to function as a proof of concept for a new style of systems design oriented - firmware structure for our Formula SAE team. It involves building out hardware abstraction drivers for specific microcontrollers and their specific features our team uses (1) and higher level interfacable API's we can call within board firmware (2). 

### Lower bound

I will be working on (1) writing the drivers for at least 3 features - timer, UART, ADC - for the Atmega16M1 microcontroller. 

I'll also design & write the higher level API interfaces (2) for these 3 microcontroller features. 

### Upper bound

Depending on available time, I will work on building out more drivers (1) & libraries (2) and implementing these within certain projects. 

I'll also integrate this project's libraries into actual board firmware - starting with the `telemetry.c` firmware. Will then run tests and observe points of system failure. 


## Learning

Through this project I'm intending to learn more about
- embedded systems development & best practices in general - interrupts, registers, buffers, flags, etc. 
- quality embedded firmware code structure from a systems design perspective - superloops, libraries, passing around interrupts between libaries,
- improve familiarty with basic C syntax - header files, project directory structure

## Getting started

Resources to be used will be this [datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7647-Automotive-Microcontrollers-ATmega16M1-32M1-64M1-32C1-64C1_datasheet.pdf), the rest of the formula team's [firmware](https://github.com/olin-electric-motorsports/mkv-code), and [Manu](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.huffpost.com%2Fentry%2Fwas-jesus-the-son-of-god-_b_7976430&psig=AOvVaw3jVRekuKmiTtUBye-nAQQK&ust=1614457963204000&source=images&cd=vfe&ved=0CAIQjRxqFwoTCOihwuyyiO8CFQAAAAAdAAAAABAD), the software systems CA. 

## First steps

In order to get started, let's start with a system level diagram of what needs to happen and the overall function and library / driver dependency tree. 

![System Function & breakdown Miro board](system_miro.png)

Reference the [Miro board](https://miro.com/welcomeonboard/FOmUawZ5cbtJwrPwp5qxJsDGcSkuQu6xTjJDfAP5yIE8iY9CYdOoj83QGHYZ06f0) to view the complete system diagram, as it's updated. 

From there we'll begin writing the drivers and libraries at the base of the dependency tree and move our way up.

For each feature (i.e. timer, ADC, etc), we'll need to consider how to provide a flexible but easy to understand and well documented interface for the microcontroller features our team uses. This requires referencing our team's firmware and seeing how we typically use certain features. 

Once the required features for the telemetry board are implemented, we'll write the telemetry board firmware using the libraries and drivers and run tests. 


## Forseeable issues
- Passing microcontroller interrupts between libraries and header files
- Cyclic dependencies between feature libraries
- Challenges in setting up hardware based test suite 



## questions 

1) What is the goal of your project; for example, what do you plan to make, and what should it do?  Identify a lower bound you are confident you can achieve and a stretch goal that is more ambitious.

2) What are your learning goals; that is, what do you intend to achieve by working on this project?

3) What do you need to get started?  Have you found the resources you need, do you have a plan to find them, or do you need help?

4) What are your first steps?  Describe at least three concrete tasks that you can do immediately, and identify which member of the team will do them.  For each one, what is the "definition of done"; that is, what will you produce to demonstrate that the task is done?