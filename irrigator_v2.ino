// Arduino self made irrgator script
// made with nodeMCU, relay module, potentiometer and LCD screen

// made by matteo jucker riva
// Standard GNU licence applies

// 0. LIBRARIES
// I2C screen
// Potentiometer?
// ??

// 1. PIN DEFINITIONS

//a. Potentiometer
#define PO
//b. Relay module
#define REL0 16
#define REL1 5
#define REL2 4
#define REL3 0
//c. LCD screen
#define LCD_VIN 2
#define LCD_V1  14
#define LCD_V2  12

// 2. GLOBAL VARIABLES and MAIN FUCNTIONS

//a. Potentiometer

//function to detect if potentiometer changes
bool potTrigger=false;
int potValue;
int potValue0 = -2;
int sensitivity = 5;

void checkPotChange() {
  if (potValue0 = -2) {
    potValue0 = potValue;
  }; //set initial value
  bool check = abs(potValue - potValue0) < sensitivity; //evaluate if current Value is significantly different from initial value

  if (check) {
    potValue0 = -2;
  };  //reset initial value before ending
  bool potTrigger=true;
};

//translate pot value in classes
int potClass(int maxValue, int val) {
  return map(val, 0, 1024, 0, maxValue);
}

//b. Relay module
// variables for direct Relay control

int relNum = 4;
int relPins[4] {REL0, REL1, REL2, REL3};

//the following Array holds all the information needed for the relays to function: 1st dim: reps, 2nd: irrigationTime
int relArray[2][4] {{3, 3, 3, 3}, {10, 10, 10, 10}};

//c. LCD screen

// There are several different versions of the LCD I2C adapter, each might have a different address.
// Try the given addresses by Un/commenting the following rows until LCD works follow the serial monitor prints.
// To find your LCD address go to: http://playground.arduino.cc/Main/I2cScanner and run example.
#define LCD_ADDRESS 0x3F
//#define LCD_ADDRESS 0x27
// Define LCD characteristics
#define LCD_ROWS 2
#define LCD_COLUMNS 16
#define SCROLL_DELAY 150
#define BACKLIGHT 255
// object initialization

//LiquidCrystal_PCF8574 lcdI2C;
Potentiometer Trimmer(TRIMMER_PIN_SIG);

//Function for easy display of messages
String lcd_line1 = " ";
String lcd_line2 = " ";

void showMessage(String firstLine = lcd_line1, String secondLine = lcd_line2 ) {

  lcd_line1 = firstLine;
  lcd_line2 = secondLine;

  lcd.selectLine(1);                    // Set cursor at the begining of line 2
  lcd.print(lcd_line1);
  lcd.selectLine(2);
  lcd.print(lcd_line2);
}

// 2. TIMEKEEPING
unsigned long time0;

//function for soft stop outputs TRUE if current Timing below delay
bool softDelay(int secondsDelay, unsigned long time0 = time0) {
  if (time0 == 0) {
    time0 = millis();
  };

  long interval = long(secondsDelay * 1000);

  bool check = bool(millis() - time0 < interval);
  if (check) {
    time0 = 0;
  };
  return check;
}


//void setTime()
//{
//  time0 = millis()
//}

//long calcTimeDiff()
//{
//  long delta = millis() - time0:
//  return delta;
//}



//3. SETTINGS PROCEDURE
int flowControl = 0;
int sector;

int changeIrrSettings() {
  // Settings start

  // Display ciao andre
  if (softDelay(5) && flowControl == 0)
  {
    showMessage("  Ciao Andre  ", "  irrighiamo?? ");
  } else if (flowControl == 0)
  {
    flowControl = flowControl + 1;
    lcd.clear();
  }

  // Choose sector
  if (softDelay(8) && flowControl == 1)
  {
    showMessage("scegli settore:", String(potClass(4, potValue)));
  } else if (flowControl == 1)
  {
    flowControl = flowControl + 1;
    sector = potClass(4, potValue);
    lcd.clear()
  }
  // Choose reps
  if (softDelay(8) && flowControl == 2)
  {
    showMessage("scegli ripetizioni", String(potClass(5, potValue)));
  } else if (flowControl == 2)
  {
    flowControl = flowControl + 1;
    relArray[0][sector] = potClass(5, potValue);
    lcd.clear()
  }
  // Choose time
  if (softDelay(8) && flowControl == 3) {
    showMessage("scegli ripetizioni", String(potClass(30, potValue)));
    //TODO add conto alla rovescia
  } else if (flowControl == 3)
  {
    flowControl = flowControl + 1;
    relArray[1][sector] = potClass(30, potValue);
    lcd.clear()
  }
  // end of settings
  if (flowControl == 4 && softDelay(5)) {
    //display final settings
    String finString="settore: "+String(sector)+"; ";
    finString=finString+"ripe: "+String(relArray[0][sector])+"; ";
    finString=finString+"tempo: "+String(relArray[1][sector])+"; ";
    showMessage("fine settaggi", finString);
    flowControl = flowControl + 1;
  };
};

  // IRRIGATION MODE

 //function calcNextIrrigationTime

unsigned long calcNextIrrigationTime(int reps){
  unsigned long time0=millis();
  interval= long( (1000*60*60*24)/reps) );
  nextIrrigation=time0+interval;
  return nextIrrigation;
  }

 //function start irrgation
 

 //function stopIrrigation
 
 // 7. Define sleep mode
 
// 8. MODE variables

int mode=0; 
//0 do nothing 
//1 set irrigation
//2 calc irrigation
//3 ready to irrigate
//4 sleep

void setMode(){
  if (potTrigger)
  
}

  // 9. Setup function
  // 10. Loop function



  //*********************************************************************

  // Pin Definitions
#define TRIMMER_PIN_SIG	A0
#define PULLPUSHSOLENOID1_1_PIN_SIG	0
#define PULLPUSHSOLENOID2_2_PIN_SIG	2
#define PULLPUSHSOLENOID3_3_PIN_SIG	14
#define PULLPUSHSOLENOID4_4_PIN_SIG	12



  // GLOBAL VARIABLES
  // There are several different versions of the LCD I2C adapter, each might have a different address.
  // Try the given addresses by Un/commenting the following rows until LCD works follow the serial monitor prints.
  // To find your LCD address go to: http://playground.arduino.cc/Main/I2cScanner and run example.
#define LCD_ADDRESS 0x3F
  //#define LCD_ADDRESS 0x27
  // Define LCD characteristics
#define LCD_ROWS 2
#define LCD_COLUMNS 16
#define SCROLL_DELAY 150
#define BACKLIGHT 255
  // object initialization
  LiquidCrystal_PCF8574 lcdI2C;
  Potentiometer Trimmer(TRIMMER_PIN_SIG);


  // define vars for testing menu
  const int timeout = 10000;       //define timeout of 10 sec
  char menuOption = 0;
  long time0;

  // Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
  void setup()
  {
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    if (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");

    // initialize the lcd
    lcdI2C.begin(LCD_COLUMNS, LCD_ROWS, LCD_ADDRESS, BACKLIGHT);
    pinMode(PULLPUSHSOLENOID1_1_PIN_SIG, OUTPUT);
    pinMode(PULLPUSHSOLENOID2_2_PIN_SIG, OUTPUT);
    pinMode(PULLPUSHSOLENOID3_3_PIN_SIG, OUTPUT);
    pinMode(PULLPUSHSOLENOID4_4_PIN_SIG, OUTPUT);
    menuOption = menu();

  }

  // Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
  void loop()
  {


    if (menuOption == '1') {
      // LCD 16x2 I2C - Test Code
      // The LCD Screen will display the text of your choice.
      lcdI2C.clear();                          // Clear LCD screen.
      lcdI2C.print("  Circuito.io  ");                   // Print print String to LCD on first line
      lcdI2C.selectLine(2);                    // Set cursor at the begining of line 2
      lcdI2C.print("     Rocks!  ");                   // Print print String to LCD on second line
      delay(1000);

    }
    else if (menuOption == '2') {
      // Trimmer Potentiometer - 10K - Test Code
      int TrimmerVal = Trimmer.read();
      Serial.print(F("Val: ")); Serial.println(TrimmerVal);
    }
    else if (menuOption == '3') {
      // Solenoid Push-Pull - 5v (Small) #1 - Test Code
      digitalWrite(PULLPUSHSOLENOID1_1_PIN_SIG, HIGH); //Turn Solenoid on.
      delay(1000);  //waits 1000 milliseconds (1 sec). change the value in the brackets (1000) for a longer or shorter delay in milliseconds.
      digitalWrite(PULLPUSHSOLENOID1_1_PIN_SIG, LOW); //Turn Solenoid off.
      delay(1000);  //waits 1000 milliseconds (1 sec). change the value in the brackets (1000) for a longer or shorter delay in milliseconds.
    }
    else if (menuOption == '4') {
      // Solenoid Push-Pull - 5v (Small) #2 - Test Code
      digitalWrite(PULLPUSHSOLENOID2_2_PIN_SIG, HIGH); //Turn Solenoid on.
      delay(1000);  //waits 1000 milliseconds (1 sec). change the value in the brackets (1000) for a longer or shorter delay in milliseconds.
      digitalWrite(PULLPUSHSOLENOID2_2_PIN_SIG, LOW); //Turn Solenoid off.
      delay(1000);  //waits 1000 milliseconds (1 sec). change the value in the brackets (1000) for a longer or shorter delay in milliseconds.
    }
    else if (menuOption == '5') {
      // Solenoid Push-Pull - 5v (Small) #3 - Test Code
      digitalWrite(PULLPUSHSOLENOID3_3_PIN_SIG, HIGH); //Turn Solenoid on.
      delay(1000);  //waits 1000 milliseconds (1 sec). change the value in the brackets (1000) for a longer or shorter delay in milliseconds.
      digitalWrite(PULLPUSHSOLENOID3_3_PIN_SIG, LOW); //Turn Solenoid off.
      delay(1000);  //waits 1000 milliseconds (1 sec). change the value in the brackets (1000) for a longer or shorter delay in milliseconds.
    }
    else if (menuOption == '6') {
      // Solenoid Push-Pull - 5v (Small) #4 - Test Code
      digitalWrite(PULLPUSHSOLENOID4_4_PIN_SIG, HIGH); //Turn Solenoid on.
      delay(1000);  //waits 1000 milliseconds (1 sec). change the value in the brackets (1000) for a longer or shorter delay in milliseconds.
      digitalWrite(PULLPUSHSOLENOID4_4_PIN_SIG, LOW); //Turn Solenoid off.
      delay(1000);  //waits 1000 milliseconds (1 sec). change the value in the brackets (1000) for a longer or shorter delay in milliseconds.
    }

    if (millis() - time0 > timeout)
    {
      menuOption = menu();
    }

  }



  // Menu function for selecting the components to be tested
  // Follow serial monitor for instrcutions
  char menu()
  {

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) LCD 16x2 I2C"));
    Serial.println(F("(2) Trimmer Potentiometer - 10K"));
    Serial.println(F("(3) Solenoid Push-Pull - 5v (Small) #1"));
    Serial.println(F("(4) Solenoid Push-Pull - 5v (Small) #2"));
    Serial.println(F("(5) Solenoid Push-Pull - 5v (Small) #3"));
    Serial.println(F("(6) Solenoid Push-Pull - 5v (Small) #4"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available())
    {
      char c = Serial.read();
      if (isAlphaNumeric(c))
      {

        if (c == '1')
          Serial.println(F("Now Testing LCD 16x2 I2C"));
        else if (c == '2')
          Serial.println(F("Now Testing Trimmer Potentiometer - 10K"));
        else if (c == '3')
          Serial.println(F("Now Testing Solenoid Push-Pull - 5v (Small) #1"));
        else if (c == '4')
          Serial.println(F("Now Testing Solenoid Push-Pull - 5v (Small) #2"));
        else if (c == '5')
          Serial.println(F("Now Testing Solenoid Push-Pull - 5v (Small) #3"));
        else if (c == '6')
          Serial.println(F("Now Testing Solenoid Push-Pull - 5v (Small) #4"));
        else
        {
          Serial.println(F("illegal input!"));
          return 0;
        }
        time0 = millis();
        return c;
      }
    }
  }

  /*******************************************************

       Circuito.io is an automatic generator of schematics and code for off
       the shelf hardware combinations.

       Copyright (C) 2016 Roboplan Technologies Ltd.

       This program is free software: you can redistribute it and/or modify
       it under the terms of the GNU General Public License as published by
       the Free Software Foundation, either version 3 of the License, or
       (at your option) any later version.

       This program is distributed in the hope that it will be useful,
       but WITHOUT ANY WARRANTY; without even the implied warranty of
       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
       GNU General Public License for more details.

       You should have received a copy of the GNU General Public License
       along with this program.  If not, see <http://www.gnu.org/licenses/>.

       In addition, and without limitation, to the disclaimers of warranties
       stated above and in the GNU General Public License version 3 (or any
       later version), Roboplan Technologies Ltd. ("Roboplan") offers this
       program subject to the following warranty disclaimers and by using
       this program you acknowledge and agree to the following:
       THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND
       WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN
       HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT
       NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS
       FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY
       STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE.
       YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
       ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT
       SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES
       NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO
       SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE
       FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT
       VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
       RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN.
       YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN,
       ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF
       THE ABOVE.
  ********************************************************/
