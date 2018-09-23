#include <TinyDebugSerial.h>
#include <uADXL345.h>

TinyDebugSerial mySerial = TinyDebugSerial();
uADXL345 gyro = uADXL345();

void setup(){
    mySerial.begin(9600);

    gyro.powerOn();
    gyro.setRangeSetting(16);
    gyro.setActivityXYZ(1, 0, 0);
    gyro.setActivityThreshold(75);
    gyro.setInactivityXYZ(1, 0, 0);
    gyro.setInactivityThreshold(75);
    gyro.setTimeInactivity(10);
    gyro.setTapDetectionOnXYZ(0, 0, 1);
    gyro.setTapThreshold(50);
    gyro.setTapDuration(15);
    gyro.setDoubleTapLatency(80);
    gyro.setDoubleTapWindow(200);
    gyro.setFreeFallThreshold(7);
    gyro.setFreeFallDuration(30);
    gyro.InactivityINT(1);
    gyro.ActivityINT(1);
    gyro.FreeFallINT(1);
    gyro.doubleTapINT(1);
    gyro.singleTapINT(1);
}

void loop(){
    int x,y,z;
    gyro.readAccel(&x, &y, &z);

    // Output Results to Serial
    /* UNCOMMENT TO VIEW X Y Z ACCELEROMETER VALUES */
    mySerial.print(x);
    mySerial.print(", ");
    mySerial.print(y);
    mySerial.print(", ");
    mySerial.print(z);
    mySerial.println();
    delay(50);

    //ADXL_ISR();
    // You may also choose to avoid using interrupts and simply run the functions within ADXL_ISR();
    // and place it within the loop instead.
    // This may come in handy when it doesn't matter when the action occurs.
}

void ADXL_ISR() {
    // getInterruptSource clears all triggered actions after returning value
    // Do not call again until you need to recheck for triggered actions
    byte interrupts = gyro.getInterruptSource();

    // Free Fall Detection
    if(gyro.triggered(interrupts, ADXL345_FREE_FALL)){
        Serial.println("*** FREE FALL ***");
        //add code here to do when free fall is sensed
    }

    // Inactivity
    if(gyro.triggered(interrupts, ADXL345_INACTIVITY)){
        Serial.println("*** INACTIVITY ***");
        //add code here to do when inactivity is sensed
    }

    // Activity
    if(gyro.triggered(interrupts, ADXL345_ACTIVITY)){
        Serial.println("*** ACTIVITY ***");
        //add code here to do when activity is sensed
    }

    // Double Tap Detection
    if(gyro.triggered(interrupts, ADXL345_DOUBLE_TAP)){
        Serial.println("*** DOUBLE TAP ***");
        //add code here to do when a 2X tap is sensed
    }

    // Tap Detection
    if(gyro.triggered(interrupts, ADXL345_SINGLE_TAP)){
        Serial.println("*** TAP ***");
        //add code here to do when a tap is sensed
    }
}
