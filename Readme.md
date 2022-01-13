
# Table of Contents

1.  [Purpose](#org5e14745)
    1.  [Currently Implemented Drivers](#org2df7f93)
2.  [Setup Instructions](#orgfff6924)



<a id="org5e14745"></a>

# Purpose

This serial communication library, formerly Team 1&rsquo;s mini project, is intended to provide a easy to implement interface to interact with UART, I2C, and SPI devices.


<a id="org2df7f93"></a>

## Currently Implemented Drivers

-   [ ] UART
-   [ ] I2C
-   [ ] SPI


<a id="orgfff6924"></a>

# Setup Instructions

The setup instructions assume you have an existing project you wish to implement serial communication in.

1.  Clone this repository to your computer. (`git clone https://github.com/zachporter1999/SYSC-4907-mini-proj.git`)
2.  Open the library project and build it.
3.  In your existing project, under &ldquo;`Options for Target 1 >> C/C++ (AC6) >> Include Paths`&rdquo; add the ralative path to the &ldquo;`libserial//inc`&rdquo; diretory

![img](./Documentation/out/setup/inc.png "Where to set the &ldquo;*Include Paths*&rdquo; setting.")

4.  In the project window at the left side of the Keil IDE, right click on the &ldquo;`Target 1`&rdquo; folder and add a new group.
5.  Rename this new group/folder to lib.
6.  right click on the &ldquo;`lib`&rdquo; folder, add existing item, and add the &ldquo;`libserial//Objects//libserial.lib`&rdquo;

![img](./Documentation/out/setup/lib.png "Where to create the &ldquo;*lib*&rdquo; folder to add the &ldquo;*.lib*&rdquo; file to.")

In order to use this library in your code you will need to include the appropriate header files.

    #include <MKL25Z.h>
    
    // Include libserial headers
    #include "drivers/uart.h"
    #include "drivers/i2c.h"
    #include "drivers/spi.h"
    
    int main() {
    
      // Main code here
    
    }

