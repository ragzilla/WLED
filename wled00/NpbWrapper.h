//this code is a modified version of https://github.com/Makuna/NeoPixelBus/issues/103
#ifndef NpbWrapper_h
#define NpbWrapper_h

//PIN CONFIGURATION
#ifdef MULTILED
#ifdef ARDUINO_ARCH_ESP32
  #define LEDPIN 19
  #define LEDPIN0 19
  #define PIXELMETHOD NeoEsp32Rmt0Ws2812xMethod
  #define PIXELMETHOD0 NeoEsp32Rmt0Ws2812xMethod
                         // for speed this implementation uses bit shifting and masking, hopefully quicker than integer math
                         // you must fill the 3 values below with matching a column from this table for your longest string
  #define LEDPERPIN 64   // this needs to represent a binary digit value,  e.g. 2,    4,    8,    16,   32,   64,   128,  256
  #define LEDSHIFT 6     // number of bits to shift, based on LEDSPERPIN        1,    2,    3,    4,    5,    6,    7,    8
  #define LEDMASK 0x3f   // the remainder mask, to send pin specific led        0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff
  #if MULTILED > 1
  #define LEDPIN1 18
  #define PIXELMETHOD1 NeoEsp32Rmt1Ws2812xMethod
  #if MULTILED > 2
  #define LEDPIN2 5
  #define PIXELMETHOD2 NeoEsp32Rmt2Ws2812xMethod
  #if MULTILED > 3
  #define LEDPIN3 17
  #define PIXELMETHOD3 NeoEsp32Rmt3Ws2812xMethod
  #if MULTILED > 4
  #define LEDPIN4 33
  #define PIXELMETHOD4 NeoEsp32Rmt4Ws2812xMethod
  #if MULTILED > 5
  #define LEDPIN5 25
  #define PIXELMETHOD5 NeoEsp32Rmt5Ws2812xMethod
  #if MULTILED > 6
  #define LEDPIN6 26
  #define PIXELMETHOD6 NeoEsp32Rmt6Ws2812xMethod
  #if MULTILED > 7
  #define LEDPIN7 27
  #define PIXELMETHOD7 NeoEsp32Rmt7Ws2812xMethod
  #endif // MULTILED > 7
  #endif // MULTILED > 6
  #endif // MULTILED > 5
  #endif // MULTILED > 4
  #endif // MULTILED > 3
  #endif // MULTILED > 2
  #endif // MULTILED > 1
#endif // ARDUINO_ARCH_ESP32
#ifdef ESP8266
  #define LEDPIN 2 // DO NOT CHANGE THIS
  #define LEDPIN0 2 // SERIOUSLY DON'T, USE PINS 2 & 3
  #define PIXELMETHOD NeoEsp8266Uart1Ws2813Method
  #define PIXELMETHOD0 NeoEsp8266Uart1Ws2813Method
                         // for speed this implementation uses bit shifting and masking, hopefully quicker than integer math
                         // you must fill the 3 values below with matching a column from this table for your longest string
  #define LEDPERPIN 64   // this needs to represent a binary digit value,  e.g. 2,    4,    8,    16,   32,   64,   128,  256
  #define LEDSHIFT 6     // number of bits to shift, based on LEDSPERPIN        1,    2,    3,    4,    5,    6,    7,    8
  #define LEDMASK 0x3f   // the remainder mask, to send pin specific led        0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff
  #if MULTILED > 1
  #define LEDPIN1 3 // Don't change this either.
  #define PIXELMETHOD1 NeoEsp8266Dma800KbpsMethod
  #if MULTILED > 2
  #undef MULTILED
  #define MULTILED 2 // cap at 2 for esp8266
  #endif // MULTILED > 2
  #endif // MULTILED > 1
#endif // ESP8266
#endif // MULTILED

#ifndef LEDPIN
#define LEDPIN 2  //strip pin. Any for ESP32, gpio2 or 3 is recommended for ESP8266 (gpio2/3 are labeled D4/RX on NodeMCU and Wemos)
#endif
//#define USE_APA102  // Uncomment for using APA102 LEDs.
//#define USE_WS2801  // Uncomment for using WS2801 LEDs (make sure you have NeoPixelBus v2.5.6 or newer)
//#define USE_LPD8806 // Uncomment for using LPD8806
//#define USE_TM1814  // Uncomment for using TM1814 LEDs (make sure you have NeoPixelBus v2.5.7 or newer)
//#define USE_P9813   // Uncomment for using P9813 LEDs (make sure you have NeoPixelBus v2.5.8 or newer)
//#define WLED_USE_ANALOG_LEDS //Uncomment for using "dumb" PWM controlled LEDs (see pins below, default R: gpio5, G: 12, B: 15, W: 13)
//#define WLED_USE_H801 //H801 controller. Please uncomment #define WLED_USE_ANALOG_LEDS as well
//#define WLED_USE_5CH_LEDS  //5 Channel H801 for cold and warm white
//#define WLED_USE_BWLT11
//#define WLED_USE_SHOJO_PCB

#ifndef BTNPIN
#define BTNPIN  0  //button pin. Needs to have pullup (gpio0 recommended)
#endif

#ifndef IR_PIN
#define IR_PIN  4  //infrared pin (-1 to disable)  MagicHome: 4, H801 Wifi: 0
#endif

#ifndef RLYPIN
#define RLYPIN 12  //pin for relay, will be set HIGH if LEDs are on (-1 to disable). Also usable for standby leds, triggers,...
#endif

#ifndef AUXPIN
#define AUXPIN -1  //debug auxiliary output pin (-1 to disable)
#endif

#ifndef RLYMDE
#define RLYMDE  1  //mode for relay, 0: LOW if LEDs are on 1: HIGH if LEDs are on
#endif

//END CONFIGURATION

#if defined(USE_APA102) || defined(USE_WS2801) || defined(USE_LPD8806) || defined(USE_P9813)
 #ifndef CLKPIN
  #define CLKPIN 0
 #endif
 #ifndef DATAPIN
  #define DATAPIN 2
 #endif
 #if BTNPIN == CLKPIN || BTNPIN == DATAPIN
  #undef BTNPIN   // Deactivate button pin if it conflicts with one of the APA102 pins.
 #endif
#endif

#ifdef WLED_USE_ANALOG_LEDS
  //PWM pins - PINs 15,13,12,14 (W2 = 04)are used with H801 Wifi LED Controller
  #ifdef WLED_USE_H801
    #define RPIN 15   //R pin for analog LED strip   
    #define GPIN 13   //G pin for analog LED strip
    #define BPIN 12   //B pin for analog LED strip
    #define WPIN 14   //W pin for analog LED strip 
    #define W2PIN 04  //W2 pin for analog LED strip
    #undef BTNPIN
    #undef IR_PIN
    #define IR_PIN  0 //infrared pin (-1 to disable)  MagicHome: 4, H801 Wifi: 0
  #elif defined(WLED_USE_BWLT11)
  //PWM pins - to use with BW-LT11
    #define RPIN 12  //R pin for analog LED strip
    #define GPIN 4   //G pin for analog LED strip
    #define BPIN 14  //B pin for analog LED strip
    #define WPIN 5   //W pin for analog LED strip
  #elif defined(WLED_USE_SHOJO_PCB)
  //PWM pins - to use with Shojo PCB (https://www.bastelbunker.de/esp-rgbww-wifi-led-controller-vbs-edition/)
    #define RPIN 14  //R pin for analog LED strip
    #define GPIN 4   //G pin for analog LED strip
    #define BPIN 5   //B pin for analog LED strip
    #define WPIN 15  //W pin for analog LED strip
    #define W2PIN 12 //W2 pin for analog LED strip
  #elif defined(WLED_USE_PLJAKOBS_PCB)
  // PWM pins - to use with esp_rgbww_controller from patrickjahns/pljakobs (https://github.com/pljakobs/esp_rgbww_controller)
    #define RPIN 12  //R pin for analog LED strip
    #define GPIN 13  //G pin for analog LED strip
    #define BPIN 14  //B pin for analog LED strip
    #define WPIN 4   //W pin for analog LED strip
    #define W2PIN 5  //W2 pin for analog LED strip
    #undef IR_PIN
  #else
  //PWM pins - PINs 5,12,13,15 are used with Magic Home LED Controller
    #define RPIN 5   //R pin for analog LED strip
    #define GPIN 12  //G pin for analog LED strip
    #define BPIN 15  //B pin for analog LED strip
    #define WPIN 13  //W pin for analog LED strip
  #endif
  #undef RLYPIN
  #define RLYPIN -1 //disable as pin 12 is used by analog LEDs
#endif

//automatically uses the right driver method for each platform
#ifndef PIXELMETHOD
#ifdef ARDUINO_ARCH_ESP32
 #ifdef USE_APA102
  #define PIXELMETHOD DotStarMethod
 #elif defined(USE_WS2801)
  #define PIXELMETHOD NeoWs2801Method
 #elif defined(USE_LPD8806)
  #define PIXELMETHOD Lpd8806Method
 #elif defined(USE_TM1814)
  #define PIXELMETHOD NeoTm1814Method  
 #elif defined(USE_P9813)
  #define PIXELMETHOD P9813Method  
 #else
  #define PIXELMETHOD NeoEsp32Rmt0Ws2812xMethod
 #endif
#else //esp8266
 //autoselect the right method depending on strip pin
 #ifdef USE_APA102
  #define PIXELMETHOD DotStarMethod
 #elif defined(USE_WS2801)
  #define PIXELMETHOD NeoWs2801Method
 #elif defined(USE_LPD8806)
  #define PIXELMETHOD Lpd8806Method
 #elif defined(USE_TM1814)
  #define PIXELMETHOD NeoTm1814Method  
 #elif defined(USE_P9813)
  #define PIXELMETHOD P9813Method  
 #elif LEDPIN == 2
  #define PIXELMETHOD NeoEsp8266Uart1Ws2813Method //if you get an error here, try to change to NeoEsp8266UartWs2813Method or update Neopixelbus
 #elif LEDPIN == 3
  #define PIXELMETHOD NeoEsp8266Dma800KbpsMethod
 #else
  #define PIXELMETHOD NeoEsp8266BitBang800KbpsMethod
  #pragma message "Software BitBang will be used because of your selected LED pin. This may cause flicker. Use GPIO 2 or 3 for best results."
 #endif
#endif 
#endif // PIXELMETHOD


//you can now change the color order in the web settings
#ifdef USE_APA102
 #define PIXELFEATURE3 DotStarBgrFeature
 #define PIXELFEATURE4 DotStarLbgrFeature
#elif defined(USE_LPD8806)
 #define PIXELFEATURE3 Lpd8806GrbFeature 
#elif defined(USE_WS2801)
 #define PIXELFEATURE3 NeoRbgFeature
 #define PIXELFEATURE4 NeoRbgFeature
#elif defined(USE_TM1814)
  #define PIXELFEATURE3 NeoWrgbTm1814Feature
  #define PIXELFEATURE4 NeoWrgbTm1814Feature
#elif defined(USE_P9813)
 #define PIXELFEATURE3 P9813BgrFeature 
 #define PIXELFEATURE4 NeoGrbwFeature   
#else
 #define PIXELFEATURE3 NeoGrbFeature
 #define PIXELFEATURE4 NeoGrbwFeature
#endif


#include <NeoPixelBrightnessBus.h>

enum NeoPixelType
{
  NeoPixelType_None = 0,
  NeoPixelType_Grb  = 1,
  NeoPixelType_Grbw = 2,
  NeoPixelType_End  = 3
};

class NeoPixelWrapper
{
public:
  NeoPixelWrapper() :
    // initialize each member to null
    _pGrb(NULL),
    #ifdef MULTILED
      #if MULTILED > 1
        _pGrb1(NULL),
      #if MULTILED > 2
        _pGrb2(NULL),
      #if MULTILED > 3
        _pGrb3(NULL),
      #if MULTILED > 4
        _pGrb4(NULL),
      #if MULTILED > 5
        _pGrb5(NULL),
      #if MULTILED > 6
        _pGrb6(NULL),
      #if MULTILED > 7
        _pGrb7(NULL),
      #endif // MULTILED > 7
      #endif // MULTILED > 6
      #endif // MULTILED > 5
      #endif // MULTILED > 4
      #endif // MULTILED > 3
      #endif // MULTILED > 2
      #endif // MULTILED > 1
    #endif // MULTILED
    _pGrbw(NULL),
    _type(NeoPixelType_None)
  {

  }

  ~NeoPixelWrapper()
  {
    cleanup();
  }

  void Begin(NeoPixelType type, uint16_t countPixels)
  {
    cleanup();
    _type = type;

    switch (_type)
    {
      case NeoPixelType_Grb:
      #if defined(USE_APA102) || defined(USE_WS2801) || defined(USE_LPD8806) || defined(USE_P9813)
        _pGrb = new NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD>(countPixels, CLKPIN, DATAPIN);
      #else
        #ifndef MULTILED
        _pGrb = new NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD>(countPixels, LEDPIN);
        _pGrb->Begin();
        #else
          _pGrb = new NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD>(LEDPERPIN, LEDPIN0);
          _pGrb->Begin();
          yield();
          #if MULTILED > 1
            _pGrb1 = new NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD1>(LEDPERPIN, LEDPIN1);
            _pGrb1->Begin();
            yield();
          #if MULTILED > 2
            _pGrb2 = new NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD2>(LEDPERPIN, LEDPIN2);
            _pGrb2->Begin();
            yield();
          #if MULTILED > 3
            _pGrb3 = new NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD3>(LEDPERPIN, LEDPIN3);
            _pGrb3->Begin();
            yield();
          #if MULTILED > 4
            _pGrb4 = new NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD4>(LEDPERPIN, LEDPIN4);
            _pGrb4->Begin();
            yield();
          #if MULTILED > 5
            _pGrb5 = new NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD5>(LEDPERPIN, LEDPIN5);
            _pGrb5->Begin();
            yield();
          #if MULTILED > 6
            _pGrb6 = new NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD6>(LEDPERPIN, LEDPIN6);
            _pGrb6->Begin();
            yield();
          #if MULTILED > 7
            _pGrb7 = new NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD7>(LEDPERPIN, LEDPIN7);
            _pGrb7->Begin();
            yield();
          #endif // MULTILED > 7
          #endif // MULTILED > 6
          #endif // MULTILED > 5
          #endif // MULTILED > 4
          #endif // MULTILED > 3
          #endif // MULTILED > 2
          #endif // MULTILED > 1
        #endif // MULTILED
      #endif
      break;
      
      case NeoPixelType_Grbw:
      #if defined(USE_APA102) || defined(USE_WS2801) || defined(USE_LPD8806) || defined(USE_P9813)
        _pGrbw = new NeoPixelBrightnessBus<PIXELFEATURE4,PIXELMETHOD>(countPixels, CLKPIN, DATAPIN);
      #else
        _pGrbw = new NeoPixelBrightnessBus<PIXELFEATURE4,PIXELMETHOD>(countPixels, LEDPIN);
      #endif
        _pGrbw->Begin();
      break;
    }

    #ifdef WLED_USE_ANALOG_LEDS 
      #ifdef ARDUINO_ARCH_ESP32
        ledcSetup(0, 5000, 8);
        ledcAttachPin(RPIN, 0);
        ledcSetup(1, 5000, 8);
        ledcAttachPin(GPIN, 1);
        ledcSetup(2, 5000, 8);        
        ledcAttachPin(BPIN, 2);
        if(_type == NeoPixelType_Grbw) 
        {
          ledcSetup(3, 5000, 8);        
          ledcAttachPin(WPIN, 3);
          #ifdef WLED_USE_5CH_LEDS
            ledcSetup(4, 5000, 8);        
            ledcAttachPin(W2PIN, 4);
          #endif
        }
      #else  // ESP8266
        //init PWM pins
        pinMode(RPIN, OUTPUT);
        pinMode(GPIN, OUTPUT);
        pinMode(BPIN, OUTPUT); 
        if(_type == NeoPixelType_Grbw) 
        {
          pinMode(WPIN, OUTPUT); 
          #ifdef WLED_USE_5CH_LEDS
            pinMode(W2PIN, OUTPUT);
          #endif
        }
        analogWriteRange(255);  //same range as one RGB channel
        analogWriteFreq(880);   //PWM frequency proven as good for LEDs
      #endif 
    #endif
  }

#ifdef WLED_USE_ANALOG_LEDS      
    void SetRgbwPwm(uint8_t r, uint8_t g, uint8_t b, uint8_t w, uint8_t w2=0)
    {
      #ifdef ARDUINO_ARCH_ESP32
        ledcWrite(0, r);
        ledcWrite(1, g);
        ledcWrite(2, b);
        switch (_type) {
          case NeoPixelType_Grb:                                                  break;
          #ifdef WLED_USE_5CH_LEDS
            case NeoPixelType_Grbw: ledcWrite(3, w); ledcWrite(4, w2);            break;
          #else
            case NeoPixelType_Grbw: ledcWrite(3, w);                              break;
          #endif
        }        
      #else   // ESP8266
        analogWrite(RPIN, r);
        analogWrite(GPIN, g);
        analogWrite(BPIN, b);
        switch (_type) {
          case NeoPixelType_Grb:                                                  break;
          #ifdef WLED_USE_5CH_LEDS
            case NeoPixelType_Grbw: analogWrite(WPIN, w); analogWrite(W2PIN, w2); break;
          #else
            case NeoPixelType_Grbw: analogWrite(WPIN, w);                         break;
          #endif
        }
      #endif 
    }
#endif

  void Show()
  {
    byte b;
    switch (_type)
    {
      case NeoPixelType_Grb:  _pGrb->Show();  
      #ifdef MULTILED
        #if MULTILED > 1
        _pGrb1->Show();
        #if MULTILED > 2
        _pGrb2->Show();
        #if MULTILED > 3
        _pGrb3->Show();
        #if MULTILED > 4
        _pGrb4->Show();
        #if MULTILED > 5
        _pGrb5->Show();
        #if MULTILED > 6
        _pGrb6->Show();
        #if MULTILED > 7
        _pGrb7->Show();
        #endif // MULTILED > 7
        #endif // MULTILED > 6
        #endif // MULTILED > 5
        #endif // MULTILED > 4
        #endif // MULTILED > 3
        #endif // MULTILED > 2
        #endif // MULTILED > 1
      #endif // MULTILED
        break;
      case NeoPixelType_Grbw: _pGrbw->Show(); break;
    }
  }

  void SetPixelColor(uint16_t indexPixel, RgbwColor color)
  {
    switch (_type) {
      case NeoPixelType_Grb: {
        #ifndef MULTILED
        _pGrb->SetPixelColor(indexPixel, RgbColor(color.R,color.G,color.B));
        #else
        if (indexPixel < LEDPERPIN) { _pGrb->SetPixelColor(indexPixel & LEDMASK, RgbColor(color.R,color.G,color.B)); return; }
          #if MULTILED > 1
        if (indexPixel < 2 * LEDPERPIN) { _pGrb1->SetPixelColor(indexPixel & LEDMASK, RgbColor(color.R,color.G,color.B)); return; }
          #if MULTILED > 2
        if (indexPixel < 3 * LEDPERPIN) { _pGrb2->SetPixelColor(indexPixel & LEDMASK, RgbColor(color.R,color.G,color.B)); return; }
          #if MULTILED > 3
        if (indexPixel < 4 * LEDPERPIN) { _pGrb3->SetPixelColor(indexPixel & LEDMASK, RgbColor(color.R,color.G,color.B)); return; }
          #if MULTILED > 4
        if (indexPixel < 5 * LEDPERPIN) { _pGrb4->SetPixelColor(indexPixel & LEDMASK, RgbColor(color.R,color.G,color.B)); return; }
          #if MULTILED > 5
        if (indexPixel < 6 * LEDPERPIN) { _pGrb5->SetPixelColor(indexPixel & LEDMASK, RgbColor(color.R,color.G,color.B)); return; }
          #if MULTILED > 6
        if (indexPixel < 7 * LEDPERPIN) { _pGrb6->SetPixelColor(indexPixel & LEDMASK, RgbColor(color.R,color.G,color.B)); return; }
          #if MULTILED > 7
        if (indexPixel < 8 * LEDPERPIN) { _pGrb7->SetPixelColor(indexPixel & LEDMASK, RgbColor(color.R,color.G,color.B)); return; }
          #endif // MULTILED > 7
          #endif // MULTILED > 6
          #endif // MULTILED > 5
          #endif // MULTILED > 4
          #endif // MULTILED > 3
          #endif // MULTILED > 2
          #endif // MULTILED > 1
        //}
        #endif MULTILED
      }
      break;
      case NeoPixelType_Grbw: {
        #if defined(USE_LPD8806) || defined(USE_WS2801)
        _pGrbw->SetPixelColor(indexPixel, RgbColor(color.R,color.G,color.B));
        #else
        _pGrbw->SetPixelColor(indexPixel, color);
        #endif
      }
      break;
    }
    
  }

  void SetBrightness(byte b)
  {
    switch (_type) {
      case NeoPixelType_Grb: _pGrb->SetBrightness(b);   
      #ifdef MULTILED
        #if MULTILED > 1
        _pGrb1->SetBrightness(b);
        #if MULTILED > 2
        _pGrb2->SetBrightness(b);
        #if MULTILED > 3
        _pGrb3->SetBrightness(b);
        #if MULTILED > 4
        _pGrb4->SetBrightness(b);
        #if MULTILED > 5
        _pGrb5->SetBrightness(b);
        #if MULTILED > 6
        _pGrb6->SetBrightness(b);
        #if MULTILED > 7
        _pGrb7->SetBrightness(b);
        #endif // MULTILED > 7
        #endif // MULTILED > 6
        #endif // MULTILED > 5
        #endif // MULTILED > 4
        #endif // MULTILED > 3
        #endif // MULTILED > 2
        #endif // MULTILED > 1
      #endif // MULTILED
        break;
      case NeoPixelType_Grbw:_pGrbw->SetBrightness(b);  break;
    }
  }

  // NOTE:  Due to feature differences, some support RGBW but the method name
  // here needs to be unique, thus GetPixeColorRgbw
  RgbwColor GetPixelColorRgbw(uint16_t indexPixel) const
  {
    switch (_type) {
      case NeoPixelType_Grb:  
        #ifndef MULTILED
        return _pGrb->GetPixelColor(indexPixel);  break;
        #else
        switch ((indexPixel >> LEDSHIFT) & 0x03) {
          case 0: return _pGrb->GetPixelColor(indexPixel & LEDMASK);  break;
          #if MULTILED > 1
          case 1: return _pGrb1->GetPixelColor(indexPixel & LEDMASK);  break;
          #if MULTILED > 2
          case 2: return _pGrb2->GetPixelColor(indexPixel & LEDMASK);  break;
          #if MULTILED > 3
          case 3: return _pGrb3->GetPixelColor(indexPixel & LEDMASK);  break;
          #if MULTILED > 4
          case 4: return _pGrb4->GetPixelColor(indexPixel & LEDMASK);  break;
          #if MULTILED > 5
          case 5: return _pGrb5->GetPixelColor(indexPixel & LEDMASK);  break;
          #if MULTILED > 6
          case 6: return _pGrb6->GetPixelColor(indexPixel & LEDMASK);  break;
          #if MULTILED > 7
          case 7: return _pGrb7->GetPixelColor(indexPixel & LEDMASK);  break;
          #endif // MULTILED > 7
          #endif // MULTILED > 6
          #endif // MULTILED > 5
          #endif // MULTILED > 4
          #endif // MULTILED > 3
          #endif // MULTILED > 2
          #endif // MULTILED > 1
        }
        #endif MULTILED
      break;
      case NeoPixelType_Grbw: return _pGrbw->GetPixelColor(indexPixel); break;
    }
    return 0;
  }

private:
  NeoPixelType _type;

  // have a member for every possible type
  NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD>*  _pGrb;
  NeoPixelBrightnessBus<PIXELFEATURE4,PIXELMETHOD>* _pGrbw;
  #ifdef MULTILED
    #if MULTILED > 1
    NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD1>*  _pGrb1;
    #if MULTILED > 2
    NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD2>*  _pGrb2;
    #if MULTILED > 3
    NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD3>*  _pGrb3;
    #if MULTILED > 4
    NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD4>*  _pGrb4;
    #if MULTILED > 5
    NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD5>*  _pGrb5;
    #if MULTILED > 6
    NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD6>*  _pGrb6;
    #if MULTILED > 7
    NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD7>*  _pGrb7;
    #endif // MULTILED > 7
    #endif // MULTILED > 6
    #endif // MULTILED > 5
    #endif // MULTILED > 4
    #endif // MULTILED > 3
    #endif // MULTILED > 2
    #endif // MULTILED > 1
  #endif // MULTILED

  void cleanup()
  {
    switch (_type) {
      case NeoPixelType_Grb:  delete _pGrb ; _pGrb  = NULL; 
      #ifdef MULTILED
        #if MULTILED > 1
        delete _pGrb1 ; _pGrb1  = NULL; 
        #if MULTILED > 2
        delete _pGrb2 ; _pGrb2  = NULL; 
        #if MULTILED > 3
        delete _pGrb3 ; _pGrb3  = NULL; 
        #if MULTILED > 4
        delete _pGrb4 ; _pGrb4  = NULL; 
        #if MULTILED > 5
        delete _pGrb5 ; _pGrb5  = NULL; 
        #if MULTILED > 6
        delete _pGrb6 ; _pGrb6  = NULL; 
        #if MULTILED > 7
        delete _pGrb7 ; _pGrb7  = NULL; 
        #endif // MULTILED > 7
        #endif // MULTILED > 6
        #endif // MULTILED > 5
        #endif // MULTILED > 4
        #endif // MULTILED > 3
        #endif // MULTILED > 2
        #endif // MULTILED > 1
      #endif // MULTILED
        break;
      case NeoPixelType_Grbw: delete _pGrbw; _pGrbw = NULL; 
        break;
    }
  }
};
#endif
