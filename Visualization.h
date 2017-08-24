  #ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <Arduino.h>
#include "FastLED.h"

class Visualization {
  protected :
    uint16_t columns;
    uint16_t rows;
    uint8_t hue;
    uint8_t saturation;
    CRGB * leds;

    CRGB color;
    uint16_t frame;
    uint32_t nextTime;
    uint16_t interval;

  public :
    Visualization(uint16_t columns,
      uint16_t rows,
      uint8_t hue,
      uint8_t saturation,
      CRGB * leds);
    void display(unsigned long currentTime);
    void setLEDColorXY(uint16_t x, uint16_t y);
    void setLEDColor(uint16_t pos);
    uint16_t xy2Pos(uint16_t x, uint16_t y);
    void setHue(uint8_t hue);
    uint8_t getHue();
    void setSaturation(uint8_t saturation);
    void setInterval(uint16_t interval);
    void setAllHue(uint8_t hue);
    void setAllCRGB(CRGB c);
};

#endif /* VISUALIZATION_H */
