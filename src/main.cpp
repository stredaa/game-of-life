#include <Arduino.h>
#include "display.hpp"
#include "gol.hpp"


GameOfLife instance = GameOfLife();


void setup(void) {
    display_prepare();
    randomSeed(analogRead(0));
}

void loop(void) {
  draw_state(instance.getState());
  instance.step();
  delay(500);
}