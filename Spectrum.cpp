#include "Spectrum.h"

Spectrum::Spectrum(uint16_t columns,
  uint16_t rows,
  uint16_t rowOffset,
  uint16_t length,
  uint8_t hue,
  uint8_t saturation,
  bool invert,
  uint8_t travel,
  CRGB * leds)
: Visualization(columns, rows, hue, saturation, leds) {
  this->rowOffset = rowOffset;
  this->invert = invert;
  this->travel = travel;
  this->length = length;
  this->threshold = 0.8;
}

void Spectrum::display(float* intensities) {
  for (uint8_t y=0; y<this->rows - this->length; y++) {
    float intensity = intensities[y + 8];  // THIS IS WHERE WE OFFSET LOWER FREQUENCIES
    if (intensity < this->threshold) {
      continue;
    }

    intensity = (intensity - (this->threshold)) / (1 - this->threshold);
    uint8_t hue = (this->travel * intensity) + this->hue;

    CRGB c = CHSV(hue, this->saturation, 255);
    for (uint8_t x=0; x<this->columns; x++) {
      if (this->invert) {
        leds[this->xy2Pos(x, this->rowOffset - y)] = c;
      } else {
        leds[this->xy2Pos(x, y + this->rowOffset)] = c;
      }
    }
  }
}

void Spectrum::setTravel(uint8_t travel) {
  this->travel = travel;
}

float Spectrum::getThreshold() {
  return this->threshold;
}

void Spectrum::setThreshold(float threshold) {
  this->threshold = threshold;
}
