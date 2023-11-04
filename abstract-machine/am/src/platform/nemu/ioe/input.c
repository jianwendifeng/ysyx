#include <am.h>
#include <nemu.h>

<<<<<<< HEAD
#define KEYDOWN_MASK 0x8000   //1000000000000000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  int kb_data = inl(KBD_ADDR);
  kbd->keydown = (kb_data & KEYDOWN_MASK ? true : false);  //如果按键按下，结果的最高位（第15位）为1，否则为0。
  kbd->keycode = kb_data & ~KEYDOWN_MASK ;          ////最高位（按键状态位）设为0，而保留其余位（按键断码位）的值
=======
#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
<<<<<<< HEAD
  kbd->keydown = 0;
  kbd->keycode = AM_KEY_NONE;
>>>>>>> a55e7fc7 (NJU-ProjectN/abstract-machine ics2023 initialized)
=======
  int kb_data = inl(KBD_ADDR);
  kbd->keydown = (kb_data & KEYDOWN_MASK) ? true : false ;
  kbd->keycode = kb_data & ~ KEYDOWN_MASK;
>>>>>>> 37f0006a (pa2)
}
