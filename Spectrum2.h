#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"
#include <algorithm>    // std::sort

class Spectrum2 : public Visualization {
  private :
    uint16_t rowOffset;
    uint16_t length;
    bool invert;
    uint8_t travel;
    float threshold;
    float peak;
    int16_t drift;
    float totalMagnitudeMovingAverage;

  public :
    Spectrum2(uint16_t columns,
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
    void setDrift(uint8_t drift);
    float getThreshold();
    void setThreshold(float threshold);
};
