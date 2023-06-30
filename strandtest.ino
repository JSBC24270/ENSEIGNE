#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define LED_PIN    6
#define LED_COUNT 48
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C lcd(0x27,20,4);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  lcd.begin(20,4);
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  lcd.setCursor(1,0);
  lcd.print("ENSEIGNE STRANDTEST");
  lcd.setCursor(2,1);  
  lcd.print("By: JSB.CREATION");
  lcd.setCursor(8,2);
  lcd.print("POUR");
  lcd.setCursor(1,3);
  lcd.print("L'BARAQUE A FREDDO");
  delay(3000);
  lcd.clear();



  
}

void loop() {
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("L'BARAQUE A FREDDO");
  lcd.setCursor(5,2);
  lcd.print("COLOR WIPE");  
  colorWipe(strip.Color(255,   0,   0), 30); // Red
  colorWipe(strip.Color(  0, 255,   0), 30); // Green
  colorWipe(strip.Color(  0,   0, 255), 30); // Blue  
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("L'BARAQUE A FREDDO");
  lcd.setCursor(3,2);
  lcd.print("THEATER CHASE");    
  theaterChase(strip.Color(255, 255, 255), 30); // White, half brightness
  theaterChase(strip.Color(255,   0,   0), 30); // Red, half brightness
  theaterChase(strip.Color(  0, 255,   0), 30); // Green, half brightness    
  theaterChase(strip.Color(  0,   0, 255), 30); // Blue, half brightness

  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("L'BARAQUE A FREDDO");  
  lcd.setCursor(6,2);
  lcd.print("RAINBOW");  
  rainbow(3);             // Flowing rainbow cycle along the whole strip
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("L'BARAQUE A FREDDO");  
  lcd.setCursor(3,2);
  lcd.print("CHASE RAINBOW");   
  theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
}

void colorWipe(uint32_t color, int wait) 
{
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
void theaterChase(uint32_t color, int wait) 
{
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

void rainbow(int wait) 
{   
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    strip.rainbow(firstPixelHue);
    strip.show(); // Update strip with new contents
 //   delay(wait);  // Pause for a moment
  }
}

void theaterChaseRainbow(int wait) 
{  
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<20; a++) 
  {  // Repeat 30 times...
    for(int b=0; b<3; b++) 
    { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      for(int c=b; c<strip.numPixels(); c += 3) {
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
