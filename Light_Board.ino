//CUSTOM LIGHT BOARD
//Author: Brendan Li
//Completed: 12/21/21


//Using FastLED library for these LEDs
#include <FastLED.h>

const int buttonPin = 2;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status
#define DATA_PIN 5
#define NUM_LEDS    9
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
int set = 0;
#define UPDATES_PER_SECOND 100


CRGBPalette16 currentPalette;
TBlendType    currentBlending;

//VOID SETUP
void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}

//VOID LOOP
void loop()
{
    buttonState = digitalRead(buttonPin);
    // check if the pushbutton is pressed. add to the set
    if (buttonState == HIGH) {
        set++;
        delay(1000);
    }
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors( startIndex);
    currentBlending = LINEARBLEND; 
    //depending on the set value, set a certain palette
    if( set ==  0)  { Pink();}
    if( set == 1)  { Aqua(); }
    if( set == 2)  { Red(); }
    if( set == 3)  { currentPalette = PartyColors_p; }
    if( set == 4)  { currentPalette = RainbowStripeColors_p; currentBlending = NOBLEND;}
    if(set == 5){set=0;}
    //send palette to LEDs
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

//FastLED FUNCTION
void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}


// This function sets up a palette of mainly red and purple colors
void Red()
{
    CRGB red = CHSV( HUE_RED, 255, 255);
    CRGB purple  = CHSV( HUE_PURPLE, 255, 255);
    
    currentPalette = CRGBPalette16(purple, purple, red, red);

}
//Aqua colored palette
void Aqua()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 9, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::Aqua;
    currentPalette[4] = CRGB::Aqua;
    currentPalette[8] = CRGB::Aqua;
    currentPalette[12] = CRGB::Aqua;
    
}

// pink colored palette
void Pink()
{
    CRGB aqua = CHSV( HUE_AQUA, 255, 255);
    CRGB pink  = CHSV( HUE_PINK, 255, 255);
    
    currentPalette = CRGBPalette16(aqua, pink, aqua, pink);
}
