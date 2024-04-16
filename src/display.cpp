#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "display.hpp"

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);


#define display_state_width DISPLAY_WIDTH
#define display_state_height DISPLAY_HEIGHT
unsigned char display_state_bits[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8] = {};


void display_prepare(void)
{
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    digitalWrite(10, 0);
    digitalWrite(9, 0);
    u8g2.begin();
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);

    u8g2.firstPage();
    do {
        u8g2.drawStr(0, 20, "Init done");
    } while (u8g2.nextPage());
    delay(2000);
}


void convert_state_to_xmp(bool game_state[], unsigned char display_state[]) {
    for (size_t i = 0; i < DISPLAY_HEIGHT * DISPLAY_WIDTH / 8; i++)
    {
        unsigned char tmp = 0;
        for (size_t j = 0; j < 8; j++)
        {
            tmp |= game_state[j + 8 * i] << j;
        }
        display_state[i] = tmp;
    }
    
}


void draw_state(bool game_state[])
{
    convert_state_to_xmp(game_state, display_state_bits);
    u8g2.firstPage();
    do {
        u8g2.drawXBM(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, display_state_bits);
    } while (u8g2.nextPage());
}
