//Receive string example for SLIC.
//Created by Nikhil M Jeby
//https://github.com/solid-droid
/////////////////////////////////////////////////////////////////////

#include "SLIC.h"
slic port(8);         // define a GPIO pin
void setup() 
{
  Serial.begin(9600); 
  Serial.println("start");
}

void loop() 
{
port.read_if_available();           //reads date if available on the pin.
if(port.buff_exist)                 // If data is received buff_exist turns HIGH.
Serial.println(port.get_string());  // get_string() returns received string (data type: String) 
                                    //and sets buff_exist to LOW
}

