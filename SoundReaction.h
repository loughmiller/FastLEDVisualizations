#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class SoundReaction : public Visualization {
  private :
    uint16_t start;
    uint16_t end;
    CRGB onColor;
    CRGB offColor;

  public :
    SoundReaction(uint16_t start, uint16_t end, CRGB * leds, CRGB onColor, CRGB offColor);
    void display(float intensity);
    void setOnColor (CRGB color);
    void setOffColor (CRGB color);
};
