#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Spectrum : public Visualization {
  private :
    uint16_t rowOffset;
    uint16_t length;
    bool invert;
    uint8_t travel;
    float threshold;

  public :
    Spectrum(uint16_t columns,
      uint16_t rows,
      uint16_t rowOffset,
      uint16_t length,
      uint8_t hue,
      uint8_t saturation,
      bool invert,
      uint8_t travel,
      CRGB * leds);
    void display(float * intensity);
    void setTravel(uint8_t travel);
    float getThreshold();
    void setThreshold(float threshold);
};
