# AVR_HAL_softsys_p1
The objective of this project is to function as a proof of concept for a new style of systems design oriented - firmware structure for our Formula SAE team. 

It involves building out hardware abstraction drivers for specific microcontrollers and their specific features our team uses (1) and higher level interfacable API's we can call within board firmware (2). 

Reference the project proposal in the `reports` directory to learn more about objectives, learning goals, etc. 

## System Breakdown Diagram 
![Miro board](/reports/system_miro.png)

### Notes, questions, thoughts

**Ideas**

- Drivers are `stupid` and the libraries are smart. The libraries include the logic on how to implement the drivers correctly
Think of the drivers as an internal interface that should hardly ever be exposed to the outside (you can use at your own risk.) 
- So libraries check for certain registers for usage of items, and call the necessary driver functions. They provide the enum typing and return the appropriate error statements. 

- We should also enable the ability for libraries to interface with different driver types (chip-specific, or software drivers for simulation, etc)


**questions**

- Class structure with referencable attributes - 
    - How do we convey that all timers are in use? 
    - How do we check that even 1 timer is in use? 
        - do we do that with registers? 
    - What about usage error handling?  
- Consider usage of UART and timer simultaneously, where user inits uart before initing timer 
- How the hell do we do error handling? Our drivers don't touch that? 
- do we store feature modes of operation as ints, enums etc? 
    - is there a benefit to one way or another? 
- how much does our code lock us in right now? How should our general driver structure change in the future? 

**Notes / observations**

- Writing the drivers will be easy but the libraries will be harder because we need to understand all usage cases for each the MCU features
- There should be great docs for the libraries but driver docs can be sparse. 




### todo
- timer drivers 
- timer interface 
- begin restructure telemetry board firmware
- low frequency (<16 Hz) interrupt with counter in library 

