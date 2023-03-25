///////////////////////////////////////////////////
///                                             ///
///  How to connect it:                         ///
///     - Connect the GND to the GND (wow)      ///
///     - Connect the Vcc to the 5V output      ///
///     - Connect the analog pin to SENSOR_PORT ///
///                                             ///
///   You must wait for the sensor to heat up   ///
///  to make sure it works correctly. It takes  ///
///  around 20 seconds.                         ///
///                                             ///
///////////////////////////////////////////////////

#define SENSOR_PIN A0 // this pin must be analog
float sensorVal;

void setup()
{
    Serial.begin(9600); // init the serial port
    pinMode(SENSOR_PIN, INPUT); // init the analog pin.

    // wait for the sensor to heat up
    Serial.println("heating up sensor...");
    delay(20000);
    Serial.println("done!");
}

void loop()
{
    // read the alcohol level
    sensorVal = analogRead(SENSOR_PIN);

    // print the value
    Serial.print("alcohol: ");
    Serial.println(sensorVal);
    delay(500);
}

// yeah that's all. what did you expect? a really complex code??
