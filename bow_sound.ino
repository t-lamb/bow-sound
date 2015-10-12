/*
Program for sound-responsive bow-tie by Teresa Lamb (http://teresaflourlamb.com/ )
This project uses Arduino Gemma v2, Electret Microphone Op Amp, and one Flora RGB Smart Neopixel.
First install Neopixel Library ( https://github.com/adafruit/Adafruit_NeoPixel )
More info about Gemma ( https://learn.adafruit.com/introducing-gemma )
*/

// Includes code (library) for Neopixel
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

// This tells the Gemma that your mic attached to A1 and your Neopixel is attached to D1.
const int micPin = A1;
const int ledPin = 1;

// Special code for Neopixel
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, ledPin, NEO_GRB + NEO_KHZ800);

int sampleWindow = 50;
int delayval = 50;

void setup() {
  // Neopixel code specifically for Gemma
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);

  // Microphone is input
  pinMode(micPin, INPUT);

  // Starts interaction with Neopixels
  pixels.begin();
}

void loop() {

  // This code averages readings from mic, so they will be more accurate
  unsigned long startMillis = millis();
  int amplitude;
  int prevMicReading = analogRead(micPin);
  int maxReading = 0;
  int minReading = 1024;

  int sampleCount = 0;
  unsigned long totalDiff = 0;

  while (millis() - startMillis < sampleWindow) {
    int newReading = analogRead(micPin);

    // find absolute difference
    int difference = abs(prevMicReading - newReading);

    //add difference to total difference
    totalDiff += difference;

    // save reading for next loop
    prevMicReading = newReading;

    sampleCount++;
  }

  float averageVolume = totalDiff / sampleCount;


  // Based on averages, set color of Neopixel
  if (averageVolume > 34) {
    pixels.setPixelColor(0, pixels.Color(200, 0, 0)); //red
    pixels.show(); // updates pixel color
    delay(delayval); // wait before changing color again
  } else if (averageVolume > 28) {
    pixels.setPixelColor(0, pixels.Color(200, 75, 0)); //orange
    pixels.show();
    delay(delayval);
  } else if (averageVolume > 22) {
    pixels.setPixelColor(0, pixels.Color(150, 150, 0)); //yellow
    pixels.show();
    delay(delayval);
  } else if (averageVolume > 16) {
    pixels.setPixelColor(0, pixels.Color(50, 150, 0)); //green
    pixels.show();
    delay(delayval);
  } else if (averageVolume > 10) {
    pixels.setPixelColor(0, pixels.Color(0, 75, 150)); //blue
    pixels.show();
    delay(delayval);
  } else if (averageVolume > 4) {
    pixels.setPixelColor(0, pixels.Color(20, 0, 100)); //purple
    pixels.show();
    delay(delayval);
  } else {
    pixels.setPixelColor(0, pixels.Color(0, 0, 0)); //off
    pixels.show();
    delay(delayval);
  }
}
