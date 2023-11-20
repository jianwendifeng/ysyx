#include <common.h>

#if defined(MULTIPROGRAM) && !defined(TIME_SHARING)
# define MULTIPROGRAM_YIELD() yield()
#else
# define MULTIPROGRAM_YIELD()
#endif

#define NAME(key) \
  [AM_KEY_##key] = #key,

static const char *keyname[256] __attribute__((used)) = {
  [AM_KEY_NONE] = "NONE",
  AM_KEYS(NAME)
};

size_t serial_write(const void *buf, size_t offset, size_t len) {
  size_t i = 0;
  while(len--){
    putch( ((char*)buf)[i++] );
  }
  return i;
}

size_t events_read(void *buf, size_t offset, size_t len) {
  AM_INPUT_KEYBRD_T ev = io_read(AM_INPUT_KEYBRD);
  assert(ev.keycode < 256);

  if(ev.keycode == AM_KEY_NONE){
    *(char*)buf = '\0';
    return 0;
  }

  // printf("Got  (kbd) : %s\t",keyname[ev.keycode]);
  int ret;
  if(ev.keydown == 1){
    ret = snprintf(buf, len, "%s %s", "kd", keyname[ev.keycode]);
  }
  else if(ev.keydown == 0){
    ret = snprintf(buf, len, "%s %s", "ku", keyname[ev.keycode]);
  }
  assert(ret >= 0);
  return ret;
}

// #define N  32
// static uint32_t color_buf[32 * 32];

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  AM_GPU_CONFIG_T vga = io_read(AM_GPU_CONFIG);
  // printf("\n-----\ndispinfo_read,len:%d,width:%d\theight:%d\n-----\n",len,vga.width,vga.height);
  int ret = snprintf(buf, len, "WIDTH:%d\nHEIGHT:%d\n",vga.width,vga.height);
  return ret;
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  // printf("\n-----\noffset:%d\tlen:%d\n-----\n",offset,len);
  if(len == 0) assert(0);
  AM_GPU_CONFIG_T gpu = io_read(AM_GPU_CONFIG);
  AM_GPU_FBDRAW_T ctl;
  
  ctl.pixels = (void *)buf;
  ctl.sync = true;
  ctl.x = offset % gpu.width; //offset 为0,起始坐标为(0，0),x为%循环从0到width-1
  ctl.y = offset / gpu.width; //直接为/后的行
  ctl.w = len >> 32;  //high32 为 w
  ctl.h = len & 0x00000000FFFFFFFF; //low32 为h
  io_write(AM_GPU_FBDRAW, ctl.x, ctl.y, ctl.pixels, ctl.w, ctl.h, ctl.sync);
  // printf("\n-----\noffset:%d\t,width:%d\theight:%d\tvmemsz:%d\tpresent:%d\thas_accel:%d\n-----\n",offset,gpu.width,gpu.height,gpu.vmemsz,gpu.present,gpu.has_accel);
  return 0;
}

void init_device() {
  Log("Initializing devices...");
  ioe_init();
}
