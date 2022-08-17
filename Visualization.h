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
    uint8_t value;
    CRGB * leds;

    CRGB color;
    uint16_t frame;
    uint32_t nextTime;
    uint16_t interval;

    uint8_t drift;
    uint32_t driftms;
    uint32_t driftOffset = 0;
    uint32_t lastDriftOffset = 0;
    uint32_t lastDriftUpdate = 0;

    uint32_t lastLog = 0;

  public :
    Visualization(uint16_t columns,
      uint16_t rows,
      uint8_t hue,
      uint8_t saturation,
      CRGB * leds,
      uint8_t drift = 64);
    void display(unsigned long currentTime);
    void setLEDColorXY(uint16_t x, uint16_t y);
    void setLEDColor(uint16_t pos);
    uint16_t xy2Pos(uint16_t x, uint16_t y);
    void setHue(uint8_t hue);
    void setValue(uint8_t value);
    uint8_t getValue();
    uint8_t getHue();
    void setSaturation(uint8_t saturation);
    void setInterval(uint16_t interval);
    void setAllHue(uint8_t hue);
    void setAll();
    void clearAll();
    void setAllCRGB(CRGB c);
    void setDrift(uint8_t drift);
    void setDriftOffset(uint32_t currentTime, uint32_t driftOffset);
    void driftLoop(uint32_t driftSync);
};

#endif /* VISUALIZATION_H */
