#include "Spectrum.h"

Spectrum::Spectrum(uint16_t columns,
  uint16_t rows,
  uint16_t rowOffset,
  bool invert,
  CRGB * leds,
  uint8_t hue,
  uint8_t travel)
: Visualization(columns, rows, leds, CHSV(hue, 245, 255)) {
  this->rowOffset = rowOffset;
  this->invert = invert;
  this->hue = hue;
  this->travel = travel;
}

void Spectrum::display(float* intensities) {
  for (uint8_t y=0; y<this->rows - this->rowOffset; y++) {
    float intensity = intensities[y+2];
    if (intensity < 0.5) {
      continue;
    }

    intensity = (intensity - 0.5) * 2.0;
    uint8_t hue = (this->travel * intensity) + this->hue;

    CRGB c = CHSV(hue, 245, 255);
    for (uint8_t x=0; x<this->columns; x++) {
      if (this->invert) {
        leds[this->xy2Pos(x, this->rowOffset - y)] = c;
      } else {
        leds[this->xy2Pos(x, y + this->rowOffset)] = c;
      }
    }
  }
}
