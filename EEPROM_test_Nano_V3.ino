#include <at24c16.h>         // library for EEPROM
at24c16 eeprom(0x50);        // I2C start address = 0x50
/* Global Variables */
int i, j, count;             // counters
int address;                 // EEPROM write address
//---------------------------------------------------------
void setup() {
  eeprom.init();
  Serial.begin(115200);      // set communication speed for the serial monitor
  Menu(); }                  // print the menu first
//---------------------------------------------------------
void loop() {
  while (1) {
    if (Serial.available() > 0) {
      char ch = Serial.read();                        // get user input
      ch == 'm' ? Menu() : Nothing();
      ch == 'h' ? Menu() : Nothing();
      ch == '?' ? Menu() : Nothing();
      ch == 'e' ? EraseEEPROM(ch)    : Nothing();
      ch == 'E' ? EraseEEPROM(ch)    : Nothing();
      ch == 'r' ? ReadEEPROM(ch)     : Nothing();
      ch == 'R' ? ReadEEPROM(ch)     : Nothing();
      ch == 't' ? WriteTextEEPROM()  : Nothing();
      ch == 'x' ? WriteRandomEEPROM(): Nothing(); }
  }
}
//--------------------------------------------------------
void Nothing(){}                                     // does nothing but needed for menu functioning!
//--------------------------------------------------------
void Menu() {
  Serial.println("\tEEPROM 24C16: (m, ? or h for this menu)");
  Serial.println("\tr - Read first 256 addresses");
  Serial.println("\tR - Read entire memory");
  Serial.println("\te - Erase first 256 addresses (write 0xFF)");
  Serial.println("\tE - Erase entire memory (write 0xFF)");
  Serial.println("\tx - Write 256 bytes random data at specified address in decimal eg x144");
  Serial.println("\tt - Write text string at specified address in decimal eg t144\n"); }
//---------------------------------------------------------
void ReadEEPROM(char ch) {
  Serial.print("\nReading from EEPROM....\n");
  byte data[32];                                                   // array for read data
  char buf[50];                                                    // array for printing data
  ch == 'r' ? count=1 : count=8;                                   // set number of blocks to 1 or 8
  for (int block = 0; block < count; block++) {                    // reads first block or all
    for (int base = 0; base < 256; base += 16) {                   // loop thro 256 locations in lines of 16
      for (int offset = 0; offset < 16; offset++) {                // loop thro 16 locations
        data[offset] = eeprom.read((block * 256) + base + offset); // read data and update array
        data[offset] > 0x1F && data[offset] < 0x7F ? data[offset + 16] = data[offset] : data[offset + 16] = 0x2E;} // check if ASCII characters
      sprintf(buf, "%04X:  %02X %02X %02X %02X %02X %02X %02X %02X   %02X %02X %02X %02X %02X %02X %02X %02X  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
        base + (block * 256), data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11],
        data[12], data[13], data[14], data[15], data[16], data[17], data[18], data[19], data[20], data[21], data[22], data[23],
        data[24], data[25], data[26], data[27], data[28], data[29], data[30], data[31]);
      Serial.println(buf); }                                       // print everything
    Serial.println(); }
  }
//---------------------------------------------------------
void EraseEEPROM(char ch) {
  Serial.print("\nErasing EEPROM....");
  ch == 'e' ? count=1 : count=8;                                   // set number of blocks to 1 or 8
  for (i = 0; i < count*256; i++)
    eeprom.write(i, 0xFF); 
  Serial.print("done\n");}
//---------------------------------------------------------
void WriteRandomEEPROM() {
  GetAddress();
  Serial.print("\nWriting random data to EEPROM....");
  for (i = 0; i < 256; i++)
    eeprom.update(address+i, random(0, 256));                      // use this line OR eeprom.update(i, i)
  Serial.print("done\n");}
//---------------------------------------------------------
void WriteTextEEPROM() {
  GetAddress();
  Serial.print("\nWriting text string to EEPROM....");
  String message = "This is data from EEPROM 24C16";
  for (i = 0; i < message.length(); i++)
    eeprom.update(address + i, message.charAt(i)); 
  Serial.print("done\n");}
//----------------------------------------------------------
void GetAddress(){
  String add = Serial.readString();  
  address = add.toInt();                                           // set EEPROM start address
  return address;}
