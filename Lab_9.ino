
#include <Adafruit_NeoPixel.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S i2s1;                   //xy=217,166
AudioAnalyzePeak peak1;               //xy=454,93
AudioAnalyzeNoteFrequency notefreq1;  //xy=493,159
AudioOutputI2S i2s2;                  //xy=500,211
AudioConnection patchCord1(i2s1, 0, peak1, 0);
AudioConnection patchCord2(i2s1, 0, i2s2, 0);
AudioConnection patchCord3(i2s1, 0, i2s2, 1);
AudioConnection patchCord4(i2s1, 0, notefreq1, 0);
AudioControlSGTL5000 sgtl5000_1;  //xy=345,32
// GUItool: end automatically generated code



int numPixels = 8;
int pixelPin = 27;
unsigned long j = 0;

int noteFreq = 0;


Adafruit_NeoPixel neopixel = Adafruit_NeoPixel(numPixels, pixelPin, NEO_GRB);


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  neopixel.begin();
  neopixel.clear();
  neopixel.show();


  AudioMemory(50);
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.volume(0.5);

  notefreq1.begin(.15);  //this sets the threshold value of your frequency
}

void loop() {
  checkFreq();
  // put your main code here, to run repeatedly:

  if (peak1.available()) {
    int peak = peak1.read() * 8;



    for (int i = 0; i < peak; i++) {



      // j = (j+i);
      neopixel.setPixelColor(i, noteFreq, 100, 30);
      neopixel.show();

      //neopixel.setPixelColor(i,0,0,0);
    }
  }
  neopixel.clear();
}


void checkFreq() {

  if (notefreq1.available()) {
    float note = notefreq1.read();
    Serial.println(note);
    noteFreq = map(note, 200, 700, 0, 255);
  }
}
