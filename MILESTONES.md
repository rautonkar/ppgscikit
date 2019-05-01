## Project Description ##
###	Product Features ###

**Provide high level overview of basic features of product.  This should be an executive level summary.**

* Product allows use of OB1203 for creating algorithms on a PC.
* Product allows configuration of OB1203 and streaming of data past configuration.
* The product shall use an MCU with an I2C bus interface, and a UART interface
* Supported MCU to include S1JA and an RL78 S2 Core.
* Product shall create a driver which shall easily interface with linux device driver (SCULL) 

###	Project Goals ###

**Discuss what the benefits of the project are, include not only sales opportunities but also benefits like engineering knowledge enhancement, brand awareness**

* Provide a command line interface to/from MCU.
* Command line interface has a help section listing all commands available.
* Provides a command to change local volatile definition of OB1203 configuration.
* Provides a command to load local volatile configuration into OB1203 registers.
* Provides a command to read configuration registers of OB1203 into local configuration on MCU.

* Provides a command to start streaming OB1203 FIFO data in CSV format.
* Commands sent to MCU are stored in non-volatile memory.
* Commands stored in MCU are executed upon reset.
* Command line options program the OB1203 configuration registers.
* Provides a state machine driver and interface to OB1203.
* State machine driver and interface shall be compliant with latest GSCE standards.
* State machine driver and interface shall be easily portable to other hardware platforms
* State machine driver and interface will have three modes of operation: Proximity Sensor, Ambient Light Sensor, and PPG Sensor
