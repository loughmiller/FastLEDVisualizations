#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Sparkle : public Visualization {
  private :
    uint32_t emptiness;

  public :
    Sparkle(uint16_t ledCount,
      uint8_t hue,
      uint8_t saturation,
      CRGB * leds,
      uint32_t emptiness);

    void display(uint32_t currentTime);
    void setEmptiness(uint32_t emptiness);
};
