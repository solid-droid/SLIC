#include "SLIC.h"
slic::slic(int p)
{
    pin = p;
}
//master
void slic::write_dat(char s[], int size_of)
{
    pinMode(pin, OUTPUT);
    bool dat[8];
    int ascii;
    ascii = size_of;
    for (int j = 7; j >= 0; --j) {
        dat[j] = ascii % 2;
        ascii /= 2;
    }
    enable_listen();
    send_dat(dat);

    for (int i = 0; i < size_of - 1; ++i) {
        ascii = s[i];
        for (int j = 7; j >= 0; --j) {
            dat[j] = ascii % 2;
            ascii /= 2;
        }
        send_dat(dat);
    }
}

void slic::send_dat(bool val[])
{
    digitalWrite(pin, HIGH);
    delay(2);
    for (int j = 0; j < 8; ++j) {
        data(val[j]);
    }
    digitalWrite(pin, LOW);
    delay(50);
}
void slic::data(bool val)
{

    int dd = 1;
    if (val == 1)
        dd = 2;
    digitalWrite(pin, LOW);
    delayMicroseconds(dd * 50);
    digitalWrite(pin, HIGH);
    delayMicroseconds(50);
}

void slic::enable_listen()
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    delay(2);
    data(1);
    data(1);
    data(1);
    data(0);
    data(0);
    data(1);
    data(1);
    data(1);
    digitalWrite(pin, LOW);
    delay(50);
}

void slic::sync_out()
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    delay(2);
    data(1);
    data(0);
    data(1);
    data(0);
    data(1);
    data(0);
    data(1);
    data(0);
    digitalWrite(pin, LOW);
    delay(50);
}
//////////////////////////////////////////////
//Slave
void slic::print_dat()
{
    int ascii = 0;
    int val = 1;
    char temp;
    for (int i = 8; i >= 0; --i, val *= 2) {
        buff_exist = LOW;
        ascii += buf[i] * val;
    }
    if (type == LOW) {
        output = "";
        switch (ascii) {
        case 231:
            sz = HIGH;
            type = HIGH;
            break;
        }
    }
    else if (sz == HIGH) {
        sz_lmt = ascii;
        get_dat = HIGH;
        sz = LOW;
    }
    else if (get_dat == HIGH) {
        temp = ascii;
        output += temp;
        if (sz_lmt > 2) {
            sz_lmt--;
        }
        else {

            get_dat = LOW;
            type = LOW;
            buff_exist = HIGH;
        }
    }
}

void slic::read_if_available()
{
    pinMode(pin, INPUT);
    rd = digitalRead(pin);
    if (rd == HIGH) {
        delay(1);
        if (digitalRead(pin) == HIGH) {
            entry = 0;
            read_enable == HIGH;
            read_dat();
        }
        else {
            read_enable == LOW;
        }
    }
}

void slic::read_dat()
{
    pinMode(pin, INPUT);
    bool rep = LOW;
    while (true) {
        rd = digitalRead(pin);
        if (digitalRead(pin) != HIGH) {

            buf[entry] += 1;
            rep = LOW;
        }
        else {
            if (rep == LOW) {
                entry++;
                if (entry > 8) {
                    if (sync_status == HIGH) {
                        arrange();
                        print_dat();
                    }
                    else if (sync_status == LOW) {
                        sync_in();
                        sync_status = HIGH;
                    }
                    break;
                }
                rep = HIGH;
            }
        }
    }
}

void slic::arrange()
{
    for (int i = 0; i < 9; ++i) {
        if (buf[i] > sync_ref)
            buf[i] = 1;
        else
            buf[i] = 0;
    }
}

void slic::sync_in()
{
    sync_ref = 0;
    for (int i = 0; i < 9; ++i)
        sync_ref += buf[i];
    sync_ref /= 8;
    for (int i = 0; i < 9; ++i)
        buf[i] = 0;
}

String slic::get_string()
{
    if (buff_exist == HIGH) {
        buff_exist = LOW;
        return (output);
    }
}
