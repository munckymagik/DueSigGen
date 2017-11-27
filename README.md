# DueSigGen

A very simple signal generator for Arduino Due.

Based on [this](https://www.arduino.cc/en/Tutorial/DueSimpleWaveformGenerator), but modified to:

* Read changes in frequency over serial instead of needing input from a potentiometer
* Allow setting the desired frequency in Hz

Waveform is hardcoded to sine, but can be varied by changing the value of the `WAVE_FORM` constant
then re-uploading.
