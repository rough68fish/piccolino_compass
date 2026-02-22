#include <Wire.h>
#include <SPI.h>
#include <Piccolino_OLED_SRAM.h>
#include <Piccolino_RAM.h>

Piccolino_OLED_SRAM display;

// Full compass string — window scrolls left-to-right across this
// Starts showing "NW--N--NE", then scrolls toward "N--NE--E"
const char* compassFull = "W---NW---N---NE---E---SE---S---SW---W---NW---N";

#define DISPLAY_CHARS 9   // Characters visible at once (adjust for font size)
int scrollIndex = 4;       // Start at "NW---N---NE" region

void setup() {
  display.begin();
  display.clear();
  display.update();
}

void loop() {
  display.clear();

  // Build the visible window string
  char window[DISPLAY_CHARS + 1];
  for (int i = 0; i < DISPLAY_CHARS; i++) {
    window[i] = compassFull[scrollIndex + i];
  }
  window[DISPLAY_CHARS] = '\0';

  // Draw a simple horizon/tick line above the text
  display.drawLine(0, 18, 127, 18, WHITE);
  // Draw a center tick mark to act as the heading indicator
  display.drawLine(63, 14, 63, 22, WHITE);

  // Print compass string
  display.setCursor(0, 26);         // Below the yellow portion of display
  display.setTextColor(WHITE);
  display.setTextSize(2);           // Larger text for readability
  display.print(window);

  display.update();

  delay(400);  // Scroll speed — increase to slow down rotation

  // Advance the scroll window one character to the right
  scrollIndex++;

  // Loop back when we've scrolled through the full string
  if (scrollIndex > (int)(strlen(compassFull) - DISPLAY_CHARS)) {
    scrollIndex = 0;
  }
}
