#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

<<<<<<< HEAD
<<<<<<< HEAD
#define SIZE_MAX_BUF 128
=======
int printf(const char *fmt, ...) {
  panic("Not implemented");
=======
#define KLIB_MAX_BUF (4 * 1024)

void* itoa(unsigned  num, char* str, int base) {  //鐢变簬鍓嶉潰宸茬粡澶勭悊浜嗚礋鏁帮紝num榛樿鏄潪璐熸暟锛屼紶鍏ユ椂鍊欎篃搴旇鏄潪璐熸暟鎵嶅锛屽鏋滄槸int锛屽氨浼氬鑷翠竴鐩村嚭鐜板儚锛堬紵锛佺瓑绗﹀彿
    int i = 0;
    if (num == 0) {
        str[i++] = '0';
    } else {
        while (num != 0) {
            int remainder = num % base;
            str[i++] = (remainder > 9) ? (remainder + 'A' - 10)   : remainder + '0'; // 浣跨敤澶у啓瀛楁瘝 'A'-'F'
            num /= base; //num = num / base;
        }
    }

    str[i] = '\0';

    // 鍙嶈浆瀛楃涓?
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }

    return str;
}


int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
    int len = 0;
  
    for (; *fmt != '\0'; fmt++) {
        while (*fmt != '%' && *fmt != '\0') {
            out[len++] = *fmt++;
            if (len > n) return n;
        }
        if (*fmt == '%') {
            fmt++;
        } else if (*fmt == '\0') {
            break;
        }

        switch (*fmt) {
            case 's': {
                char* tmp_str = va_arg(ap, char*);
                while (*tmp_str != '\0') {
                    out[len++] = *tmp_str++;
                    if (len > n) return n;
                }
                break;
            }
                
            case 'd': {
                int tmp_dex = va_arg(ap, int);
                if (tmp_dex < 0) {
                    tmp_dex = -tmp_dex;
                    out[len++] = '-';   // 璐熸暟
                    if (len > n) return n;
                }
                char out_str_dex[n];
                itoa(tmp_dex, out_str_dex, 10);
                int i = 0;
                while (out_str_dex[i] != '\0') {
                    out[len++] = out_str_dex[i++];
                    if (len > n) return n;
                }
                break;
            }
                
            case 'x':
            case 'p': {
                out[len++] = '0';
                out[len++] = 'x';
                uint64_t tmp_hex = va_arg(ap, uint64_t);
                char out_str_hex[n]; 
                itoa(tmp_hex, out_str_hex, 16);
                int j = 0;
                while (out_str_hex[j] != '\0') {
                    out[len++] = out_str_hex[j++];
                    if (len > n) return n;
                }
                break;
            }
        }
    }
    if (len > n) return n;
    out[len++] = '\0';
    return len;
>>>>>>> 37f0006a (pa2)
}

int vsprintf(char *out, const char *fmt, va_list ap) {
    return vsnprintf(out, KLIB_MAX_BUF, fmt, ap);
}

int printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    char out[KLIB_MAX_BUF];
    int lenth = vsprintf(out, fmt, ap);
    for (int i = 0; i < lenth; i++) {
        putch(out[i]);
    }
    va_end(ap);
    return lenth;
}

int sprintf(char *out, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int length = vsprintf(out, fmt, ap);
    va_end(ap);
    return length;
}
>>>>>>> a55e7fc7 (NJU-ProjectN/abstract-machine ics2023 initialized)

int snprintf(char *out, size_t n, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int length = vsnprintf(out, n, fmt, ap);
    va_end(ap);
    return length;
}

<<<<<<< HEAD
<<<<<<< HEAD

void reverse(char* num,int len,char* out){

    int start = 0;
    int end = len- 1;
    
    while(start < len){
        *out = num[end] +'0';
        out++;
        start++;
        end--;
    }
}

int itoa(int num,char *out,int base){
	int len = 0;
	char temp[SIZE_MAX_BUF]; 
	int i = 0;
    if(num == 0) {
    	*out++ = 0;
    	len++;
    	return len;
	}
	if(num < 0 ){
		*out++ = '-';
		len++;
		num = -num;
	}
	
	do{
    	temp[i] = (num % base) ;
    //	printf("temp[%d]:%d\n",i,temp[i]);
    	i++;
    	num = num / base;
    	len++;

	}while(num  != 0 );
	reverse(temp,i,out);
    return len;
}


int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
    int len = 0;
    while(*fmt != '\0'){
        if(*fmt != '%' ){
        	*out++ = *fmt++; 
        	len++;
        }
        else{
            switch (*++fmt){
                case 'd':
                	fmt++;
                    int tmp_int = va_arg(ap,int);
                    int i = itoa(tmp_int,out,10);
                    out += i;
                    len += i;
                    break;
                case 's':
                    fmt++;
                    char *tmp_ch = va_arg(ap,char*);
                     while (*tmp_ch != '\0') {
                        out[++len] = *tmp_ch++;
                    }
                    break;
                default:
                    out[len++] = *fmt++;
                    //out[len++] = *fmt++;
                    break;
            }
        }
  
    }
    out[len] = '\0';
    return len;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
    int count = 0;
    count = vsnprintf(out, SIZE_MAX_BUF, fmt, ap);
    return count;
}

int sprintf(char *out, const char *fmt, ...)
{ 
  int i = 0 ;
  while (i<SIZE_MAX_BUF){
    out[i++] = 0;
  }
  va_list args;
  int len = 0;
	
  va_start(args,fmt);
  len = vsprintf(out,fmt,args);
  va_end(args);

  return len;
}


int printf(const char *fmt, ...) {
  va_list ap;
  char buf[SIZE_MAX_BUF];
   int i = 0 ;
  while (i<SIZE_MAX_BUF){
    buf[i++] = 0;
  }
  va_start(ap, fmt);
  int len = vsprintf(buf, fmt, ap);
  va_end(ap);
  i=0;
  while(i < len){
    putch(buf[i++]);
  }
  return 0;
}




#endif	
=======
int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
>>>>>>> a55e7fc7 (NJU-ProjectN/abstract-machine ics2023 initialized)
=======
#endif
>>>>>>> 37f0006a (pa2)
