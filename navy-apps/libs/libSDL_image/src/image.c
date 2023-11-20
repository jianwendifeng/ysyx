#define SDL_malloc  malloc
#define SDL_free    free
#define SDL_realloc realloc

#define SDL_STBIMAGE_IMPLEMENTATION
#include "SDL_stbimage.h"

SDL_Surface* IMG_Load_RW(SDL_RWops *src, int freesrc) {
  assert(src->type == RW_TYPE_MEM);
  assert(freesrc == 0);
  return NULL;
}

SDL_Surface* IMG_Load(const char *filename) {
  FILE* fd = fopen(filename, "rb");
  assert(fd);

  // 获取文件大小
  fseek(fd, 0, SEEK_END);
  long size = ftell(fd);
  rewind(fd);

  // 申请内存区域
  unsigned char* buf = (unsigned char*)malloc(size);
  assert(buf);

  // 将文件读取到缓冲区
  if (fread(buf, 1, size, fd) != size) {
      printf("\n-----\nError reading file: %s\n-----\n", filename);
      fclose(fd);
      free(buf);
      return NULL;
  }

  // 调用STBIMG_LoadFromMemory，加载图像
  int width, height, channels;
  unsigned char* pixels = stbi_load_from_memory(buf, size, &width, &height, &channels, 4);  // 4表示希望输出32位像素
  assert(pixels);

  // 创建SDL Surface
  SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, width, height, 32, width * 4, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

  // 关闭文件，释放内存
  fclose(fd);
  free(buf);

  return surface;
}

int IMG_isPNG(SDL_RWops *src) {
  return 0;
}

SDL_Surface* IMG_LoadJPG_RW(SDL_RWops *src) {
  return IMG_Load_RW(src, 0);
}

char *IMG_GetError() {
  return "Navy does not support IMG_GetError()";
}
