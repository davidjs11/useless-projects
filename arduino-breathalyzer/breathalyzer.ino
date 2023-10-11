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

#define SENSOR_PIN A0

float sensorVal;

void setup()
{

    // iniciar el sensor
    Serial.begin(9600);
    pinMode(SENSOR_PIN, INPUT);
    delay(20000); // calentarlo
}

void loop()
{
    float adcValue = 0; 
    for(int i = 0; i < 20; i++){
        adcValue = analogRead(SENSOR_PIN);
        delay(10);
    }

    float val = (adcValue/20) * (5.0/1024.0);
    float mgL = 0.67 * val;

    // leer valor del sensor
    Serial.print(mgL);
    Serial.print(" mgL");
    Serial.println();
}
