//Transmit string example for SLIC.
//Created by Nikhil M Jeby
//https://github.com/solid-droid
/////////////////////////////////////////////////////////////////////

#include "SLIC.h"
slic port(8);            // define a GPIO port
char s[]="hello world";  // String to transmit, don’t use String data type.
int ss;                  // Integer to store string size
void setup() 
{
port.sync_out();        // Sends out synching information. (One time only, on start up of receivers)
 ss=sizeof(s);          // Size of the string.
port.write_dat(s,ss);   // Transmit string data (string, string size)
  
}

void loop() 
{

}







