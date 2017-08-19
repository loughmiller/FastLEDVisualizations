#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Spectrum : public Visualization {
  private :
    uint16_t rowOffset;
    bool invert;
    uint8_t hue;
    uint8_t travel;

  public :
    Spectrum(uint16_t columns,
      uint16_t rows,
      uint16_t rowOffset,       // row to start on
      bool invert,              // false = rowOffset++, true = rowOffset--
      CRGB * leds,
      uint8_t hue,
      uint8_t travel);
    void display(float * intensity);
};
