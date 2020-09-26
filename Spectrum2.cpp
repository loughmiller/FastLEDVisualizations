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
  this->density = 0.06;
  this->threshold = 1000.0;
  this->peak = 2000.0;
  this->drift = 0;
  this->totalMagnitudeMovingAverage = 20000.0;
}

void Spectrum2::display(float* magnitudes) {
  uint_fast16_t peakCount = 0;
  bool overPeak = false;

  float sorted[this->length];
  memcpy(sorted, magnitudes, sizeof(magnitudes[0]) * this->length);
  std::sort(sorted, sorted+sizeof(sorted)/sizeof(sorted[0]));

  const float alpha = 0.9;

  float cutoffMagnitude = sorted[(uint_fast16_t)((1 - this->density)*this->length)];
  float peakMagnitude = sorted[this->length - 2];
  this->threshold = (this->threshold * alpha) + (cutoffMagnitude* (1 - alpha));
  this->peak = (this->peak * alpha) + (peakMagnitude * (1 - alpha));

  float magnitude;
  float magnitudeSum = 0;

  for (uint8_t y=0; y<this->length; y++) {
    overPeak = false;
    magnitudeSum += magnitudes[y];

    if (magnitudes[y] < this->threshold) {
      continue;
    }

    if (magnitudes[y] > this->peak * 1.2) {
      peakCount++;
      overPeak = true;
    }

    magnitude = ((magnitudes[y] - this->threshold) / (this->peak - this->threshold));
    magnitude = min(magnitude, 1);
    magnitude = max(magnitude, 0.15);

    CRGB c = CHSV(this->hue, this->saturation, magnitude*255);
    CRGB c2 = CHSV(this->hue, this->saturation, magnitude*128);
    for (uint8_t x=0; x<this->columns; x++) {
      if (this->invert) {
        leds[this->xy2Pos(x, this->rowOffset - y)] = c;
        if (overPeak) {
          if (y > 0) {
            leds[this->xy2Pos(x, (this->rowOffset - (y - 1)))] = c2;
          }
          if (y < this->length - 1) {
            leds[this->xy2Pos(x, (this->rowOffset - (y + 1)))] = c2;
          }
        }
      } else {
        leds[this->xy2Pos(x, y + this->rowOffset)] = c;
        if (overPeak) {
          if (y > 0) {
            leds[this->xy2Pos(x, (y + this->rowOffset) - 1)] = c2;
          }
          if (y < this->length - 1) {
            leds[this->xy2Pos(x, y + this->rowOffset + 1)] = c2;
          }
        }
      }
    }
    if (overPeak) {
      y++;
    }
  }

  uint_fast32_t currentTime = millis();

  this->hue = (currentTime / this->drift) % 256;

  // Change hue to pink on big volume increases
  if (this->drift > 0 && magnitudeSum > this->totalMagnitudeMovingAverage * 1.75) {
    this->hue = 240;
  }

  this->totalMagnitudeMovingAverage = (this->totalMagnitudeMovingAverage * (0.9998)) + (magnitudeSum/5000.0);


  // put things we want to log here
  if (currentTime > this->loggingTimestamp + 5000) {
    this->loggingTimestamp = currentTime;

    // Serial.print(peakCount);
    // Serial.print(cutoffMagnitude);
    // Serial.print("\t");
    // Serial.print(peakMagnitude);
    // Serial.print("\t");
    // Serial.print(this->threshold);
    // Serial.print("\t");
    // Serial.print(this->peak);
    // Serial.print("\t");
    // Serial.print(this->hue);
    // Serial.print("\t");
    // Serial.print(magnitudeSum);
    // Serial.print("\t");
    // Serial.print(this->totalMagnitudeMovingAverage);
    // Serial.println("");
  }
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
