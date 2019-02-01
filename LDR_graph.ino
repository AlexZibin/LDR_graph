#include <Adafruit_NeoPixel.h>


// Collecting data each TIME_STEP milliseconds:
#define TIME_STEP (1)
// How much measurements we will collect:
#define NUM_POINTS (250)

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
    //Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    strip.setBrightness(50);
    strip.show(); // Initialize all pixels to 'off'
    
}

void loop () {
    // Loop is empty
}
