#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <assert.h>
#include <fcntl.h>
static int evtdev = -1;
static int fbdev = -1;
static int screen_w = 0, screen_h = 0;

uint32_t NDL_GetTicks() {
  struct timeval now;
  gettimeofday(&now, NULL);
  // printf("\n-----\nus:%ld\n-----\n",now.tv_usec/1000);
  return now.tv_usec / 1000;  //syscall 里系统调用用us表示
}

int NDL_PollEvent(char *buf, int len) {
  int fp = open("/dev/events", 0, 0);
  if(fp == -1) return 0;
  else return (int)read(fp, buf, len);
}

void NDL_OpenCanvas(int *w, int *h) {
  // if (getenv("NWM_APP")) {
  //   int fbctl = 4;
  //   fbdev = 5;
  //   screen_w = *w; screen_h = *h;
  //   char buf[64];
  //   int len = sprintf(buf, "%d %d", screen_w, screen_h);
  //   // let NWM resize the window and create the frame buffer
  //   write(fbctl, buf, len);
  //   while (1) {
  //     // 3 = evtdev
  //     int nread = read(3, buf, sizeof(buf) - 1);
  //     if (nread <= 0) continue;
  //     buf[nread] = '\0';
  //     if (strcmp(buf, "mmap ok") == 0) break;
  //   }
  //   close(fbctl);
  // }
  
  int fp = open("/proc/dispinfo", 0, 0);
  // printf("fp:%d\n",fp);
  // assert(fp);
  if(!fp){
    printf("\n-----\nError open /pro/dispinfo\n-----\n");
    return;
  }
  char buf[64];
  read(fp, buf, sizeof(buf) - 1); // `4`号文件是图形控制管道,应用程序期望创建的窗口宽度和高度
  // printf("\n-----\nbuf:%s\n-----\n",buf);
  sscanf(buf,"WIDTH:%d\nHEIGHT:%d\n",&screen_w,&screen_h);

  if (*w == 0 && *h == 0) {
    *w = screen_w;
    *h = screen_h;
  }
  assert(screen_w >= *w && screen_h >= *h);
  // printf("\n-----\nWIDTH:%d\tHEIGHT:%d\tw:%d\th:%d\n-----\n",screen_w, screen_h,*w,*h);
  close(fp);
}

void NDL_DrawRect(uint32_t *pixels, int x, int y, int w, int h) {
  // printf("\n-----\nx:%d\ty:%d\tw:%d\th:%d\tscreen_w:%d\tscreen_h:%d\toffset:%d\t\n-----\n",x,y,w,h,screen_w,screen_h,x*y);
  int fp = open("/dev/fb", 0, 0);
  #if defined(__ISA_NATIVE__)
    for(int j=0; j<h; j++){
      lseek(fp,((y+j)*screen_w+x)*4,SEEK_SET);
      write(fp, pixels+w*j, 4*w);
    }
  #else 
    lseek(fp,x*y,SEEK_SET);
    write(fp, pixels, ((size_t)w<<32) | ((size_t)h & 0x00000000FFFFFFFF)); //w=high32bit, h=low32bit
  #endif
  close(fp);
}

void NDL_OpenAudio(int freq, int channels, int samples) {
}

void NDL_CloseAudio() {
}

int NDL_PlayAudio(void *buf, int len) {
  return 0;
}

int NDL_QueryAudio() {
  return 0;
}

int NDL_Init(uint32_t flags) {
  if (getenv("NWM_APP")) {
    evtdev = 3;
  }
  return 0;
}

void NDL_Quit() {
}
