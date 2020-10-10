#include<reg51.h>

sbit doorp = P2 ^ 0;
sbit doorn = P2 ^ 1;
sbit rs = P2 ^ 5;
sbit rw = P2 ^ 6;
sbit en = P2 ^ 7;

void lcddat(unsigned char);
void lcdcmd(unsigned char);
void lcddis(unsigned char * );
void lcd_init();
void serial_init();
void check();
void delay();
void mdelay();
unsigned char rfid[10], v1;

void main() {
  doorp = doorn = 0;
  serial_init();
  lcd_init();
  lcddis("RFID BASED CAR");
  lcdcmd(0xc0);
  lcddis("PARKING SYSTEM");
  mdelay();
  lcdcmd(0x01);
  while (1) {
    lcdcmd(0x01);
    lcddis("SWIPE YOUR CARD");
		
    for (v1 = 0; v1 < 10; v1++) {
      while (RI == 0);
      rfid[v1] = SBUF;
			SBUF = 0;
      RI = 0;
      while (TI == 0);
      TI = 0;
    }
    check();
  }
}

void check() {

  //1712345642 - GOLAM SLOT
  //1711080042 - AZIZ SLOT
  //1813198642 - TASNIMUL SLOT		
  //1711153042 - ARIF SLOT

  if (rfid[0] == '1' && rfid[1] == '7' && rfid[2] == '1' && rfid[3] == '2' && rfid[4] == '3' &&
    rfid[5] == '4' && rfid[6] == '5' && rfid[7] == '6' && rfid[8] == '4' && rfid[9] == '2') {
    lcdcmd(0x01);
    lcddis("HOUSING MEMBER");
    lcdcmd(0xc0);
    lcddis("GOLAM- FLAT 101");
    mdelay();
    lcdcmd(0x01);
    doorp = 1;
    doorn = 0;
    lcddis("DOOR OPENING");
    lcdcmd(0xc0);
    lcddis("ALLOW INSIDE");
		mdelay();
    doorp = 0;
    doorn = 0;
    delay();
    lcdcmd(0x01);
    doorp = 0;
    doorn = 1;
    lcddis("DOOR CLOSING");
    mdelay();
    doorp = 0;
    doorn = 0;
  } 
		else if (rfid[0] == '1' && rfid[1] == '7' && rfid[2] == '1' && rfid[3] == '1' && rfid[4] == '0' &&
    rfid[5] == '8' && rfid[6] == '0' && rfid[7] == '0' && rfid[8] == '4' && rfid[9] == '2') {
    lcdcmd(0x01);
    lcddis("HOUSING MEMBER");
    lcdcmd(0xc0);
    lcddis("AZIZ- FLAT 105");
    mdelay();
    lcdcmd(0x01);
    doorp = 1;
    doorn = 0;
    lcddis("DOOR OPENING");
    lcdcmd(0xc0);
    lcddis("ALLOW INSIDE");
    mdelay();
    doorp = 0;
    doorn = 0;
    delay();
    lcdcmd(0x01);
    doorp = 0;
    doorn = 1;
    lcddis("DOOR CLOSING");
    mdelay();
    doorp = 0;
    doorn = 0;
  } 
		else if (rfid[0] == '1' && rfid[1] == '8' && rfid[2] == '1' && rfid[3] == '3' && rfid[4] == '1' &&
    rfid[5] == '9' && rfid[6] == '8' && rfid[7] == '6' && rfid[8] == '4' && rfid[9] == '2') {
    lcdcmd(0x01);
    lcddis("HOUSING MEMBER");
    lcdcmd(0xc0);
    lcddis("TASNIMUL- FLAT 405");  
    mdelay();
    lcdcmd(0x01);
    doorp = 1;
    doorn = 0;
    lcddis("DOOR OPENING");
    lcdcmd(0xc0);
    lcddis("ALLOW INSIDE");
    mdelay();
    doorp = 0;
    doorn = 0;
    delay();
    lcdcmd(0x01);
    doorp = 0;
    doorn = 1;
    lcddis("DOOR CLOSING");
    mdelay();
    lcddis("DOOR CLOSING");
    mdelay();
    doorp = 0;
    doorn = 0;
  } 
		else if (rfid[0] == '1' && rfid[1] == '7' && rfid[2] == '1' && rfid[3] == '1' && rfid[4] == '1' &&
    rfid[5] == '5' && rfid[6] == '3' && rfid[7] == '0' && rfid[8] == '4' && rfid[9] == '2') {
    lcdcmd(0x01);
    lcddis("HOUSING MEMBER");
    lcdcmd(0xc0);
    lcddis("ARIF- SLOT 103");
    mdelay();
    lcdcmd(0x01);
    doorp = 1;
    doorn = 0;
    lcddis("DOOR OPENING");
    lcdcmd(0xc0);
    lcddis("ALLOW INSIDE");
    mdelay();
    doorp = 0;
    doorn = 0;
    delay();
    lcdcmd(0x01);
    doorp = 0;
    doorn = 1;
    lcddis("DOOR CLOSING");
    mdelay();
    doorp = 0;
    doorn = 0;
  } 
		else {
    lcdcmd(0x01);
    lcddis("OUTSIDE PERSON");
    lcdcmd(0xc0);
    lcddis("NO SLOT FOR YOU");
    mdelay();
  }
}

void lcd_init() {
  lcdcmd(0x38);
  lcdcmd(0x01);
  lcdcmd(0x10);
  lcdcmd(0x0c);
  lcdcmd(0x80);
}

void lcdcmd(unsigned char val) {
  P1 = val;
  rs = 0;
  rw = 0;
  en = 1;
  delay();
  en = 0;
}

void lcddat(unsigned char val) {
  P1 = val;
  rs = 1;
  rw = 0;
  en = 1;
  delay();
  en = 0;
}

void delay() {
  unsigned int v5;
  for (v5 = 0; v5 < 6000; v5++);
}

void lcddis(unsigned char * s) {
  unsigned char w;
  for (w = 0; s[w] != '\0'; w++) {
    lcddat(s[w]);
  }
}

void serial_init() {
  SCON = 0X50;
  TMOD = 0X20;
  TH1 = 0XFD;
  TR1 = 1;
	
}

void mdelay() {
  unsigned int v6, v7;
  for (v6 = 0; v6 < 2; v6++) {
    for (v7 = 0; v7 < 60000; v7++);
  }
}