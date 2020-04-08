#include <TimerOne.h>
#include <Adafruit_NeoPixel.h>
#define PINHand 12 //defining the PWM pin
#define PINCircle 53
#define N_LEDSHand 20 //number of LED units on the strip
#define N_LEDSCircle 12
#define ctsPin 13

Adafruit_NeoPixel stripHand = Adafruit_NeoPixel(N_LEDSHand, PINHand);
Adafruit_NeoPixel stripCircle = Adafruit_NeoPixel(N_LEDSCircle, PINCircle);

int sensorReading = 0;
bool circleOff = false;

unsigned char channel_1 = 4;  // Output to Opto Triac pin, channel 1
unsigned char channel_2 = 5;  // Output to Opto Triac pin, channel 2
unsigned char channel_3 = 6;  // Output to Opto Triac pin, channel 3
unsigned char channel_4 = 7;  // Output to Opto Triac pin, channel 4
unsigned char channel_5 = 8;  // Output to Opto Triac pin, channel 5
unsigned char channel_6 = 9;  // Output to Opto Triac pin, channel 6
unsigned char channel_7 = 10; // Output to Opto Triac pin, channel 7
unsigned char channel_8 = 11; // Output to Opto Triac pin, channel 8
unsigned char channel_9 = 24;  // Output to Opto Triac pin, channel 1
unsigned char channel_10 = 26;  // Output to Opto Triac pin, channel 2
unsigned char channel_11 = 28; // Output to Opto Triac pin, channel 3
unsigned char channel_12 = 30;  // Output to Opto Triac pin, channel 4
unsigned char channel_13 = 32;  // Output to Opto Triac pin, channel 5
unsigned char channel_14 = 34; // Output to Opto Triac pin, channel 6
unsigned char channel_15 = 36; // Output to Opto Triac pin, channel 7
unsigned char channel_16 = 38; // Output to Opto Triac pin, channel 7

unsigned char CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8, CH9, CH10, CH11, CH12, CH13, CH14, CH15, CH16;
unsigned char CHANNEL_SELECT1;
unsigned char CHANNEL_SELECT2;
unsigned char i = 0;

// overall state  designating which act the sequence is currently in
int act = 0;

int j1 = 5;
int j2 = 5;
int j3 = 5;
int j4 = 5;
int j5 = 5;
int j6 = 5;
int j7 = 5;
int j8 = 5;
int j9 = 5;
int j10 = 5;
int j11 = 5;
int j12 = 5;
int j13 = 5;
int j14 = 5;
int j15 = 5;
int j16 = 5;

//initialize values for act 3
int ch1Val;
int ch2Val;
int ch3Val;
int ch4Val;
int ch5Val;
int ch6Val;
int ch7Val;
int ch8Val;
int ch9Val;
int ch10Val;
int ch11Val;
int ch12Val;
int ch13Val;
int ch14Val;
int ch15Val;

int chanArray[] = {5, 128};

volatile unsigned char clock_tick; // variable for Timer1

unsigned char low = 64;
unsigned char high = 5;
unsigned char off = 128;
long ptime;
long ptime1;
long ptime2;
long overallptime;
long endingptime;
long finalptime;
boolean forward = false;
int fsr1Pin = 0; // FSR is connected to analog 0
int fsr2Pin = 1; // FSR is connected to analog 1
int fsr3Pin = 2; // FSR is connected to analog 2
int fsr4Pin = 3; // FSR is connected to analog 3
int fsr5Pin = 4; // FSR is connected to analog 4

int fsr1Reading;
int fsr2Reading;
int fsr3Reading;
int fsr4Reading;
int fsr5Reading;

int fsr1State = 0;
int fsr2State = 0;
int fsr3State = 0;
int fsr4State = 0;
int fsr5State = 0;

int prevfsr1State = 0;
int prevfsr2State = 0;
int prevfsr3State = 0;
int prevfsr4State = 0;
int prevfsr5State = 0;

int fsr1ReadingState = 0;
int fsr2ReadingState = 0;
int fsr3ReadingState = 0;
int fsr4ReadingState = 0;
int fsr5ReadingState = 0;

int prevfsr1ReadingState = 0;
int prevfsr2ReadingState = 0;
int prevfsr3ReadingState = 0;
int prevfsr4ReadingState = 0;
int prevfsr5ReadingState = 0;

boolean bulb1Dim = false;
boolean bulb2Dim = false;
boolean bulb3Dim = false;
boolean bulb4Dim = false;
boolean bulb5Dim = false;
boolean bulb6Dim = false;
boolean bulb7Dim = false;
boolean bulb8Dim = false;
boolean bulb9Dim = false;
boolean bulb10Dim = false;
boolean bulb11Dim = false;
boolean bulb12Dim = false;
boolean bulb13Dim = false;
boolean bulb14Dim = false;
boolean bulb15Dim = false;
boolean bulb16Dim = false;
boolean openingAnimation = false;
boolean changeState = false;

int state1;
int state2;
int finalState;

int Delay1 = 25;
int Delay2 = 25;
int Delay3 = 25;
int Delay4 = 25;
int Delay5 = 25;
long overallDelay = 100000;
long finalDelay = 8000;
long delay_time1 = 300;
long delay_time2 = 500;
long endingDelay = 300;


void setup() {
  stripHand.begin();
  stripHand.setBrightness(50);
  stripHand.show();
  stripCircle.begin();
  stripCircle.setBrightness(50);
  stripCircle.show();

  Serial.begin(9600);
  pinMode(ctsPin, INPUT);

  pinMode(channel_1, OUTPUT);// Set AC Load pin as output
  pinMode(channel_2, OUTPUT);// Set AC Load pin as output
  pinMode(channel_3, OUTPUT);// Set AC Load pin as output
  pinMode(channel_4, OUTPUT);// Set AC Load pin as output
  pinMode(channel_5, OUTPUT);// Set AC Load pin as output
  pinMode(channel_6, OUTPUT);// Set AC Load pin as output
  pinMode(channel_7, OUTPUT);// Set AC Load pin as output
  pinMode(channel_8, OUTPUT);// Set AC Load pin as output
  pinMode(channel_9, OUTPUT);// Set AC Load pin as output
  pinMode(channel_10, OUTPUT);// Set AC Load pin as output
  pinMode(channel_11, OUTPUT);// Set AC Load pin as output
  pinMode(channel_12, OUTPUT);// Set AC Load pin as output
  pinMode(channel_13, OUTPUT);// Set AC Load pin as output
  pinMode(channel_14, OUTPUT);// Set AC Load pin as output
  pinMode(channel_15, OUTPUT);// Set AC Load pin as output
  pinMode(channel_16, OUTPUT);// Set AC Load pin as output

  attachInterrupt(1, zero_crosss_int, RISING);
  Timer1.initialize(83); // set a timer of length 100 microseconds for 200Hz or 83 microseconds for 60Hz;
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here
  ptime = millis();
}

void timerIsr()
{
  clock_tick++;

  if (CH1 == clock_tick)
  {
    digitalWrite(channel_1, HIGH); // triac firing
    delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_1, LOW); // triac Off
  }

  if (CH2 == clock_tick)
  {
    digitalWrite(channel_2, HIGH); // triac firing
    delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_2, LOW); // triac Off
  }

  if (CH3 == clock_tick )
  {
    digitalWrite(channel_3, HIGH); // triac firing
    delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_3, LOW); // triac Off
  }

  if (CH4 == clock_tick)
  {
    digitalWrite(channel_4, HIGH); // triac firing
    delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_4, LOW); // triac Off
  }

  if (CH5 == clock_tick)
  {
    digitalWrite(channel_5, HIGH); // triac firing
    delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_5, LOW); // triac Off
  }

  if (CH6 == clock_tick)
  {
    digitalWrite(channel_6, HIGH); // triac firing
    delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_6, LOW); // triac Off
  }

  if (CH7 == clock_tick)
  {
    digitalWrite(channel_7, HIGH); // triac firing
    delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_7, LOW); // triac Off
  }

  if (CH8 == clock_tick)
  {
    digitalWrite(channel_8, HIGH); // triac firing
    delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_8, LOW); // triac Off
  }

  if (CH9 == clock_tick)
  {
    digitalWrite(channel_9, HIGH); // triac firing
    delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_9, LOW); // triac Off
  }

  if (CH10 == clock_tick)
  {
    digitalWrite(channel_10, HIGH); // triac firing
    delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_10, LOW); // triac Off
  }

  if (CH11 == clock_tick )
  {
    digitalWrite(channel_11, HIGH); // triac firing
    delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_11, LOW); // triac Off
  }

  if (CH12 == clock_tick)
  {
    digitalWrite(channel_12, HIGH); // triac firing
    delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_12, LOW); // triac Off
  }

  if (CH13 == clock_tick)
  {
    digitalWrite(channel_13, HIGH); // triac firing
    delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_13, LOW); // triac Off
  }

  if (CH14 == clock_tick)
  {
    digitalWrite(channel_14, HIGH); // triac firing
    delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_14, LOW); // triac Off
  }

  if (CH15 == clock_tick)
  {
    digitalWrite(channel_15, HIGH); // triac firing
    delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_15, LOW); // triac Off
  }

  if (CH16 == clock_tick)
  {
    digitalWrite(channel_16, HIGH); // triac firing
    delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_16, LOW); // triac Off
  }

}



void zero_crosss_int() // function to be fired at the zero crossing to dim the light
{
  // Every zerocrossing interrupt: For 200Hz (1/2 Cycle) => 10ms ; For 60Hz (1/2 Cycle) => 8.33ms
  // 10ms=10000us , 8.33ms=8330us

  clock_tick = 0;
}

void loop() {

  //Initialization of neopixels turning on and off
  actZeroState();
  actOneState();
  actTwoState();
  actThreeState();

  //  fsr1Reading = analogRead(fsr1Pin);
  //  fsr2Reading = analogRead(fsr2Pin);
  //  fsr3Reading = analogRead(fsr3Pin);
  //  fsr4Reading = analogRead(fsr4Pin);
  //  fsr5Reading = analogRead(fsr5Pin);
  //    Serial.print(fsr1Reading);
  //    Serial.print(",");
  //    Serial.print(fsr2Reading);
  //    Serial.print(",");
  //    Serial.print(fsr3Reading);
  //    Serial.print(",");
  //    Serial.print(fsr4Reading);
  //    Serial.print(",");
  //    Serial.println(fsr5Reading);
  //
  //  fsr1StateChanges();
  //  fsr2StateChanges();
  //  fsr3StateChanges();
  //  fsr4StateChanges();
  //  fsr5StateChanges();
}





void fsr1StateChanges() {
  //  Serial.println(fsr1State);
  //  Serial.println(fsr1ReadingState);
  //  Serial.println(fsr1Reading);

  if (fsr1Reading >= 170) {
    fsr1ReadingState = 1;
  }

  if (fsr1Reading < 170) {
    fsr1ReadingState = 0;
  }

  if (fsr1ReadingState == 1) {
    if (prevfsr1ReadingState == 1) {}
    if (prevfsr1ReadingState == 0) {
      prevfsr1ReadingState = 1;
    }
  }

  if (fsr1ReadingState == 0) {
    if (prevfsr1ReadingState == 0) {}
    if (prevfsr1ReadingState == 1) {
      fsr1State ++;
      prevfsr1ReadingState = 0;
      //      Serial.println(fsr1State);
    }
  }

  // make sure that the correct state is reached for the first finger's fsr
  if (fsr1State == 0 || fsr1State == 1 || fsr1State == 2) {

    //if the finger isn't putting maximum pressure then the pulsing is mapped to the fsr



    if (fsr1Reading > 200 && fsr1Reading < 800 && !bulb1Dim ) {
      CH1 = 128 - fsr1Reading / 8;
    }


    //if the finger is putting max pressure then the pulsing becomes automated
    if (fsr1Reading >= 800 && bulb1Dim == false) {
      bulb1Dim = true;
      ptime = millis();
    }

    if (bulb1Dim) {
      if (millis() > ptime + Delay1) {
        CH1 = j1;

        if (j1 <= 5) {
          forward = true;
        }

        if (j1 >= 128) {
          forward = false;
        }

        if (forward) {
          j1++;
        } else {
          j1--;
        }
        ptime = millis();
      }
    }
  }

  if (fsr1State == 1 || fsr1State == 2) {

    //if the finger isn't putting maximum pressure then the pulsing is mapped to the fsr
    if (fsr1Reading > 200 && fsr1Reading < 800 && !bulb4Dim ) {
      CH4 = 128 - fsr1Reading / 8;
    }
    //if the finger is putting max pressure then the pulsing becomes automated
    if (fsr1Reading >= 800 && bulb4Dim == false) {
      //Serial.println("made it to state 1");

      bulb4Dim = true;
      ptime = millis();
      //      Serial.print("state 1 time");
      //      Serial.println(ptime);
    }

    if (bulb4Dim) {

      if (millis() > ptime + Delay1) {
        changeState = true;
        CH4 = j4;

        if (j4 <= 5) {
          forward = true;
        }

        if (j4 >= 128) {
          forward = false;
        }

        if (forward) {
          j4++;
        } else {
          j4--;
        }
        ptime = millis();
      }
    }
  }


  if (fsr1State == 2) {

    //if the finger isn't putting maximum pressure then the pulsing is mapped to the fsr
    if (fsr1Reading > 200 && fsr1Reading < 800 && !bulb9Dim ) {
      CH9 = 128 - fsr1Reading / 8;
    }
    //if the finger is putting max pressure then the pulsing becomes automated
    if (fsr1Reading >= 800 && bulb9Dim == false) {
      bulb9Dim = true;
      ptime = millis();
    }

    if (bulb9Dim) {
      if (millis() > ptime + Delay1) {
        changeState = true;
        CH9 = j9;

        if (j9 <= 5) {
          forward = true;
        }

        if (j9 >= 128) {
          forward = false;
        }

        if (forward) {
          j9++;
        } else {
          j9--;
        }
        ptime = millis();
      }
    }
  }


  fsr1State = fsr1State % 3;

}


//-----------------------------------------------------------------------------------------------------------

void fsr2StateChanges() {

  if (fsr2Reading >= 170) {
    fsr2ReadingState = 1;
  }

  if (fsr2Reading < 170) {
    fsr2ReadingState = 0;
  }

  if (fsr2ReadingState == 1) {
    if (prevfsr2ReadingState == 1) {}
    if (prevfsr2ReadingState == 0) {
      prevfsr2ReadingState = 1;
    }
  }

  if (fsr2ReadingState == 0) {
    if (prevfsr2ReadingState == 0) {}
    if (prevfsr2ReadingState == 1) {
      fsr2State ++;
      prevfsr2ReadingState = 0;
    }
  }

  // make sure that the correct state is reached for the first finger's fsr
  if (fsr2State == 0 || fsr2State == 1 || fsr2State == 2) {

    //if the finger isn't putting maximum pressure then the pulsing is mapped to the fsr
    if (fsr2Reading > 200 && fsr2Reading < 800 && !bulb11Dim ) {
      CH11 = 128 - fsr2Reading / 8;
    }
    //if the finger is putting max pressure then the pulsing becomes automated
    if (fsr2Reading >= 800 && bulb11Dim == false) {
      bulb11Dim = true;
      ptime = millis();
    }

    if (bulb11Dim) {
      if (millis() > ptime + Delay2) {
        CH11 = j11;

        if (j11 <= 5) {
          forward = true;
        }

        if (j11 >= 128) {
          forward = false;
        }

        if (forward) {
          j11++;
        } else {
          j11--;
        }
        ptime = millis();
      }
    }
  }

  if (fsr2State == 1 || fsr2State == 2) {

    //if the finger isn't putting maximum pressure then the pulsing is mapped to the fsr
    if (fsr2Reading > 200 && fsr2Reading < 800 && !bulb14Dim ) {
      CH14 = 128 - fsr2Reading / 8;
    }
    //if the finger is putting max pressure then the pulsing becomes automated
    if (fsr2Reading >= 800 && bulb14Dim == false) {
      //Serial.println("made it to state 1");

      bulb14Dim = true;
      ptime = millis();
      //      Serial.print("state 1 time");
      //      Serial.println(ptime);
    }

    if (bulb14Dim) {

      if (millis() > ptime + Delay2) {
        changeState = true;
        CH14 = j14;

        if (j14 <= 5) {
          forward = true;
        }

        if (j14 >= 128) {
          forward = false;
        }

        if (forward) {
          j14++;
        } else {
          j14--;
        }
        ptime = millis();
      }
    }
  }


  if (fsr2State == 2) {

    //if the finger isn't putting maximum pressure then the pulsing is mapped to the fsr
    if (fsr2Reading > 200 && fsr2Reading < 800 && !bulb5Dim ) {
      CH5 = 128 - fsr2Reading / 8;
    }
    //if the finger is putting max pressure then the pulsing becomes automated
    if (fsr2Reading >= 800 && bulb5Dim == false) {
      bulb5Dim = true;
      ptime = millis();
    }

    if (bulb5Dim) {
      if (millis() > ptime + Delay2) {
        changeState = true;
        CH5 = j5;

        if (j5 <= 5) {
          forward = true;
        }

        if (j5 >= 128) {
          forward = false;
        }

        if (forward) {
          j5++;
        } else {
          j5--;
        }
        ptime = millis();
      }
    }
  }


  fsr2State = fsr2State % 3;

}

//-----------------------------------------------------------------------------------------------------------------


void fsr3StateChanges() {

  if (fsr3Reading >= 170) {
    fsr3ReadingState = 1;
  }

  if (fsr3Reading < 170) {
    fsr3ReadingState = 0;
  }

  if (fsr3ReadingState == 1) {
    if (prevfsr3ReadingState == 1) {}
    if (prevfsr3ReadingState == 0) {
      prevfsr3ReadingState = 1;
    }
  }

  if (fsr3ReadingState == 0) {
    if (prevfsr3ReadingState == 0) {}
    if (prevfsr3ReadingState == 1) {
      fsr3State ++;
      prevfsr3ReadingState = 0;
    }
  }

  // make sure that the correct state is reached for the first finger's fsr
  if (fsr3State == 0 || fsr3State == 1 || fsr3State == 2) {

    //if the finger isn't putting maximum pressure then the pulsing is mapped to the fsr
    if (fsr3Reading > 200 && fsr3Reading < 800 && !bulb15Dim ) {
      CH15 = 128 - fsr3Reading / 8;
    }
    //if the finger is putting max pressure then the pulsing becomes automated
    if (fsr3Reading >= 800 && bulb15Dim == false) {
      bulb15Dim = true;
      ptime = millis();
    }

    if (bulb15Dim) {
      if (millis() > ptime + Delay3) {
        CH15 = j15;

        if (j15 <= 5) {
          forward = true;
        }

        if (j15 >= 128) {
          forward = false;
        }

        if (forward) {
          j15++;
        } else {
          j15--;
        }
        ptime = millis();
      }
    }
  }

  if (fsr3State == 1 || fsr3State == 2) {

    //if the finger isn't putting maximum pressure then the pulsing is mapped to the fsr
    if (fsr3Reading > 200 && fsr3Reading < 800 && !bulb10Dim ) {
      CH10 = 128 - fsr3Reading / 8;
    }
    //if the finger is putting max pressure then the pulsing becomes automated
    if (fsr3Reading >= 800 && bulb10Dim == false) {
      //Serial.println("made it to state 1");

      bulb10Dim = true;
      ptime = millis();
      //      Serial.print("state 1 time");
      //      Serial.println(ptime);
    }

    if (bulb10Dim) {

      if (millis() > ptime + Delay3) {
        changeState = true;
        CH10 = j10;

        if (j10 <= 5) {
          forward = true;
        }

        if (j10 >= 128) {
          forward = false;
        }

        if (forward) {
          j10++;
        } else {
          j10--;
        }
        ptime = millis();
      }
    }
  }


  if (fsr3State == 2) {

    //if the finger isn't putting maximum pressure then the pulsing is mapped to the fsr
    if (fsr3Reading > 200 && fsr3Reading < 800 && !bulb2Dim ) {
      CH2 = 128 - fsr3Reading / 8;
    }
    //if the finger is putting max pressure then the pulsing becomes automated
    if (fsr3Reading >= 800 && bulb2Dim == false) {
      bulb2Dim = true;
      ptime = millis();
    }

    if (bulb2Dim) {
      if (millis() > ptime + Delay3) {
        changeState = true;
        CH2 = j2;

        if (j2 <= 5) {
          forward = true;
        }

        if (j2 >= 128) {
          forward = false;
        }

        if (forward) {
          j2++;
        } else {
          j2--;
        }
        ptime = millis();
      }
    }
  }


  fsr3State = fsr3State % 3;

}

//-----------------------------------------------------------------------------------------------------------------

void fsr4StateChanges() {

  if (fsr4Reading >= 170) {
    fsr4ReadingState = 1;
  }

  if (fsr4Reading < 170) {
    fsr4ReadingState = 0;
  }

  if (fsr4ReadingState == 1) {
    if (prevfsr4ReadingState == 1) {}
    if (prevfsr4ReadingState == 0) {
      prevfsr4ReadingState = 1;
    }
  }

  if (fsr4ReadingState == 0) {
    if (prevfsr4ReadingState == 0) {}
    if (prevfsr4ReadingState == 1) {
      fsr4State ++;
      prevfsr4ReadingState = 0;
    }
  }

  // make sure that the correct state is reached for the first finger's fsr
  if (fsr4State == 0 || fsr4State == 1 || fsr4State == 2) {

    //if the finger isn't putting maximum pressure then the pulsing is mapped to the fsr
    if (fsr4Reading > 200 && fsr4Reading < 800 && !bulb7Dim ) {
      CH7 = 128 - fsr4Reading / 8;
    }
    //if the finger is putting max pressure then the pulsing becomes automated
    if (fsr4Reading >= 800 && bulb7Dim == false) {
      bulb7Dim = true;
      ptime = millis();
    }

    if (bulb7Dim) {
      if (millis() > ptime + Delay4) {
        CH7 = j7;

        if (j7 <= 5) {
          forward = true;
        }

        if (j7 >= 128) {
          forward = false;
        }

        if (forward) {
          j7++;
        } else {
          j7--;
        }
        ptime = millis();
      }
    }
  }

  if (fsr4State == 1 || fsr4State == 2) {

    //if the finger isn't putting maximum pressure then the pulsing is mapped to the fsr
    if (fsr4Reading > 200 && fsr4Reading < 800 && !bulb13Dim ) {
      CH13 = 128 - fsr4Reading / 8;
    }
    //if the finger is putting max pressure then the pulsing becomes automated
    if (fsr4Reading >= 800 && bulb13Dim == false) {
      //Serial.println("made it to state 1");

      bulb13Dim = true;
      ptime = millis();

    }

    if (bulb13Dim) {

      if (millis() > ptime + Delay4) {
        changeState = true;
        CH13 = j13;

        if (j13 <= 5) {
          forward = true;
        }

        if (j13 >= 128) {
          forward = false;
        }

        if (forward) {
          j13++;
        } else {
          j13--;
        }
        ptime = millis();
      }
    }
  }


  if (fsr4State == 2) {

    //if the finger isn't putting maximum pressure then the pulsing is mapped to the fsr
    if (fsr4Reading > 200 && fsr4Reading < 800 && !bulb3Dim ) {
      CH3 = 128 - fsr4Reading / 8;
    }
    //if the finger is putting max pressure then the pulsing becomes automated
    if (fsr4Reading >= 800 && bulb3Dim == false) {
      bulb3Dim = true;
      ptime = millis();
    }

    if (bulb3Dim) {
      if (millis() > ptime + Delay4) {
        changeState = true;
        CH3 = j3;

        if (j3 <= 5) {
          forward = true;
        }

        if (j3 >= 128) {
          forward = false;
        }

        if (forward) {
          j3++;
        } else {
          j3--;
        }
        ptime = millis();
      }
    }
  }


  fsr4State = fsr4State % 3;

}

//-------------------------------------------------------------------------------------------------------------------------

void fsr5StateChanges() {

  if (fsr5Reading >= 170) {
    fsr5ReadingState = 1;
  }

  if (fsr5Reading < 170) {
    fsr5ReadingState = 0;
  }

  if (fsr5ReadingState == 1) {
    if (prevfsr5ReadingState == 1) {}
    if (prevfsr5ReadingState == 0) {
      prevfsr5ReadingState = 1;
    }
  }

  if (fsr5ReadingState == 0) {
    if (prevfsr5ReadingState == 0) {}
    if (prevfsr5ReadingState == 1) {
      fsr5State ++;
      prevfsr5ReadingState = 0;
    }
  }

  // make sure that the correct state is reached for the first finger's fsr
  if (fsr5State == 0 || fsr5State == 1 || fsr5State == 2) {

    //if the finger isn't putting maximum pressure then the pulsing is mapped to the fsr
    if (fsr5Reading > 200 && fsr5Reading < 800 && !bulb6Dim ) {
      CH6 = 128 - fsr5Reading / 8;
    }
    //if the finger is putting max pressure then the pulsing becomes automated
    if (fsr5Reading >= 800 && bulb6Dim == false) {
      bulb6Dim = true;
      ptime = millis();
    }

    if (bulb6Dim) {
      if (millis() > ptime + Delay5) {
        CH6 = j6;

        if (j6 <= 5) {
          forward = true;
        }

        if (j6 >= 128) {
          forward = false;
        }

        if (forward) {
          j6++;
        } else {
          j6--;
        }
        ptime = millis();
      }
    }
  }

  if (fsr5State == 1 || fsr5State == 2) {

    //if the finger isn't putting maximum pressure then the pulsing is mapped to the fsr
    if (fsr5Reading > 200 && fsr5Reading < 800 && !bulb12Dim ) {
      CH12 = 128 - fsr5Reading / 8;
    }
    //if the finger is putting max pressure then the pulsing becomes automated
    if (fsr5Reading >= 800 && bulb12Dim == false) {
      //Serial.println("made it to state 1");

      bulb12Dim = true;
      ptime = millis();

    }

    if (bulb12Dim) {

      if (millis() > ptime + Delay5) {
        changeState = true;
        CH12 = j12;

        if (j12 <= 5) {
          forward = true;
        }

        if (j12 >= 128) {
          forward = false;
        }

        if (forward) {
          j12++;
        } else {
          j12--;
        }
        ptime = millis();
      }
    }
  }


  if (fsr5State == 2) {

    //if the finger isn't putting maximum pressure then the pulsing is mapped to the fsr
    if (fsr5Reading > 200 && fsr5Reading < 800 && !bulb8Dim ) {
      CH8 = 128 - fsr5Reading / 8;
    }
    //if the finger is putting max pressure then the pulsing becomes automated
    if (fsr5Reading >= 800 && bulb8Dim == false) {
      bulb8Dim = true;
      ptime = millis();
    }

    if (bulb8Dim) {
      if (millis() > ptime + Delay5) {
        changeState = true;
        CH8 = j8;

        if (j8 <= 5) {
          forward = true;
        }

        if (j8 >= 128) {
          forward = false;
        }

        if (forward) {
          j8++;
        } else {
          j8--;
        }
        ptime = millis();
      }
    }
  }


  fsr5State = fsr5State % 3;
}

void initialHandInteraction() {
  sensorReading = digitalRead(ctsPin);
  stripHandOn();
  Serial.println(sensorReading);
  //  Serial.println("Hand interation!");
  if (sensorReading == 0 && circleOff == false) {
    stripCircleOn();
    //    Serial.println("Sensor read is 0!");
  }

  if (sensorReading == 1 && circleOff == false) {
    //    Serial.println(sensorReading);
    //    Serial.println("Sensor read is 1!");
    ptime1 = millis();
    circleOff = true;
    state1 = 0;
    act = 1;
    //    delay(1);
  }

  if (circleOff) {
    stripCircleOff();
  }
}

void stripHandOn() {
  for (int i = 0; i < 20; i++ ) {
    stripHand.setPixelColor(i, 255, 150, 50);
    stripHand.show();
  }
}

void stripHandOff() {
  //  Serial.println("turning off pixels for hand");
  for (int i = 0; i < 20; i++ ) {
    stripHand.setPixelColor(i, 0);
    stripHand.show();
  }
}

void stripCircleOn() {
  for (int i = 0; i < 12; i++ ) {
    stripCircle.setPixelColor(i, 255, 150, 50);
    stripCircle.show();
  }
}

void stripCircleOff() {
  for (int i = 0; i < 12; i++ ) {
    stripCircle.setPixelColor(i, 0);
    stripCircle.show();
  }
}

void actZeroState() {
  if (act == 0) {
    CH1 = off; CH2 = off; CH3 = off; CH4 = off; CH5 = off; CH6 = off; CH7 = off; CH8 = off; CH9 = off;
    CH10 = off; CH11 = off; CH12 = off; CH13 = off; CH14 = off; CH15 = off;
    //    Serial.println("Act 0!");
    initialHandInteraction();
  }
}

void actOneState() {
  if (act == 1) {
    if (millis() - ptime1 > delay_time1) {
      state1++;
      ptime1 = millis();
    }
    //    Serial.println("Act 1!");
    //lights turn on from 1 - 15

    if (state1 == 0) {
      CH1 = low;
    }
    //    delay(25);
    if (state1 == 1) {
      CH2 = high; CH1 = off;
    }
    //    delay(25);
    if (state1 == 2) {
      CH3 = high; CH2 = off;
    }
    //    delay(25);
    if (state1 == 3) {
      CH4 = high; CH3 = off;
    }
    //    delay(25);
    if (state1 == 4) {
      CH5 = high; CH4 = off;
    }
    //    delay(25);
    if (state1 == 5) {
      CH6 = high; CH5 = off;
    }
    //    delay(25);
    if (state1 == 6) {
      CH7 = high; CH6 = off;
    }
    //    delay(25);
    if (state1 == 7) {
      CH8 = high; CH7 = off;
    }
    //    delay(25);
    if (state1 == 8) {
      CH9 = high; CH8 = off;
    }
    //    delay(25);
    if (state1 == 9) {
      CH10 = high; CH9 = off;
    }
    //    delay(25);
    if (state1 == 10) {
      CH11 = high; CH10 = off;
    }
    //    delay(25);
    if (state1 == 11) {
      CH12 = high; CH11 = off;
    }
    //    delay(25);
    if (state1 == 12) {
      CH13 = high; CH12 = off;
    }
    //    delay(25);
    if (state1 == 13) {
      CH14 = high; CH13 = off;
    }
    //    delay(25);
    if (state1 == 14) {
      CH15 = high; CH14 = off;
    }
    //    delay(25);

    //turn lights on from 15 - 1
    if (state1 == 15) {
      CH15 = high;
    }
    //    delay(25);
    if (state1 == 16) {
      CH14 = high; CH15 = off;
    }
    //    delay(25);
    if (state1 == 17) {
      CH13 = high; CH14 = off;
    }
    //    delay(25);
    if (state1 == 18) {
      CH12 = high; CH13 = off;
    }
    //    delay(25);
    if (state1 == 19) {
      CH11 = high; CH12 = off;
    }
    //    delay(25);
    if (state1 == 20) {
      CH10 = high; CH11 = off;
    }
    //    delay(25);
    if (state1 == 21) {
      CH9 = high; CH10 = off;
    }
    //    delay(25);
    if (state1 == 22) {
      CH8 = high; CH9 = off;
    }
    //    delay(25);
    if (state1 == 23) {
      CH7 = high; CH8 = off;
    }
    //    delay(25);
    if (state1 == 24) {
      CH6 = high; CH7 = off;
    }
    //    delay(25);
    if (state1 == 25) {
      CH5 = high; CH6 = off;
    }
    //    delay(25);
    if (state1 == 26) {
      CH4 = high; CH5 = off;
    }
    //    delay(25);
    if (state1 == 27) {
      CH3 = high; CH4 = off;
    }
    //    delay(25);
    if (state1 == 28) {
      CH2 = high; CH3 = off;
    }
    //    delay(25);
    if (state1 == 29) {
      CH1 = high; CH2 = off;
    }
    //    delay(25);
    if (state1 == 30) {
      CH1 = off;
      ptime2 = millis();
      state2 = 0;
      openingAnimation = true;
    }

    if (openingAnimation) {
      if (millis() - ptime2 > delay_time2) {
        state2++;
        ptime2 = millis();
      }
      if (state2 == 0) {
        CH1 = high; CH2 = off; CH3 = off; CH4 = off; CH5 = off; CH6 = high; CH7 = off; CH8 = off;
        CH9 = off; CH10 = high; CH11 = off; CH12 = off; CH13 = high; CH14 = off; CH15 = off;
      }

      if (state2 == 1) {
        CH1 = off; CH2 = off; CH3 = high; CH4 = off; CH5 = off; CH6 = off; CH7 = off; CH8 = high;
        CH9 = off; CH10 = off; CH11 = off; CH12 = off; CH13 = off; CH14 = off; CH15 = high;
      }

      if (state2 == 2) {
        CH1 = off; CH2 = high; CH3 = off; CH4 = off; CH5 = high; CH6 = off; CH7 = high; CH8 = off;
        CH9 = high; CH10 = off; CH11 = off; CH12 = high; CH13 = off; CH14 = off; CH15 = off;
      }

      if (state2 == 3) {
        CH1 = off; CH2 = off; CH3 = high; CH4 = high; CH5 = off; CH6 = off; CH7 = high; CH8 = off;
        CH9 = off; CH10 = off; CH11 = high; CH12 = off; CH13 = off; CH14 = off; CH15 = off;
      }

      if (state2 == 4) {
        CH1 = high; CH2 = off; CH3 = off; CH4 = off; CH5 = off; CH6 = high; CH7 = off; CH8 = off;
        CH9 = off; CH10 = high; CH11 = off; CH12 = high; CH13 = off; CH14 = off; CH15 = high;
      }

      if (state2 == 5) {
        CH1 = off; CH2 = off; CH3 = off; CH4 = off; CH5 = high; CH6 = off; CH7 = off; CH8 = high;
        CH9 = off; CH10 = off; CH11 = high; CH12 = off; CH13 = off; CH14 = high; CH15 = off;
      }

      if (state2 == 6) {
        CH1 = off; CH2 = high; CH3 = high; CH4 = off; CH5 = high; CH6 = off; CH7 = off; CH8 = off;
        CH9 = high; CH10 = high; CH11 = off; CH12 = off; CH13 = off; CH14 = off; CH15 = off;
      }

      if (state2 == 7) {
        CH1 = high; CH2 = off; CH3 = off; CH4 = high; CH5 = off; CH6 = off; CH7 = high; CH8 = off;
        CH9 = off; CH10 = off; CH11 = off; CH12 = off; CH13 = high; CH14 = off; CH15 = off;
      }

      if (state2 == 8) {
        CH1 = off; CH2 = off; CH3 = off; CH4 = off; CH5 = off; CH6 = high; CH7 = off; CH8 = high;
        CH9 = off; CH10 = high; CH11 = off; CH12 = high; CH13 = off; CH14 = off; CH15 = high;
      }

      if (state2 == 9) {
        CH1 = off; CH2 = high; CH3 = off; CH4 = off; CH5 = high; CH6 = off; CH7 = off; CH8 = high;
        CH9 = off; CH10 = off; CH11 = high; CH12 = off; CH13 = off; CH14 = high; CH15 = off;
      }

      if (state2 == 10) {
        CH1 = high; CH2 = off; CH3 = off; CH4 = high; CH5 = off; CH6 = off; CH7 = high; CH8 = off;
        CH9 = off; CH10 = off; CH11 = high; CH12 = off; CH13 = high; CH14 = off; CH15 = high;
      }

      if (state2 == 11) {
        CH1 = off; CH2 = off; CH3 = high; CH4 = off; CH5 = high; CH6 = high; CH7 = off; CH8 = off;
        CH9 = off; CH10 = high; CH11 = off; CH12 = off; CH13 = off; CH14 = high; CH15 = off;
      }

      if (state2 == 12) {
        CH1 = off; CH2 = high; CH3 = off; CH4 = off; CH5 = high; CH6 = off; CH7 = high; CH8 = off;
        CH9 = high; CH10 = off; CH11 = off; CH12 = high; CH13 = high; CH14 = off; CH15 = off;
      }

      if (state2 == 13) {
        CH1 = high; CH2 = off; CH3 = high; CH4 = off; CH5 = off; CH6 = off; CH7 = off; CH8 = high;
        CH9 = off; CH10 = off; CH11 = high; CH12 = high; CH13 = off; CH14 = high; CH15 = off;
      }

      if (state2 == 14) {
        CH1 = off; CH2 = off; CH3 = off; CH4 = off; CH5 = off; CH6 = off; CH7 = off; CH8 = off;
        CH9 = off; CH10 = off; CH11 = off; CH12 = off; CH13 = off; CH14 = off; CH15 = off;
      }

      if (state2 == 15) {
        overallptime = millis();
        act = 2;
      }
    }
  }
}

void actTwoState() {

  if (act == 2) {
    fsr1Reading = analogRead(fsr1Pin);
    fsr2Reading = analogRead(fsr2Pin);
    fsr3Reading = analogRead(fsr3Pin);
    fsr4Reading = analogRead(fsr4Pin);
    fsr5Reading = analogRead(fsr5Pin);
    fsr1StateChanges();
    fsr2StateChanges();
    fsr3StateChanges();
    fsr4StateChanges();
    fsr5StateChanges();
    if (millis() > overallptime + overallDelay) {
      finalptime = millis();
      endingptime = millis();
      finalState = 0;
      act = 3;
    }
  }
}

void actThreeState() {
  if (act == 3) {

    //    for (int i = 0; i < 10; i++) {
    //    if (millis() - endingptime > endingDelay) {
    finalState++;
    //      endingptime = millis();
    //    }


    if (finalState == 0) {

      ch1Val = j1;
      ch2Val = j2;
      ch3Val = j3;
      ch4Val = j4;
      ch5Val = j5;
      ch6Val = j6;
      ch7Val = j7;
      ch8Val = j8;
      ch9Val = j9;
      ch10Val = j10;
      ch11Val = j11;
      ch12Val = j12;
      ch13Val = j13;
      ch14Val = j14;
      ch15Val = j15;

      for (int i = 0 ; i < 128; i++) {
        CH1 = constrain(ch1Val + i, 5, 128);
        CH2 = constrain(ch2Val + i, 5, 128);
        CH3 = constrain(ch3Val + i, 5, 128);
        CH4 = constrain(ch4Val + i, 5, 128);
        CH5 = constrain(ch5Val + i, 5, 128);
        CH6 = constrain(ch6Val + i, 5, 128);
        CH7 = constrain(ch7Val + i, 5, 128);
        CH8 = constrain(ch8Val + i, 5, 128);
        CH9 = constrain(ch9Val + i, 5, 128);
        CH10 = constrain(ch10Val + i, 5, 128);
        CH11 = constrain(ch11Val + i, 5, 128);
        CH12 = constrain(ch12Val + i, 5, 128);
        CH13 = constrain(ch13Val + i, 5, 128);
        CH14 = constrain(ch14Val + i, 5, 128);
        CH15 = constrain(ch15Val + i, 5, 128);
        delay(100);
        finalState++;
      }
    }

    if (millis() > finalptime + finalDelay) {
      act = 0;
      circleOff = false;

    }
  }
}
