#include "Spectrum2.h"

Spectrum2::Spectrum2(uint16_t columns,
  uint16_t rows,
  uint16_t rowOffset,
  uint16_t length,
  uint8_t hue,
  uint8_t saturation,
  bool invert,
  bool fill,
  CRGB * leds)
: Visualization(columns, rows, hue, saturation, leds) {
  this->rowOffset = rowOffset;
  this->invert = invert;
  this->length = length;
  this->density = 0.08;
  this->threshold = 1000.0;
  this->peak = 2000.0;
  this->drift = 0;
  this->totalMagnitudeMovingAverage = 10000.0;
  this->fill = fill;
  this->lowPassPeakMovingAverage = 20000.0;
  this->lowPassTroughMovingAverage = 5000.0;
  this->lowPassMovingAverage = 10000.0;
}

void Spectrum2::display(float* magnitudes) {
  uint_fast32_t currentTime = millis();

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
  float lowPassMagnitudeSum = 0;

  for (uint8_t y=0; y<this->length; y++) {
    if (y < this->lowPassCount) {
      lowPassMagnitudeSum += magnitudes[y];
    }
    magnitudeSum += magnitudes[y];
  }

  this->totalMagnitudeMovingAverage = (this->totalMagnitudeMovingAverage * 0.98) + magnitudeSum * 0.02;
  this->lowPassMovingAverage = (this->lowPassMovingAverage * 0.98) + (lowPassMagnitudeSum * (1 - 0.98));


  if (fill) {

    float ratio = 0;
    uint_fast8_t height = 0;

    for (uint8_t column=0; column<this->columns; column++) {
      magnitude = magnitudes[column];
      ratio = magnitude / this->peak;
      height = min(this->length, this->length * ratio);
      uint_fast8_t intensity = min(ratio * 200, 200);

      for (uint8_t row=0; row<height; row++) {
        if (this->invert) {
          this->leds[this->xy2Pos(column, this->rowOffset + (this->length - row))] = CHSV(this->hue, this->saturation, intensity);
        } else {
          this->leds[this->xy2Pos(column, this->rowOffset + row)] = CHSV(this->hue, this->saturation, intensity);
        }
      }
    }

    // put things we want to log here
    // if (currentTime > this->loggingTimestamp + 500) {
    //   this->loggingTimestamp = currentTime;

    //   // for (uint8_t column=0; column<15; column++) {
    //   //   Serial.print(magnitudes[column]);
    //   //   Serial.print("\t");
    //   // }
    //   // Serial.print(this->peak);
    //   // Serial.print("\t");
    //   // Serial.print(ratio);
    //   // Serial.print("\t");
    //   // Serial.print(height);
    //   // Serial.print("\t");
    //   // Serial.print(this->length);

    //   // Serial.println("");
    // }

  } else {
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
      if (this->invert) {
        this->displayRow(this->rowOffset - y, c);
        if (overPeak) {
          if (y > 0) {
            this->displayRow(this->rowOffset - (y - 1), c2);
          }
          if (y < this->length - 1) {
            this->displayRow(this->rowOffset - (y + 1), c2);
          }
        }
      } else {
        this->displayRow(this->rowOffset + y, c);
        if (overPeak) {
          if (y > 0) {
            this->displayRow(this->rowOffset + (y - 1), c2);
          }
          if (y < this->length - 1) {
            this->displayRow(this->rowOffset + (y + 1), c2);
          }
        }
      }
      if (overPeak) {
        y++;
      }
    }
  }

  if (this->drift > 0) {
    this->hue = (currentTime / this->drift) % 256;
  }

  // Change hue to pink on big volume increases
  // if (this->drift > 0 && magnitudeSum > this->totalMagnitudeMovingAverage * 1.75) {
  //   this->hue = 240;
  // }

  // put things we want to log here
  // if (currentTime > this->loggingTimestamp + 500) {
  //   this->loggingTimestamp = currentTime;

  //     Serial.print(currentTime);
  //     Serial.print("\t");
  //     Serial.print(this->drift);
  //     Serial.print("\t");
  //     Serial.print(this->hue);


  //   // Serial.print(peakCount);
  //   // Serial.print(cutoffMagnitude);
  //   // Serial.print("\t");
  //   // Serial.print(peakMagnitude);
  //   // Serial.print("\t");
  //   // Serial.print(this->threshold);
  //   // Serial.print("\t");
  //   // Serial.print(this->peak);
  //   // Serial.print("\t");
  //   // Serial.print(this->hue);
  //   // Serial.print("\t");
  //   // Serial.print(magnitudeSum);
  //   // Serial.print("\t");
  //   // Serial.print(this->totalMagnitudeMovingAverage);

  //   Serial.println("");
  // }
}

void Spectrum2::setDrift(uint_fast32_t drift) {
  this->drift = drift;
}

float Spectrum2::getDensity() {
  return this->density;
}

void Spectrum2::setDensity(float density) {
  this->density = density;
}

float Spectrum2::getMagnitude() {
  return this->totalMagnitudeMovingAverage;
}

void Spectrum2::displayRow(uint8_t y, CRGB color) {
   for (uint8_t x=0; x<this->columns; x++) {
    leds[this->xy2Pos(x, y)] = color;
   }
}
