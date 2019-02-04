#include "FS.h"
#include "SD.h"
#include "SPI.h"

#include <Adafruit_NeoPixel.h>
#define NUMPIXELS      (2)

// Collecting data each TIME_STEP milliseconds:
#define TIME_STEP (1)
// How much measurements we will collect during one half-period:
#define NUM_POINTS (250)
// How much half-periods:
#define HALF_PERIODS (4)

unsigned int data[NUM_POINTS*HALF_PERIODS];

//Pins
#define LDR_PIN (25)
#define LED_PIN (32)
#define BUZZER_PIN (26)
#define BROKEN_CIRCUIT_PIN (35)
#define RX2_PIN (32)
#define TX2_PIN (34)
#define RESET_A6_PIN (36)
//

Adafruit_NeoPixel strip = Adafruit_NeoPixel (NUMPIXELS, LED_PIN, NEO_RGB + NEO_KHZ800);

void setup () {
    Serial.begin (115200);
    if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }

    pinMode (LDR_PIN, INPUT);
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    strip.begin();
    //strip.setBrightness(50);
    strip.show(); // Initialize all pixels to 'off'
    delay (100);

    int i;
    for (int j = 0; j < HALF_PERIODS; j++) {
        if (j % 2) { // Blink
            for (i = 0; i < NUMPIXELS; i++) {
                strip.setPixelColor(i, strip.Color(0,0,0)); 
            }
            Serial.println ("LEDs off");
        }
        else {
            for (i = 0; i < NUMPIXELS; i++) {
                strip.setPixelColor(i, strip.Color(255,255,255)); 
            }
            Serial.println ("LEDs ON");
        }
        strip.show(); 
        
        //unsigned long _millis = millis ();
        for (int i = 0; i < NUM_POINTS; i++) {
            data [j*NUM_POINTS + i] = analogRead (LDR_PIN);
            delay (TIME_STEP);
        }
    }

    File file = SD.open ("/log001.txt", FILE_WRITE);
    //File file = SD.open(path, FILE_APPEND);
    //Serial.printf("%u bytes read for %u ms\n", flen, end);
    if (!file) {
        Serial.println ("Failed to open file for writing");
        return;
    }
    
    for (int j = 0; j < HALF_PERIODS; j++) {
        for (int i = 0; i < NUM_POINTS; i++) {
            if (!file.print (data [j*NUM_POINTS + i])) {
                Serial.println ("Write failed");
                return;
            }
            file.print (", ");
            if (i < 20) {
                Serial.println (data [j*NUM_POINTS + i]);
            }
        }
        Serial.println ();
    }
    file.close ();
    Serial.println ("Completed!");
}

void loop () {
    // Loop is empty
}
