/*
  Copyright (C) AC SOFTWARE SP. Z O.O.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

/*
-(50MHz) Osc. Enable to GND -
GPIO22 - EMAC_TXD1   : TX1
GPIO19 - EMAC_TXD0   : TX0
GPIO21 - EMAC_TX_EN  : TX_EN
GPIO26 - EMAC_RXD1   : RX1
GPIO25 - EMAC_RXD0   : RX0
GPIO27 - EMAC_RX_DV  : CRS
GPIO17 - EMAC_TX_CLK : nINT/REFCLK (50MHz)
GPIO23 - SMI_MDC     : MDC
GPIO18 - SMI_MDIO    : MDIO
GND                  : GND
3V3                  : VCC
*/

#define supla_lib_config_h_  // silences debug messages
#define STATUS_LED_GPIO 22

#include <SuplaDevice.h>
#include <Adafruit_MCP23017.h>
#include <SPI.h>
#include <supla/io.h>
#include <supla/control/relay.h>
#include <supla/control/button.h>
#include <supla/control/action_trigger.h>
#include <supla/network/esp32eth.h>
  Supla::ESPETH Eth(1);  // uint_t ETH_ADDR = I²C-address of Ethernet PHY (0 or 1)


Adafruit_MCP23017 mcp; // adds supprt for two MCP, based on examples shared by @elmaya i @radzik_r: https://forum.supla.org/viewtopic.php?p=79452#p79452
Adafruit_MCP23017 mcp2;

class MyMcp23017 : public Supla::Io {
  public:
    void customDigitalWrite(int channelNumber, uint8_t pin, uint8_t val) {
      if ((pin >= 100) && (pin <= 115)) {
        mcp.digitalWrite(pin - 100, val);
               return;
      }
      if (pin <= 99) {
        return ::digitalWrite(pin, val);
      }
    }

    int customDigitalRead(int channelNumber, uint8_t pin) {
      if ((pin >= 100) && (pin <= 115)) {
        return mcp.digitalRead(pin - 100);
      }
      if (pin <= 99) {
        return ::digitalRead(pin);
      }
      if ((pin >= 200) && (pin <= 215)) {
        return mcp2.digitalRead(pin - 200);
      }
    }
} MyMcp23017;

 
 void setup() {
  Serial.begin(115200);
    Wire.begin(4,16); //Wire.begin (sda, scl)
    mcp.begin();  // sets MCP to 0x20
   
  mcp.pinMode(0, OUTPUT);
  mcp.pinMode(1, OUTPUT);
  mcp.pinMode(2, OUTPUT);
  mcp.pinMode(3, OUTPUT);
  mcp.pinMode(4, OUTPUT);
  mcp.pinMode(5, OUTPUT);
  mcp.pinMode(6, OUTPUT);
  mcp.pinMode(7, OUTPUT);
  mcp.pinMode(8, OUTPUT);
  mcp.pinMode(9, OUTPUT);
  mcp.pinMode(10, OUTPUT);
  mcp.pinMode(11, OUTPUT);
  mcp.pinMode(12, OUTPUT);
  mcp.pinMode(13, OUTPUT);
  mcp.pinMode(14, OUTPUT);
  mcp.pinMode(15, OUTPUT);
  
    mcp2.begin(1);  // sets MCP2 to 0x21
     
  mcp2.pinMode(0, INPUT);  mcp2.pullUp(0, HIGH);  // turn on a 100K true internally
  mcp2.pinMode(1, INPUT);  mcp2.pullUp(1, HIGH);  // turn on a 100K true internally
  mcp2.pinMode(2, INPUT);  mcp2.pullUp(2, HIGH);  // turn on a 100K true internally
  mcp2.pinMode(3, INPUT);  mcp2.pullUp(3, HIGH);  // turn on a 100K true internally
  mcp2.pinMode(4, INPUT);  mcp2.pullUp(4, HIGH);  // turn on a 100K true internally
  mcp2.pinMode(5, INPUT);  mcp2.pullUp(5, HIGH);  // turn on a 100K true internally
  mcp2.pinMode(6, INPUT);  mcp2.pullUp(6, HIGH);  // turn on a 100K true internally
  mcp2.pinMode(7, INPUT);  mcp2.pullUp(7, HIGH);  // turn on a 100K true internally
  mcp2.pinMode(8, INPUT);  mcp2.pullUp(8, HIGH);  // turn on a 100K true internally
  mcp2.pinMode(9, INPUT);  mcp2.pullUp(9, HIGH);  // turn on a 100K true internally
  mcp2.pinMode(10, INPUT);  mcp2.pullUp(10, HIGH);  // turn on a 100K true internally
  mcp2.pinMode(11, INPUT);  mcp2.pullUp(11, HIGH);  // turn on a 100K true internally
  mcp2.pinMode(12, INPUT);  mcp2.pullUp(12, HIGH);  // turn on a 100K true internally
  mcp2.pinMode(13, INPUT);  mcp2.pullUp(13, HIGH);  // turn on a 100K true internally
  mcp2.pinMode(14, INPUT);  mcp2.pullUp(14, HIGH);  // turn on a 100K true internally
  mcp2.pinMode(15, INPUT);  mcp2.pullUp(15, HIGH);  // turn on a 100K true internally
  
  // Replace the falowing GUID with value that you can retrieve from https://www.supla.org/arduino/get-guid
  char GUID[SUPLA_GUID_SIZE] = {0x30,0x65,0x52,0x02,0x2A,0xF9,0x53,0x46,0xF6,0x21,0xC9,0x72,0xD6,0x3C,0xDD,0x20};

  // Replace the following AUTHKEY with value that you can retrieve from: https://www.supla.org/arduino/get-authkey
  char AUTHKEY[SUPLA_AUTHKEY_SIZE] = {0x84,0x83,0x4F,0x2F,0x73,0x00,0x82,0xD2,0x29,0x24,0xE6,0x2E,0x04,0xDC,0xDD,0x9B};

  // Sekcja mapowania przekaźników i przycisków; przekaźniki: https://forum.supla.org/viewtopic.php?t=7263; przyciski: https://forum.supla.org/viewtopic.php?t=7512; wyzwalacze akcji: https://forum.supla.org/viewtopic.php?t=9503
  
  auto r101 = new Supla::Control::Relay(108); //B0
  auto r102 = new Supla::Control::Relay(109); //B1
  auto r103 = new Supla::Control::Relay(110); //B2
  auto r104 = new Supla::Control::Relay(111); //B3
  auto r105 = new Supla::Control::Relay(112); //B4
  auto r106 = new Supla::Control::Relay(113); //B5
  auto r107 = new Supla::Control::Relay(114); //B6
  auto r108 = new Supla::Control::Relay(115); //B7
  auto r109 = new Supla::Control::Relay(100); //A0
  auto r110 = new Supla::Control::Relay(101); //A1
  auto r111 = new Supla::Control::Relay(102); //A2
  auto r112 = new Supla::Control::Relay(103); //A3
  auto r113 = new Supla::Control::Relay(104); //A4
  auto r114 = new Supla::Control::Relay(106); //A6
  auto r115 = new Supla::Control::Relay(105); //A5
  auto r116 = new Supla::Control::Relay(107); //A7
  auto r117 = new Supla::Control::Relay(32);  //IO32
  auto r118 = new Supla::Control::Relay(33);  //IO33

  auto b101 = new Supla::Control::Button(208, true, true); // input pullup and reverse logic (connects to GND) B0
  auto b102 = new Supla::Control::Button(209, true, true); // input pullup and reverse logic (connects to GND) B1
  auto b103 = new Supla::Control::Button(210, true, true); // input pullup and reverse logic (connects to GND) B2
  auto b104 = new Supla::Control::Button(211, true, true); // input pullup and reverse logic (connects to GND) B3
  auto b105 = new Supla::Control::Button(212, true, true); // input pullup and reverse logic (connects to GND) B4
  auto b106 = new Supla::Control::Button(213, true, true); // input pullup and reverse logic (connects to GND) B5
  auto b107 = new Supla::Control::Button(214, true, true); // input pullup and reverse logic (connects to GND) B6
  auto b108 = new Supla::Control::Button(215, true, true); // input pullup and reverse logic (connects to GND) B7
  auto b109 = new Supla::Control::Button(200, true, true); // input pullup and reverse logic (connects to GND) A0
  auto b110 = new Supla::Control::Button(201, true, true); // input pullup and reverse logic (connects to GND) A1
  auto b111 = new Supla::Control::Button(202, true, true); // input pullup and reverse logic (connects to GND) A2
  auto b112 = new Supla::Control::Button(203, true, true); // input pullup and reverse logic (connects to GND) A3
  auto b113 = new Supla::Control::Button(204, true, true); // input pullup and reverse logic (connects to GND) A4
  auto b114 = new Supla::Control::Button(205, true, true); // input pullup and reverse logic (connects to GND) A5
  auto b115 = new Supla::Control::Button(206, true, true); // input pullup and reverse logic (connects to GND) A6
  auto b116 = new Supla::Control::Button(207, true, true); // input pullup and reverse logic (connects to GND) A7
  auto b117 = new Supla::Control::Button(34, true, true); // input pullup and reverse logic (connects to GND)  IO34
  auto b118 = new Supla::Control::Button(5, true, true); // input pullup and reverse logic (connects to GND)  IO5
  b118->setMulticlickTime(400); // the software counts clicks and after 400ms after the release of a button starts an predefined action
  b118->setHoldTime(2000); // after 2s of holding the button the ON_HOLD event will be started

  auto at101 = new Supla::Control::ActionTrigger();
  at101->setRelatedChannel(r101);  // pairs the AT with relay channel in Supla Cloud
  at101->attach(b101);
  b101->setMulticlickTime(400, false); // true for bistable button
  b101->setHoldTime(2000); // after 2s of holding the button the ON_HOLD event will be started
  auto at102 = new Supla::Control::ActionTrigger();
  at102->setRelatedChannel(r102);  // pairs the AT with relay channel in Supla Cloud
  at102->attach(b102);
  b102->setMulticlickTime(400, false); // true for bistable button
  b102->setHoldTime(2000); // po 2 s od przytrzymania przycisku zostanie wywołane zdarzenie ON_HOLD
  auto at103 = new Supla::Control::ActionTrigger();
  at103->setRelatedChannel(r103);  // pairs the AT with relay channel in Supla Cloud
  at103->attach(b103);
  b103->setMulticlickTime(400, false); // true for bistable button
  b103->setHoldTime(2000); // after 2s of holding the button the ON_HOLD event will be started
  auto at104 = new Supla::Control::ActionTrigger();
  at104->setRelatedChannel(r104);  // pairs the AT with relay channel in Supla Cloud
  at104->attach(b104);
  b104->setMulticlickTime(400, false); // true for bistable button
  b104->setHoldTime(2000); // after 2s of holding the button the ON_HOLD event will be started
  auto at105 = new Supla::Control::ActionTrigger();
  at105->setRelatedChannel(r105);  // pairs the AT with relay channel in Supla Cloud
  at105->attach(b105);
  b105->setMulticlickTime(400, false); // true for bistable button
  b105->setHoldTime(2000); // after 2s of holding the button the ON_HOLD event will be started
  auto at106 = new Supla::Control::ActionTrigger();
  at106->setRelatedChannel(r106);  // pairs the AT with relay channel in Supla Cloud
  at106->attach(b106);
  b106->setMulticlickTime(400, false); // true for bistable button
  b106->setHoldTime(2000); // after 2s of holding the button the ON_HOLD event will be started
  auto at107 = new Supla::Control::ActionTrigger();
  at107->setRelatedChannel(r107);  // pairs the AT with relay channel in Supla Cloud
  at107->attach(b107);
  b107->setMulticlickTime(400, false); // true for bistable button
  b107->setHoldTime(2000); // after 2s of holding the button the ON_HOLD event will be started
  auto at108 = new Supla::Control::ActionTrigger();
  at108->setRelatedChannel(r108);  // pairs the AT with relay channel in Supla Cloud
  at108->attach(b108);
  b108->setMulticlickTime(400, false); // true for bistable button
  b108->setHoldTime(2000); // after 2s of holding the button the ON_HOLD event will be started
  auto at109 = new Supla::Control::ActionTrigger();
  at109->setRelatedChannel(r109);  // pairs the AT with relay channel in Supla Cloud
  at109->attach(b109);
  b109->setMulticlickTime(400, false); // true for bistable button
  b109->setHoldTime(2000); // after 2s of holding the button the ON_HOLD event will be started
  auto at110 = new Supla::Control::ActionTrigger();
  at110->setRelatedChannel(r110);  // pairs the AT with relay channel in Supla Cloud
  at110->attach(b110);
  b110->setMulticlickTime(400, false); // true for bistable button
  b110->setHoldTime(2000); // after 2s of holding the button the ON_HOLD event will be started
  auto at111 = new Supla::Control::ActionTrigger();
  at111->setRelatedChannel(r111);  // pairs the AT with relay channel in Supla Cloud
  at111->attach(b111);
  b111->setMulticlickTime(400, false); // true for bistable button
  b111->setHoldTime(2000); // after 2s of holding the button the ON_HOLD event will be started
  auto at112 = new Supla::Control::ActionTrigger();
  at112->setRelatedChannel(r112);  // pairs the AT with relay channel in Supla Cloud
  at112->attach(b112);
  b112->setMulticlickTime(400, false); // true for bistable button
  b112->setHoldTime(2000); // after 2s of holding the button the ON_HOLD event will be started
  auto at113 = new Supla::Control::ActionTrigger();
  at113->setRelatedChannel(r113);  // pairs the AT with relay channel in Supla Cloud
  at113->attach(b113);
  b113->setMulticlickTime(400, false); // true for bistable button
  b113->setHoldTime(2000); // after 2s of holding the button the ON_HOLD event will be started
  auto at114 = new Supla::Control::ActionTrigger();
  at114->setRelatedChannel(r114);  // pairs the AT with relay channel in Supla Cloud
  at114->attach(b114);
  b114->setMulticlickTime(400, false); // true for bistable button
  b114->setHoldTime(2000); // after 2s of holding the button the ON_HOLD event will be started
  auto at115 = new Supla::Control::ActionTrigger();
  at1155->setRelatedChannel(r115);  // pairs the AT with relay channel in Supla Cloud
  at115->attach(b115);
  b115->setMulticlickTime(400, false); // true for bistable button
  b115->setHoldTime(2000); // after 2s of holding the button the ON_HOLD event will be started
  auto at116 = new Supla::Control::ActionTrigger();
  at116->setRelatedChannel(r116);  // pairs the AT with relay channel in Supla Cloud
  at116->attach(b116);
  b116->setMulticlickTime(400, false); // true for bistable button
  b116->setHoldTime(2000); // after 2s of holding the button the ON_HOLD event will be started
  auto at117 = new Supla::Control::ActionTrigger();
  at117->setRelatedChannel(r117);  // pairs the AT with relay channel in Supla Cloud
  at117->attach(b117);
  b117->setMulticlickTime(400, false); // true for bistable button
  b117->setHoldTime(2000); // after 2s of holding the button the ON_HOLD event will be started
  auto at118 = new Supla::Control::ActionTrigger();
  at118->attach(b118);
    
  // You can find more about pairing buttons with relays on the forum: https://forum.supla.org/viewtopic.php?t=7512

  b101->addAction(Supla::TOGGLE , r101, Supla::ON_PRESS); // 1
  b102->addAction(Supla::TOGGLE , r102, Supla::ON_PRESS); // 2
  b103->addAction(Supla::TOGGLE , r103, Supla::ON_PRESS); // 3
  b104->addAction(Supla::TOGGLE , r104, Supla::ON_PRESS); // 4
  b105->addAction(Supla::TOGGLE , r105, Supla::ON_PRESS); // 5
  b106->addAction(Supla::TOGGLE , r106, Supla::ON_PRESS); // 6
  b107->addAction(Supla::TOGGLE , r107, Supla::ON_PRESS); // 7
  b108->addAction(Supla::TOGGLE , r108, Supla::ON_PRESS); // 8
  b109->addAction(Supla::TOGGLE , r109, Supla::ON_PRESS); // 9  
  b110->addAction(Supla::TOGGLE , r110, Supla::ON_PRESS); // 10
  b111->addAction(Supla::TOGGLE , r111, Supla::ON_PRESS); // 11
  b112->addAction(Supla::TOGGLE , r112, Supla::ON_PRESS); // 12
  b113->addAction(Supla::TOGGLE , r113, Supla::ON_PRESS); // 13
  b114->addAction(Supla::TOGGLE , r114, Supla::ON_PRESS); // 14
  b115->addAction(Supla::TOGGLE , r115, Supla::ON_PRESS); // 15
  b116->addAction(Supla::TOGGLE , r116, Supla::ON_PRESS); // 16

  // turn off all relays
  b117->addAction(Supla::TURN_OFF , r101, Supla::ON_PRESS); // 1
  b117->addAction(Supla::TURN_OFF , r102, Supla::ON_PRESS); // 2
  b117->addAction(Supla::TURN_OFF , r103, Supla::ON_PRESS); // 3
  b117->addAction(Supla::TURN_OFF , r104, Supla::ON_PRESS); // 4
  b117->addAction(Supla::TURN_OFF , r105, Supla::ON_PRESS); // 5
  b117->addAction(Supla::TURN_OFF , r106, Supla::ON_PRESS); // 6
  b117->addAction(Supla::TURN_OFF , r107, Supla::ON_PRESS); // 7
  b117->addAction(Supla::TURN_OFF , r108, Supla::ON_PRESS); // 8
  b117->addAction(Supla::TURN_OFF , r109, Supla::ON_PRESS); // 9
  b117->addAction(Supla::TURN_OFF , r110, Supla::ON_PRESS); // 10
  b117->addAction(Supla::TURN_OFF , r111, Supla::ON_PRESS); // 11
  b117->addAction(Supla::TURN_OFF , r112, Supla::ON_PRESS); // 12
  b117->addAction(Supla::TURN_OFF , r113, Supla::ON_PRESS); // 13
  b117->addAction(Supla::TURN_OFF , r114, Supla::ON_PRESS); // 14
  b117->addAction(Supla::TURN_OFF , r115, Supla::ON_PRESS); // 15
  b117->addAction(Supla::TURN_OFF , r116, Supla::ON_PRESS); // 16
  b117->addAction(Supla::TURN_OFF , r117, Supla::ON_PRESS); // 17
  b117->addAction(Supla::TURN_OFF , r118, Supla::ON_PRESS); // 18

  // test button
  b118->addAction(Supla::TURN_ON , r101, Supla::ON_CLICK_1); // 1
  b118->addAction(Supla::TURN_ON , r102, Supla::ON_CLICK_1); // 2
  b118->addAction(Supla::TURN_ON , r103, Supla::ON_CLICK_1); // 3
  b118->addAction(Supla::TURN_ON , r104, Supla::ON_CLICK_1); // 4
  b118->addAction(Supla::TURN_ON , r105, Supla::ON_CLICK_1); // 5
  b118->addAction(Supla::TURN_ON , r106, Supla::ON_CLICK_1); // 6
  b118->addAction(Supla::TURN_ON , r107, Supla::ON_CLICK_1); // 7
  b118->addAction(Supla::TURN_ON , r108, Supla::ON_CLICK_1); // 8
  b118->addAction(Supla::TURN_ON , r109, Supla::ON_CLICK_1); // 9
  b118->addAction(Supla::TURN_ON , r110, Supla::ON_CLICK_1); // 10
  b118->addAction(Supla::TURN_ON , r111, Supla::ON_CLICK_1); // 11
  b118->addAction(Supla::TURN_ON , r112, Supla::ON_CLICK_1); // 12
  b118->addAction(Supla::TURN_ON , r113, Supla::ON_CLICK_1); // 13
  b118->addAction(Supla::TURN_ON , r114, Supla::ON_CLICK_1); // 14
  b118->addAction(Supla::TURN_ON , r115, Supla::ON_CLICK_1); // 15
  b118->addAction(Supla::TURN_ON , r116, Supla::ON_CLICK_1); // 16
  b118->addAction(Supla::TURN_ON , r117, Supla::ON_CLICK_1); // 17
  b118->addAction(Supla::TURN_ON , r118, Supla::ON_CLICK_1); // 18

  b118->addAction(Supla::TURN_OFF , r101, Supla::ON_CLICK_2); // 1
  b118->addAction(Supla::TURN_OFF , r102, Supla::ON_CLICK_2); // 2
  b118->addAction(Supla::TURN_OFF , r103, Supla::ON_CLICK_2); // 3
  b118->addAction(Supla::TURN_OFF , r104, Supla::ON_CLICK_2); // 4
  b118->addAction(Supla::TURN_OFF , r105, Supla::ON_CLICK_2); // 5
  b118->addAction(Supla::TURN_OFF , r106, Supla::ON_CLICK_2); // 6
  b118->addAction(Supla::TURN_OFF , r107, Supla::ON_CLICK_2); // 7
  b118->addAction(Supla::TURN_OFF , r108, Supla::ON_CLICK_2); // 8
  b118->addAction(Supla::TURN_OFF , r109, Supla::ON_CLICK_2); // 9
  b118->addAction(Supla::TURN_OFF , r110, Supla::ON_CLICK_2); // 10
  b118->addAction(Supla::TURN_OFF , r111, Supla::ON_CLICK_2); // 11
  b118->addAction(Supla::TURN_OFF , r112, Supla::ON_CLICK_2); // 12
  b118->addAction(Supla::TURN_OFF , r113, Supla::ON_CLICK_2); // 13
  b118->addAction(Supla::TURN_OFF , r114, Supla::ON_CLICK_2); // 14
  b118->addAction(Supla::TURN_OFF , r115, Supla::ON_CLICK_2); // 15
  b118->addAction(Supla::TURN_OFF , r116, Supla::ON_CLICK_2); // 16
  b118->addAction(Supla::TURN_OFF , r117, Supla::ON_CLICK_2); // 17
  b118->addAction(Supla::TURN_OFF , r118, Supla::ON_CLICK_2); // 18
  
  /*
     Having your device already registered at cloud.supla.org,
     you want to change CHANNEL sequence or remove any of them,
     then you must also remove the device itself from cloud.supla.org.
     Otherwise you will get "Channel conflict!" error.
  */
  
  /*
     SuplaDevice Initialization.
     Server address is available at https://cloud.supla.org
     If you do not have an account, you can create it at
     https://cloud.supla.org/account/create SUPLA and SUPLA CLOUD are free of
     charge

  */

  SuplaDevice.begin(
      GUID,              // Global Unique Identifier
      "svrXX.supla.org",  // SUPLA server address
      "user@email.com",   // Email address used to login to Supla Cloud
      AUTHKEY);          // Authorization key
}

void loop() {
  SuplaDevice.iterate();
}
