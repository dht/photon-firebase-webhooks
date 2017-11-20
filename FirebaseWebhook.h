#ifndef Firebase_h

#define Firebase_h

#include <SparkJson.h>

class Firebase {

    public:
        Firebase();
        Firebase(char *readHook);

        void
            subscribe(),
            setCallback(void (*readCallback)(JsonObject& root)),
            readData(),
            publishData(char *eventName, char *JSON);


    private:
            void
                getDataHandler(const char *topic, const char *data),
                (*_readCallback)(JsonObject& root);

            StaticJsonBuffer<256> jsonBuffer;

            char
                *_readHook;
};

#endif