#include <Adafruit_NeoPixel.h>
#define NUMPIXELS      (2)

// Collecting data each TIME_STEP milliseconds:
#define TIME_STEP (5)
// How much measurements we will collect during one half-period:
#define NUM_POINTS (250)
// How much half-periods:
#define HALF_PERIODS (4)

unsigned int data[NUM_POINTS*HALF_PERIODS];

//Pins
#define LDR_PIN (25)
#define LED_PIN (27)
#define BUZZER_PIN (26)
#define BROKEN_CIRCUIT_PIN (35)
#define RX2_PIN (32)
#define TX2_PIN (34)
#define RESET_A6_PIN (36)
//

void setup () {
    //Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    //strip.setBrightness(50);
    strip.show(); // Initialize all pixels to 'off'
    delay (100);
    
    for (int j = 0; j < HALF_PERIODS; j++) {
        if (j % 2) // Blink
            strip.setPixelColor(i, strip.Color(255,255,255)); 
        else
            strip.setPixelColor(i, strip.Color(0,0,0)); 
        strip.show(); 
        
        unsigned long _millis = millis ();
        for (int i = 0; i < NUMPIXELS;i++) {
            if (millis () - _millis >= TIME_STEP) { // And write resistance in array
                _millis = millis ();
                data [j*NUM_POINTS + i]= analogRead (LDR_PIN);
            }
        }
    }
    sd.mount ();
    file.open();
    for (int j = 0; j < HALF_PERIODS; j++) 
       for (int i = 0; i < NUMPIXELS; i++) {
            file.write (data [j*NUM_POINTS + i]);
            file.write (", ");
       }
    file.close();
}

void loop () {
    // Loop is empty
}
