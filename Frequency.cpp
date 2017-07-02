#include "Frequency.h"

Frequency::Frequency (int columns, int rows, CRGB * leds, CRGB color)
: Visualization(columns, rows, leds)
{
  this->interval = 1000;
  this->color = color;
  this->color.maximizeBrightness();
  this->nextTime = 0;
}

void Frequency::display(unsigned long currentTime, int * levels) {
  int currentFrame = this->frame % 100;
  // Serial.println(currentTime, this->nextTime);

  if (currentTime > this->nextTime) {
    for(int i=0;i<7;i++)
    {
      Serial.print(levels[i]);
      if(i<6)  Serial.print(",");
      else Serial.println();
      levels[i] = 0;
    }

    this->frame++;
    this->nextTime = currentTime + this->interval;
  }

}
