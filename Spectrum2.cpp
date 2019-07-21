#include "Spectrum2.h"

Spectrum2::Spectrum2(uint16_t columns,
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
  this->threshold = 1000.0;
  this->peak = 3000.0;
  this->drift = 0;
}

void Spectrum2::display(float* magnitudes) {
  float sorted[this->length];
  memcpy(sorted, magnitudes, sizeof(magnitudes[0]) * this->length);
  std::sort(sorted, sorted+sizeof(sorted)/sizeof(sorted[0]));

  float twoThirds = sorted[(uint_fast16_t)(0.9*this->length)];
  float maxNote = sorted[this->length - 1];
  this->threshold = (this->threshold * (0.99)) + (twoThirds/100.0);
  this->peak = (this->peak * (0.99)) + (maxNote/100.0);

  float magnitude;
  for (uint8_t y=0; y<this->length; y++) {
    if (magnitudes[y] < this->threshold) {
      continue;
    }

    magnitude = ((magnitudes[y] - threshold) / (peak - threshold));

    CRGB c = CHSV(this->hue, this->saturation, magnitude*255);
    for (uint8_t x=0; x<this->columns; x++) {
      if (this->invert) {
        leds[this->xy2Pos(x, this->rowOffset - y)] = c;
      } else {
        leds[this->xy2Pos(x, y + this->rowOffset)] = c;
      }
    }
  }

  this->hue += this->drift;
}

void Spectrum2::setTravel(uint8_t travel) {
  this->travel = travel;
}

void Spectrum2::setDrift(uint8_t drift) {
  this->drift = drift;
}

float Spectrum2::getThreshold() {
  return this->threshold;
}

void Spectrum2::setThreshold(float threshold) {
  this->threshold = threshold;
}
