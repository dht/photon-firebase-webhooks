#include "Particle.h"
// This #include statement was automatically added by the Particle IDE.
#include <SparkJson.h>
#include "Firebase.h"

Firebase::Firebase() {
}

Firebase::Firebase(char *readHook) {
    this->_readHook = readHook;
    Serial.printlnf("Firebase instance created for %s (read)", readHook);
}

void Firebase::getDataHandler(const char *topic, const char *data) {
    Serial.printlnf("getDataHandler invoked");
	// TODO: more efficiant object handling
	StaticJsonBuffer<256> jsonBuffer;
	char *mutableCopy = strdup(data);
	JsonObject& root = jsonBuffer.parseObject(mutableCopy);
	free(mutableCopy);

	Serial.printlnf("data received: %s", data);
    _readCallback(root);
}

void Firebase::subscribe() {
    Serial.printlnf("Firebase subscribe");
    //Particle.subscribe("hook-response/test3rdata", getDataHandler, MY_DEVICES);

    Particle.subscribe(strncat("hook-response/", this->_readHook, 99), std::bind(&Firebase::getDataHandler, this, std::placeholders::_1, std::placeholders::_2), MY_DEVICES);
}

void Firebase::setCallback(void (*readCallback)(JsonObject& root)) {
    Serial.printlnf("set callback");
	_readCallback = readCallback;
}

void Firebase::publishData(char *eventName, char *JSON) {
	Serial.printlnf("publishing %s", JSON);
	Particle.publish(eventName, JSON, PRIVATE);
}

void Firebase::readData() {
	Particle.publish(this->_readHook, "", PRIVATE);
}
