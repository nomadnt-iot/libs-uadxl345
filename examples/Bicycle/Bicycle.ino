#include <avr/power.h>
#include <uADXL345.h>

#include <FastLED.h>
//#include <TinyDebugSerial.h>

#define NUM_LEDS 5
#define DATA_PIN 3

uADXL345 adxl = uADXL345();
CRGB leds[NUM_LEDS];
//TinyDebugSerial mySerial = TinyDebugSerial();

int x, y, z = 0;

void setup(){
    // if(F_CPU == 16000000){
    //     clock_prescale_set(clock_div_1);
    // }else if(F_CPU == 8000000){
    //     clock_prescale_set(clock_div_1);
    // }else if(F_CPU == 4000000){
    //     clock_prescale_set(clock_div_2);
    // }else if(F_CPU == 2000000){
    //     clock_prescale_set(clock_div_4);
    // }else if(F_CPU == 1000000){
    //     clock_prescale_set(clock_div_8);
    // }

    //mySerial.begin(9600);

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    // for(uint8_t i = 0; i < 20; i++){ stop(); }
    // for(uint8_t i = 0; i < 20; i++){ left(); }
    // for(uint8_t i = 0; i < 20; i++){ right(); }

    adxl.powerOn();
    adxl.setRangeSetting(16);
    // adxl.setActivityXYZ(1, 0, 0);
    // adxl.setActivityThreshold(75);
    // adxl.setInactivityXYZ(1, 0, 0);
    // adxl.setInactivityThreshold(75);
    // adxl.setTimeInactivity(10);
}

/****************** MAIN CODE ******************/
/*     Accelerometer Readings and Interrupt    */
void loop(){
    // Accelerometer Readings
    int gx, gy, gz;

    adxl.readAccel(&gx, &gy, &gz);         // Read the accelerometer values and store them in variables declared above gx,gy,gz

    // int ax = 180 * atan(gx / sqrt(gy * gy + gz * gz))/M_PI;                     // working
    // int ay = 180 * atan(gy / sqrt(gx * gx + gz * gz))/M_PI;                     // working
    // int ax = 180 * atan(gx / sqrt(sq(gy) + sq(gz)))/M_PI;                       // working
    // int ay = 180 * atan(gy / sqrt(sq(gx) + sq(gz)))/M_PI;                       // working

    if(gy > 10){
        stop();
    }else{
        if(gx > 15){
            left();
        }
        if(gx < -15){
            right();
        }
    }

    x = gx;
    y = gy;
    z = gz;

    //debug();

    delay(50);
}

// void debug(){
//     mySerial.print(x);
//     mySerial.print(", ");
//     mySerial.print(y);
//     mySerial.print(", ");
//     mySerial.print(z);
//     mySerial.println();
// }

void right(){
    for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB::Orange;
        FastLED.show();
        FastLED.delay(50);
        //delay(50);
    }

    for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB::Black;
        FastLED.show();
        FastLED.delay(50);
        //delay(50);
    }
}

void left(){
    for(int i = 0; i < NUM_LEDS; i++){
        leds[4 - i] = CRGB::Orange;
        FastLED.show();
        FastLED.delay(50);
        //delay(50);
    }

    for(int i = 0; i < NUM_LEDS; i++){
        leds[4 - i] = CRGB::Black;
        FastLED.show();
        FastLED.delay(50);
        //delay(50);
    }
}

void stop(){
    for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB::Red;
    }
    FastLED.show();
    FastLED.delay(100);
    //delay(100);

    for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB::Black;
    }
    FastLED.show();
    FastLED.delay(100);
    //delay(100);
}
