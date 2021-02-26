# AVR Hardware Abstraction Layer Project proposal 

## Team members: Adi Ramachandran | CA: Manu Patil | Prof: Steve Matsumoto

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

[System Function & breakdown Miro board](system_miro.png)

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