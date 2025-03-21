/*
  Example for TFT_eSPI library

  Created by Bodmer 11/03/17

  Make sure LOAD_GFXFF is defined in the used User_Setup file
  within the library folder.

  --------------------------- NOTE ----------------------------------------
  The free font encoding format does not lend itself easily to plotting
  the background without flicker. For values that changes on screen it is
  better to use Fonts 1- 8 which are encoded specifically for rapid
  drawing with background.
  -------------------------------------------------------------------------

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  ######   TO SELECT YOUR DISPLAY TYPE, PINS USED AND ENABLE FONTS   ######
  #########################################################################
*/

// Note the the tilda symbol ~ does not exist in some fonts at the moment
#define TEXT "abc MWy 123 |" // Text that will be printed on screen in any font


#include <LilyGoLib.h>

// Stock font and GFXFF reference handle
#define GFXFF 1
#define FF18 &FreeSans12pt7b

// Custom are fonts added to library "TFT_eSPI\Fonts\Custom" folder
// a #include must also be added to the "User_Custom_Fonts.h" file
// in the "TFT_eSPI\User_Setups" folder. See example entries.
#define CF_OL24 &Orbitron_Light_24
#define CF_OL32 &Orbitron_Light_32
#define CF_RT24 &Roboto_Thin_24
#define CF_S24  &Satisfy_24
#define CF_Y32  &Yellowtail_32


// Use hardware SPI


void setup(void)
{

    Serial.begin(250000);

    watch.begin();

    watch.setRotation(1);

}

void loop()
{

    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    // Show custom fonts
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    // Where font sizes increase the screen is not cleared as the larger fonts overwrite
    // the smaller one with the background colour.

    // We can set the text datum to be Top, Middle, Bottom vertically and Left, Centre
    // and Right horizontally. These are the text datums that can be used:
    // TL_DATUM = Top left (default)
    // TC_DATUM = Top centre
    // TR_DATUM = Top right
    // ML_DATUM = Middle left
    // MC_DATUM = Middle centre <<< This is used below
    // MR_DATUM = Middle right
    // BL_DATUM = Bottom left
    // BC_DATUM = Bottom centre
    // BR_DATUM = Bottom right
    // L_BASELINE = Left character baseline (Line the 'A' character would sit on)
    // C_BASELINE = Centre character baseline
    // R_BASELINE = Right character baseline

    //Serial.println();

    // Set text datum to middle centre (MC_DATUM)
    watch.setTextDatum(MC_DATUM);

    // Set text colour to white with black background
    // Unlike the stock Adafruit_GFX library, the TFT_eSPI library DOES draw the background
    // for the custom and Free Fonts
    watch.setTextColor(TFT_WHITE, TFT_BLACK);

    watch.fillScreen(TFT_MAGENTA);            // Clear screen
    watch.setFreeFont(FF18);                 // Select the font
    watch.drawString("Yellowtail 32", 160, 60, GFXFF);// Print the string name of the font
    watch.setFreeFont(CF_Y32);                 // Select the font
    watch.drawString(TEXT, 160, 120, GFXFF);// Print the string name of the font
    delay(2000);

    watch.fillScreen(TFT_BLUE);            // Clear screen
    watch.setFreeFont(FF18);                 // Select the font
    watch.drawString("Satisfy 24", 160, 60, GFXFF);// Print the string name of the font
    watch.setFreeFont(CF_S24);                 // Select the font
    watch.drawString(TEXT, 160, 120, GFXFF);// Print the test text in the custom font
    delay(2000);

    watch.fillScreen(TFT_RED);            // Clear screen
    watch.setFreeFont(FF18);                 // Select the font
    watch.drawString("Roboto 24", 160, 60, GFXFF);// Print the string name of the font
    watch.setFreeFont(CF_RT24);                 // Select the font
    watch.drawString(TEXT, 160, 120, GFXFF);// Print the test text in the custom font
    delay(2000);

    watch.fillScreen(TFT_DARKGREY);            // Clear screen
    watch.setFreeFont(FF18);                 // Select the font
    watch.drawString("Orbitron 24", 160, 60, GFXFF);// Print the string name of the font
    watch.setFreeFont(CF_OL24);                 // Select the font
    watch.drawString(TEXT, 160, 120, GFXFF);// Print the test text in the custom font
    delay(2000);

    // Here we do not clear the screen and rely on the new text over-writing the old
    watch.setFreeFont(FF18);                 // Select the font
    watch.drawString("Orbitron 32", 160, 60, GFXFF);// Print the string name of the font
    watch.setFreeFont(CF_OL32);                 // Select the font
    watch.drawString(TEXT, 160, 120, GFXFF);// Print the test text in the custom font
    delay(2000);

    // Here we use text background padding to over-write the old text
    watch.fillScreen(TFT_YELLOW);            // Clear screen
    watch.setTextColor(TFT_WHITE, TFT_BLACK);

    // Here we use text background padding to over-write the old text
    watch.setTextPadding(watch.width() - 20); // Blanked area will be width of screen minus 20 pixels
    watch.setFreeFont(FF18);                 // Select the font
    watch.drawString("Orbitron 32 with padding", 160, 60, GFXFF);// Print the string name of the font
    watch.setFreeFont(CF_OL32);                 // Select the font
    watch.drawString(TEXT, 160, 120, GFXFF);// Print the test text in the custom font
    delay(2000);

    // Use 80 pixel wide padding so old numbers over-write old ones
    // One of the problrms with proportionally spaced numbers is that they jiggle position
    watch.setTextPadding(80);
    watch.setTextDatum(MC_DATUM);
    watch.setFreeFont(CF_OL32);
    for ( int i = 100; i > 0; i--) {
        watch.drawNumber( i, 160, 200);
        delay(500);
    }

    // Reset text padding to zero (default)
    watch.setTextPadding(0);
}

