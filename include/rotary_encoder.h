#ifndef RE_H
#define RE_H

#include <inttypes.h>
#define BTN_PRESSED 1
#define BTN_NOT_PRESSED 0  
void setup_encoder(uint8_t pinA, uint8_t pinB, uint8_t pinSW);
int32_t get_encoder_state();
void set_encoder_state(int32_t value);
void SWButtonPress(uint32_t &btn_state, int &btn_counter);

#endif // RE_H