void setupNeo() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  // END of Trinket-specific code.
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

}

void lightupNumRGB(int number, int r, int g, int b) {
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.setPixelColor(number, pixels.Color(r, g, b));
  pixels.show();   // Send the updated pixel colors to the hardware.
}

void turnOffAllLEDs(){
  pixels.clear(); 
}