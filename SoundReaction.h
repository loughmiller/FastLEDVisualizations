#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class SoundReaction : public Visualization {
  private :
    uint16_t start;
    uint16_t end;
    uint8_t onHue;
    uint8_t offHue;

  public :
    SoundReaction(uint16_t start,
      uint16_t stop,
      uint8_t onHue,
      uint8_t offHue,
      uint8_t saturation,
      CRGB * leds);
    void display(float intensity);
    void setOnHue(uint8_t hue);
    void setOffHue(uint8_t hue);
};
