#include "Particle.h"
#include "ArduinoJson.h"
#include "Firebase.h"

Firebase *firebase;

int bluePin = D0;
int redPin = D1;
int greenPin = D2;
int r;
int g;
int b;
int d;

const unsigned long CHECK_PERIOD_MS = 10000;
const unsigned long FIRST_CHECK_MS = 5000;

unsigned long lastPublish = FIRST_CHECK_MS - CHECK_PERIOD_MS;

void setup() {
	Serial.begin(9600);

    firebase = new Firebase("test3rdata");
    firebase->subscribe();
    firebase->setCallback(readCallback);

    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    r = 0;
    g = 0;
    b = 255;

    d = 500;
}

char buf[256];

void loop() {
	if (millis() - lastPublish >= CHECK_PERIOD_MS) {
		lastPublish = millis();

		Serial.printlnf("Publish");

	    snprintf(buf, sizeof(buf), "{\"a\":%d,\"b\":%d,\"c\":%d}", r, b, b);

	    firebase->readData();
		firebase->publishData("test1data", buf);
	}

	setColor(r, g, b);
	delay(d);
	setColor(0, 0, 0);
	delay(d);
}


void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void readCallback(JsonObject& root)
{
	r = root["r"];
	g = root["g"];
	b = root["b"];
	int td = root["d"];

	if (td > 50) {
	    d = td;
	}

	Serial.printlnf("Yes! r=%d g=%d b=%d d=%d", r, g, b, d);
}