
# Table of Contents

1.  [What is libserial](#org91a826c)
    1.  [Currently Implemented Drivers](#org855e3eb)
2.  [Setup Instructions](#org350f30a)
    1.  [Libserial install and build](#orga422d7d)
    2.  [Setting up the include path to libserial&rsquo;s headers](#orgde03789)
    3.  [Linking the libserial to project](#org4627552)
    4.  [Using libserial drivers in your program](#org4bf1f84)



<a id="org91a826c"></a>

# What is libserial

Libserial was formerly Team 1&rsquo;s mini project that has now been adapted into a serial communication libray for use in your programs. Libserial provides drivers for the 3 communication protocols availables on the KL25Z. Namely UART, I2C, and SPI. Libserial should allow for easy implementation of these protocols without the need to reinventi the wheel again.

Libserial is a Keil project that is set to produce a static library instead of an executable. This should allow for easier implementation into your different programs without having to copy files around.


<a id="org855e3eb"></a>

## Currently Implemented Drivers

-   [X] UART
-   [ ] I2C
-   [ ] SPI


<a id="org350f30a"></a>

# Setup Instructions

The setup instructions assume you have an existing project you wish to implement serial communication in.


<a id="orga422d7d"></a>

## Libserial install and build

1.  Clone this repository to your computer. (`git clone https://github.com/zachporter1999/SYSC-4907-mini-proj.git`)
2.  Open the library project and build it.

The Library setup is finished. Now lets setup your existing Keil to link this library in at compile time.


<a id="orgde03789"></a>

## Setting up the include path to libserial&rsquo;s headers

1.  In your existing project, under &ldquo;`Options for Target 1 >> C/C++ (AC6) >> Include Paths`&rdquo; add the ralative path to the &ldquo;`libserial//inc`&rdquo; diretory

![img](./Documentation/out/setup/inc.png "Where to set the &ldquo;*Include Paths*&rdquo; setting.")


<a id="org4627552"></a>

## Linking the libserial to project

1.  In the project window at the left side of the Keil IDE, right click on the &ldquo;`Target 1`&rdquo; folder and add a new group.
2.  Rename this new group/folder to lib.
3.  right click on the &ldquo;`lib`&rdquo; folder, add existing item, and add the &ldquo;`libserial//Objects//libserial.lib`&rdquo;

![img](./Documentation/out/setup/lib.png "Where to create the &ldquo;*lib*&rdquo; folder to add the &ldquo;*.lib*&rdquo; file to.")


<a id="org4bf1f84"></a>

## Using libserial drivers in your program

In order to use this library in your code you will need to include the appropriate header files.

    #include <MKL25Z.h>
    
    // Include libserial headers
    #include "drivers/uart.h"
    #include "drivers/i2c.h"
    #include "drivers/spi.h"
    
    int main() {
    
      // Main code here
    
    }

