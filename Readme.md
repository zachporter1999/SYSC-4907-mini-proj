
# Table of Contents

1.  [What is libserial](#org751db20)
    1.  [Currently Implemented Drivers](#org0aaf07e)
2.  [Setup Instructions](#org8c82d68)
    1.  [Setting up the include path](#org3192872)
    2.  [Linking the library](#orga652994)



<a id="org751db20"></a>

# What is libserial

Libserial was formerly Team 1&rsquo;s mini project that has now been adapted into a serial communication libray for use in your programs. Libserial provides drivers for the 3 communication protocols availables on the KL25Z. Namely UART, I2C, and SPI. Libserial should allow for easy implementation of these protocols without reinventing the wheel.

Libserial is a Keil project that is set to produce a static library instead of an executable. This should allow for easier implementation into your different programs without having to copy files around.


<a id="org0aaf07e"></a>

## Currently Implemented Drivers

-   [ ] UART
-   [ ] I2C
-   [ ] SPI


<a id="org8c82d68"></a>

# Setup Instructions

The setup instructions assume you have an existing project you wish to implement serial communication in.


<a id="org3192872"></a>

## Setting up the include path

1.  Clone this repository to your computer. (`git clone https://github.com/zachporter1999/SYSC-4907-mini-proj.git`)
2.  Open the library project and build it.
3.  In your existing project, under &ldquo;`Options for Target 1 >> C/C++ (AC6) >> Include Paths`&rdquo; add the ralative path to the &ldquo;`libserial//inc`&rdquo; diretory

![img](./Documentation/out/setup/inc.png "Where to set the &ldquo;*Include Paths*&rdquo; setting.")


<a id="orga652994"></a>

## Linking the library

1.  In the project window at the left side of the Keil IDE, right click on the &ldquo;`Target 1`&rdquo; folder and add a new group.
2.  Rename this new group/folder to lib.
3.  right click on the &ldquo;`lib`&rdquo; folder, add existing item, and add the &ldquo;`libserial//Objects//libserial.lib`&rdquo;

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

