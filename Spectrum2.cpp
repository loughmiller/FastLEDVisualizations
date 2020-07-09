#include "Spectrum2.h"

Spectrum2::Spectrum2(uint16_t columns,
  uint16_t rows,
  uint16_t rowOffset,
  uint16_t length,
  uint8_t hue,
  uint8_t saturation,
  bool invert,
  CRGB * leds)
: Visualization(columns, rows, hue, saturation, leds) {
  this->rowOffset = rowOffset;
  this->invert = invert;
  this->length = length;
  this->density = 0.15;
  this->threshold = 1000.0;
  this->peak = 2000.0;
  this->drift = 0;
  this->totalMagnitudeMovingAverage = 20000.0;
}

void Spectrum2::display(float* magnitudes) {

  float sorted[this->length];
  memcpy(sorted, magnitudes, sizeof(magnitudes[0]) * this->length);
  std::sort(sorted, sorted+sizeof(sorted)/sizeof(sorted[0]));

  float cutoffMagnitude = sorted[(uint_fast16_t)((1 - this->density)*this->length)];
  float peakMagnitude = sorted[this->length - 2];
  this->threshold = (this->threshold * (0.9998)) + (cutoffMagnitude/5000.0);
  this->peak = (this->peak * (0.9998)) + (peakMagnitude/5000.0);

  float magnitude;
  float magnitudeSum = 0;

  for (uint8_t y=0; y<this->length; y++) {
    magnitudeSum += magnitudes[y];

    if (magnitudes[y] < this->threshold) {
      continue;
    }

    magnitude = ((magnitudes[y] - threshold) / (peak - threshold));
    magnitude = min(magnitude, 1);

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

  if (this->drift > 0 && magnitudeSum > this->totalMagnitudeMovingAverage * 1.75) {
    this->hue = 240;
  }

  this->totalMagnitudeMovingAverage = (this->totalMagnitudeMovingAverage * (0.9998)) + (magnitudeSum/5000.0);

}

void Spectrum2::setDrift(uint8_t drift) {
  this->drift = drift;
}

float Spectrum2::getDensity() {
  return this->density;
}

void Spectrum2::setDensity(float density) {
  this->density = density;
}
