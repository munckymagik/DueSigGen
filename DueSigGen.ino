#include <Arduino.h>
#include "Waveforms.h"

// 8333 uS per sample at 1Hz
const auto MCS_PER_SAMPLE_AT_1_HZ = 1000000 / NUM_SAMPLES;  // sample for the 1Hz signal expressed in microseconds
const auto WAVE_FORM = WaveForm::Sin;
// 1 Hz is the minimum freq
const int32_t START_FREQ_HZ = 200;
int32_t frequency = START_FREQ_HZ;

// With my Due the cost of 1 iteration of the loop is about 6 uS
const int32_t COST_OF_LOOP_MCS = 6;

int sample_index = 0;
uint32_t last_time = 0;

inline auto frequency_to_period(int freq) -> int {
  return MCS_PER_SAMPLE_AT_1_HZ / freq;
}

void setup() {
  analogWriteResolution(12);  // set the analog output resolution to 12 bit (4096 levels)
  Serial.begin(9600);
}

void loop() {
  analogWrite(DAC0, get_sample(WAVE_FORM, sample_index));  // write the selected waveform on DAC0

  sample_index++;
  if (sample_index == NUM_SAMPLES) sample_index = 0; // Reset the counter to repeat the wave

  if (Serial.available()) {
    frequency = Serial.parseInt();
  }

  auto period = frequency_to_period(frequency);
  auto delay_mcs = period - COST_OF_LOOP_MCS;

  if (delay_mcs > 0) delayMicroseconds(delay_mcs);  // Hold the sample value for the sample time
}
