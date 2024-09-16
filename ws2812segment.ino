#include <WS2812FX.h>

#define LED_PIN 3    // digital pin used to drive the LED strip
#define LED_COUNT 16 // number of LEDs on the strip
long int lastmil = 0;
#define DELAY 5000
bool Which = false;

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(115200);
  ws2812fx.init();
  ws2812fx.setBrightness(128);
  ws2812fx.start();
}

void loop()
{
  ws2812fx.service();
  if (lastmil + DELAY < millis())
  {
    Serial.println("Switch Is Now");
    lastmil = millis();

    if (Which)
    {
      Serial.println("Switch True");
      ws2812fx.removeActiveSegment(1);
      ws2812fx.removeActiveSegment(2);
      ws2812fx.removeActiveSegment(3);
      ws2812fx.removeActiveSegment(4);
      ws2812fx.stop();
      ws2812fx.setSegment(0, 0, 15, FX_MODE_STATIC, GREEN, 1000, false);
      ws2812fx.start();
    }
    else
    {
      Serial.println("Switch False");
      ws2812fx.removeActiveSegment(0);
      ws2812fx.stop();
      ws2812fx.setSegment(1, 0, 3, FX_MODE_STATIC, RED, 1000, false);
      ws2812fx.setSegment(2, 4, 7, FX_MODE_STATIC, ORANGE, 1000, false);
      ws2812fx.setSegment(3, 8, 11, FX_MODE_STATIC, CYAN, 1000, false);
      ws2812fx.setSegment(4, 12, 15, FX_MODE_STATIC, YELLOW, 1000, false);
      ws2812fx.start();
    }
    Which = !Which;
  }
}
