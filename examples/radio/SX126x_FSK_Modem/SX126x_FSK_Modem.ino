/*
   RadioLib SX126x FSK Modem Example

   This example shows how to use FSK modem in SX126x chips.

   NOTE: The sketch below is just a guide on how to use
         FSK modem, so this code should not be run directly!
         Instead, modify the other examples to use FSK
         modem and use the appropriate configuration
         methods.

   For default module settings, see the wiki page
   https://github.com/jgromes/RadioLib/wiki/Default-configuration#sx126x---fsk-modem

   For full API reference, see the GitHub Pages
   https://jgromes.github.io/RadioLib/
*/

// include the library
#include <LilyGoLib.h>
#include <LV_Helper.h>

void setup()
{
    Serial.begin(115200);

    watch.begin();

    beginLvglHelper();

    // if needed, you can switch between LoRa and FSK modes
    //
    // watch.begin()       start LoRa mode (and disable FSK)
    // watch.beginFSK()    start FSK mode (and disable LoRa)

    // the following settings can also
    // be modified at run-time
    int state = watch.setFrequency(433.5);
    state = watch.setBitRate(100.0);
    state = watch.setFrequencyDeviation(10.0);
    state = watch.setRxBandwidth(250.0);
    state = watch.setOutputPower(10.0);
    state = watch.setCurrentLimit(100.0);
    state = watch.setDataShaping(RADIOLIB_SHAPING_1_0);
    uint8_t syncWord[] = {0x01, 0x23, 0x45, 0x67,
                          0x89, 0xAB, 0xCD, 0xEF
                         };
    state = watch.setSyncWord(syncWord, 8);
    if (state != RADIOLIB_ERR_NONE) {
        Serial.print(F("Unable to set configuration, code "));
        Serial.println(state);
        while (true);
    }

    // FSK modem on SX126x can handle the sync word setting in bits, not just
    // whole bytes. The value used is left-justified.
    // This makes same result as watch.setSyncWord(syncWord, 8):
    state = watch.setSyncBits(syncWord, 64);
    // This will use 0x012 as sync word (12 bits only):
    state = watch.setSyncBits(syncWord, 12);

    // FSK modem allows advanced CRC configuration
    // Default is CCIT CRC16 (2 bytes, initial 0x1D0F, polynomial 0x1021, inverted)
    // Set CRC to IBM CRC (2 bytes, initial 0xFFFF, polynomial 0x8005, non-inverted)
    state = watch.setCRC(2, 0xFFFF, 0x8005, false);
    // set CRC length to 0 to disable CRC

#warning "This sketch is just an API guide! Read the note at line 6."
}

void loop()
{
    // FSK modem can use the same transmit/receive methods
    // as the LoRa modem, even their interrupt-driven versions

    // transmit FSK packet
    int state = watch.transmit("Hello World!");
    /*
      byte byteArr[] = {0x01, 0x23, 0x45, 0x67,
                        0x89, 0xAB, 0xCD, 0xEF};
      int state = watch.transmit(byteArr, 8);
    */
    if (state == RADIOLIB_ERR_NONE) {
        Serial.println(F("[SX1262] Packet transmitted successfully!"));
    } else if (state == RADIOLIB_ERR_PACKET_TOO_LONG) {
        Serial.println(F("[SX1262] Packet too long!"));
    } else if (state == RADIOLIB_ERR_TX_TIMEOUT) {
        Serial.println(F("[SX1262] Timed out while transmitting!"));
    } else {
        Serial.println(F("[SX1262] Failed to transmit packet, code "));
        Serial.println(state);
    }

    // receive FSK packet
    String str;
    state = watch.receive(str);
    /*
      byte byteArr[8];
      int state = watch.receive(byteArr, 8);
    */
    if (state == RADIOLIB_ERR_NONE) {
        Serial.println(F("[SX1262] Received packet!"));
        Serial.print(F("[SX1262] Data:\t"));
        Serial.println(str);
    } else if (state == RADIOLIB_ERR_RX_TIMEOUT) {
        Serial.println(F("[SX1262] Timed out while waiting for packet!"));
    } else {
        Serial.println(F("[SX1262] Failed to receive packet, code "));
        Serial.println(state);
    }

    // FSK modem has built-in address filtering system
    // it can be enabled by setting node address, broadcast
    // address, or both
    //
    // to transmit packet to a particular address,
    // use the following methods:
    //
    // watch.transmit("Hello World!", address);
    // watch.startTransmit("Hello World!", address);

    // set node address to 0x02
    state = watch.setNodeAddress(0x02);
    // set broadcast address to 0xFF
    state = watch.setBroadcastAddress(0xFF);
    if (state != RADIOLIB_ERR_NONE) {
        Serial.println(F("[SX1262] Unable to set address filter, code "));
        Serial.println(state);
    }

    // address filtering can also be disabled
    // NOTE: calling this method will also erase previously set
    //       node and broadcast address
    /*
      state = watch.disableAddressFiltering();
      if (state != RADIOLIB_ERR_NONE) {
        Serial.println(F("Unable to remove address filter, code "));
      }
    */

    lv_task_handler();
    delay(5);
}
