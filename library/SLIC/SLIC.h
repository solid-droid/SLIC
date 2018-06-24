#ifndef SLIC
#define SLIC
#if (ARDUINO >=100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class slic
{
public:
  slic(int p);
  int sync_ref=10;
  String output;
  boolean sync_status=LOW;
  boolean buff_exist=LOW;
  void write_dat(char s[],int size_of);
  void data(bool val);
  void enable_listen();
  void sync_out();
  void read_if_available();
  void read_dat();
  String get_string();
  
private:
  int sz_lmt=0;
  int pin;
  boolean sz=LOW;
  boolean get_dat=LOW;
  boolean type=LOW;
  bool read_enable=LOW;
  bool rd;
  int buf[9];
  int entry=0;
  void send_dat(bool val[]);
  void print_dat();
  void arrange();
  void sync_in();
    
};


#endif
