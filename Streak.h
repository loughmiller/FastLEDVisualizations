#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Streak : public Visualization {
  private :
    int column;
    int length;
    int minLength;
    int maxLength;
    int minInterval;
    int maxInterval;
    CRGB color;

  public :
    Streak (int columns, int rows, CRGB * leds, CRGB color);

    void inititalize();

    void display (unsigned long currentTime);

    void setColor (CRGB color);

    void setLengthMinMax(int min, int max);

    void setIntervalMinMax(int min, int max);
};
