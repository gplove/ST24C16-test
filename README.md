# ST24C16-test
Arduino and STM32 test programs for EEPROM

After my last posting I continued (struggled) to write a working program for testing the ST24C16 EEPROM on Arduino Nano, Nano Every and STM32F103 platforms. Initialy I could not get the same program to run on all three. After updating some libraries (presumably) I found that 'sprintf' started working on the Nano Every. I could not get the same program to run on the STM32 without two modifications and both programs are presented here.

The first modification for the STM32 was to change the 'data' array type from 'byte' to 'int'

The second was to delete the 'return address' command in one of the functions
If anyone knows why these two changes were necessary please let me know.


En route I had developed an interesting menu system which should work in other scenarios (but may not be seen as good programming!) - see the loop()
