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
#define MAX_ARBITRARIO 600
#include<LiquidCrystal.h>


float sensorVal, adcValue, val, mgL;
float initialValue;

float val_min, val_act, val_max = MAX_ARBITRARIO;
float m, n, res;

int rs = 13;
int E = 11;
int D4 = 5, D5 = 4; D6 = 3, D7 = 2;
LiquidCrystal lcd(rs, E, D4, D5, D6, D7);

int buzzPin = 8;



void setup()
{
    // iniciar el sensor
    Serial.begin(9600);
    pinMode(SENSOR_PIN, INPUT);
    delay(2000); // calentarlo
    
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Alcoholímetro");

    delay(3000);
    lcd.clear();

    pinMode(buzzPin, OUTPUT);

    // tomar valor inicial (SIN ALCOHOL) (2seg)
    for(int i=0; i<200; i++) {
        val_min += analogRead(SENSOR_PIN);
        delay(10);
    }
    val_min /= 200;
}

float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

void loop()
{   

    Serial.print("min: ");
    Serial.print(val_min);
    Serial.print("\tact: ");
    Serial.print(val_act);
    Serial.print("\tmax: ");
    Serial.print(val_max);
    Serial.print("\tres: ");
    Serial.println(res);


    // tomar valor actual (media)
    for(int i=0; i<20; i++) {
        val_act += analogRead(SENSOR_PIN);
        delay(10);
    }
    val_act /= 20;

    // comparar con el máximo y con el minimo
    if (val_act >= val_max)
        val_max = val_act;

    if (val_act <= val_min)
        val_min = val_act;


    // Calcular la relación lineal
    // m = 10.0f / (val_max - val_min);
    // n = -10.0f * val_min / (val_max - val_min);
    // res = m * (val_act + n);
    res = mapFloat(val_act, val_min, val_max, 0.0, 10.0f);

    digitalWrite(buzzPin, HIGH);
    delayMicroseconds(100);
          digitalWrite(buzzPin, LOW);

    lcd.print(res);
    delay(250);
    lcd.clear();

}

/*
void loop()
{
    adcValue = 0; 

    Serial.print("Inicio de medida");
    Serial.println();
    delay(1000);

    for(int i = 0; i < 20; ++i){
        adcValue += analogRead(SENSOR_PIN);
        delay(100);
    }

    val = (adcValue/20.0) * (5.0/1024.0);
    mgL = 0.67 * val;

    Serial.print("Fin de medición");
    Serial.println();
    delay(3000);

      // leer valor del sensor
    Serial.print(mgL);
    Serial.print(" mgL");
    Serial.println();
}
*/




/*oid loop()
{
    adcValue = 0;
    delay(100)
    initialValue = analogRead(SENSOR_PIN);

    // tomar 20 medidas
    for(int i=0; i<20; i++) {
        adcValue += analogRead(SENSOR_PIN);
        delay(100);
    }

    // realizar la media
    val = adcValue;
    mgL = 0.28777219 * val;

    Serial.println(mgL);
}*/
