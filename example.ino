// This #include statement was automatically added by the Particle IDE.
#include "Firebase.h"
#include "Particle.h"

#include "ArduinoJson.h"
// Test Program #3 for Firebase Integration
// Reads data from the database and prints it to the debug serial port

// Requires the SparkJson library:
// https://github.com/menan/SparkJson

#include "Firebase.h"

int bluePin = D0;
int redPin = D1;
int greenPin = D2;
int r;
int g;
int b;
int d;

Firebase *firebase;

// Forward declarations
void getDataHandler(const char *topic, const char *data);


const unsigned long CHECK_PERIOD_MS = 10000;
const unsigned long FIRST_CHECK_MS = 5000;

unsigned long lastPublish = FIRST_CHECK_MS - CHECK_PERIOD_MS;

void setup() {
    firebase = new Firebase("test3rdata");
	Serial.begin(9600);
// 	Particle.subscribe("hook-response/test3rdata", getDataHandler, MY_DEVICES);
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