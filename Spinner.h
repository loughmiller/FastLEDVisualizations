#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Spinner : public Visualization {
  private :
    uint8_t ledCount;
    uint8_t length;

  public :
    Spinner(uint16_t columns,
      uint16_t rows,
      uint8_t hue,
      uint8_t saturation,
      CRGB * leds);

    void inititalize();

    void display(unsigned long currentTime);
};
