#include <am.h>
#include <nemu.h>

void __am_timer_init() {
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
<<<<<<< HEAD
<<<<<<< HEAD
  uint32_t high = inl(RTC_ADDR + 4 );
  uint32_t low  = inl(RTC_ADDR );
  uptime->us = ((uint64_t)high << 32) + low;
=======
  uptime->us = 0;
>>>>>>> a55e7fc7 (NJU-ProjectN/abstract-machine ics2023 initialized)
=======
  uint32_t high = inl(RTC_ADDR + 4 );
  uint32_t low  = inl(RTC_ADDR );
  uptime->us = ((uint64_t)high << 32) + low;
>>>>>>> 37f0006a (pa2)
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
