#include <DHT.h>
#include <DHT_U.h>

#include <Adafruit_Sensor.h>

#define DHTPIN 3

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int Led1 = 13;
int Led2 = 12;
int Led3 = 11;

const int triggerPin = 9;
const int echoPin = 10;

void setup() {
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    float duration = pulseIn(echoPin, HIGH);

    int distance = duration * 0.034/2;

    if(distance < 7)
    {
        digitalWrite(Led1, HIGH);
        digitalWrite(Led2, HIGH);
        digitalWrite(Led3, HIGH);
    }
    else if(distance >= 7 && distance < 15)
    {
        digitalWrite(Led1, HIGH);
        digitalWrite(Led2, HIGH);
        digitalWrite(Led3, LOW);
    }
    else if(distance >= 15 && distance < 25)
    {
        digitalWrite(Led1, HIGH);
        digitalWrite(Led2, LOW);
        digitalWrite(Led3, LOW);
    }
    else
    {
        digitalWrite(Led1, LOW);
        digitalWrite(Led2, LOW);
        digitalWrite(Led3, LOW);
    }

    float h = dht.readHumidity();

    float t = dht.readTemperature();

    float hic = dht.computeHeatIndex(t, h, false);

    Serial.println(String(t)+","+String(h)+","+String(hic));
}
