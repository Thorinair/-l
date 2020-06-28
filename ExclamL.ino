#include <Adafruit_NeoPixel.h>
#include <ESP8266HTTPClient.h>

#include "ESP8266WiFi.h"

#include "Shared.h"
#include "TwiFi.h"

#include "ConfigurationLED.h"
#include "ConfigurationLuna.h"
#include "ConfigurationWiFi.h"


#define PIN_PIXEL  13
#define PIN_BUTTON 12

#define RESULT_SUCCESS   0
#define RESULT_ERROR     1
#define RESULT_NO_LYRICS 2

#define URL_RESULT_DONE 0
#define URL_RESULT_FAIL 1


/* LEDs */
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN_PIXEL, NEO_GRB + NEO_KHZ800);

struct LEDMain {
	RGB led {ledIdle.r, ledIdle.g, ledIdle.b};
} ledMain;

/* Misc. Values */
bool buttonPressed = false;
int holdCounter = 0;

void setupPins();
void setupLED();

void processButtons();
void processTicks();

void ledFlicker();
void ledSet();
int openL();
int openURL(String url);


void setupPins() {
    pinMode(PIN_BUTTON, INPUT_PULLUP);
}

void setupLED() {
    strip.begin();
    ledSet();
}   

void processButtons() {
    if (digitalRead(PIN_BUTTON) == LOW && !buttonPressed) {
        buttonPressed = true;
        holdCounter = 0;

        ledMain.led.r = ledPressed.r;
        ledMain.led.g = ledPressed.g;
        ledMain.led.b = ledPressed.b;
        ledSet();

        int result = openL();
        switch (result) {
            case RESULT_SUCCESS:
                ledMain.led.r = ledNotifSuccess.r;
                ledMain.led.g = ledNotifSuccess.g;
                ledMain.led.b = ledNotifSuccess.b;
                ledSet();
                break;
            case RESULT_ERROR:
                ledFlicker();
                break;
            case RESULT_NO_LYRICS:
                ledMain.led.r = ledNotifNoLyrics.r;
                ledMain.led.g = ledNotifNoLyrics.g;
                ledMain.led.b = ledNotifNoLyrics.b;
                ledSet();
                break;
        }
    }
    else if (digitalRead(PIN_BUTTON) == HIGH && buttonPressed) {
        buttonPressed = false;
    }
}

void processTicks() {
    if (holdCounter >= LED_NOTIF_HOLD / LED_ANIMATION_INTERVAL) {
        float div = LED_NOTIF_FADE / LED_ANIMATION_INTERVAL;
        float rOffs = (ledIdle.r - ledMain.led.r) / div;
        float gOffs = (ledIdle.g - ledMain.led.g) / div;
        float bOffs = (ledIdle.b - ledMain.led.b) / div;

        ledMain.led.r += rOffs;
        ledMain.led.g += gOffs;
        ledMain.led.b += bOffs;
    }
    else {
        holdCounter++;
    }

    ledSet();
}

void ledFlicker() {
    for (int i = 0; i < LED_ERROR_FLICKER_CNT; i++) {
        ledMain.led.r = 0;
        ledMain.led.g = 0;
        ledMain.led.b = 0;
        ledSet();
        delay(LED_ERROR_FLICKER_INT);
        ledMain.led.r = ledNotifError.r;
        ledMain.led.g = ledNotifError.g;
        ledMain.led.b = ledNotifError.b;
        ledSet();
        delay(LED_ERROR_FLICKER_INT);
    }
}

void ledSet() {
    strip.setPixelColor(0, strip.Color(ledMain.led.r, ledMain.led.g, ledMain.led.b));
    strip.show();
}

int openL() {
    HTTPClient http;

    http.begin(LUNA_IP, LUNA_PORT, String(LUNA_URL_L) + "&key=" + String(LUNA_KEY));

    int httpCode = http.GET();
    if (httpCode != 200)
        return RESULT_ERROR;

    String body = http.getString();
    http.end();

    if (body == "success")
        return RESULT_SUCCESS;
    else if (body == "no_lyrics")
        return RESULT_NO_LYRICS;
    else
        return RESULT_ERROR;
}

int openURL(String url) {
    if (LUNA_DEBUG)
        Serial.println("Opening URL: " + String(LUNA_IP) + url);
        
    WiFiClient client;
    if (!client.connect(LUNA_IP, LUNA_PORT)) {  
        if (LUNA_DEBUG)
            Serial.println("Error connecting!");
        return URL_RESULT_FAIL;
    }

    client.print("GET " + url + " HTTP/1.1\r\n" +
                 "Host: " + LUNA_IP + "\r\n" + 
                 "Connection: close\r\n\r\n");
    client.stop();
    
    if (LUNA_DEBUG)
        Serial.println("Connection success.");

    return URL_RESULT_DONE;
}

void setup() {
    Serial.begin(115200);

    setupPins();
    setupLED();
	connectWiFi(true);

	if (!LED_COLOR_DEBUG) {
        ledSet();
		openURL(String(LUNA_URL_BOOT) + "&key=" + String(LUNA_KEY) + "&device=" + String(WIFI_HOST));
	}
}

void loop() {	
	if (!LED_COLOR_DEBUG) {
        processButtons();
		processTicks();

		if (WiFi.status() != WL_CONNECTED) {
			connectWiFi(true);
	    }
	}
	else {
		strip.setPixelColor(0, strip.Color(ledDebug.r, ledDebug.g, ledDebug.b)); 
		strip.show();
	} 

	delay(LED_ANIMATION_INTERVAL);
}

