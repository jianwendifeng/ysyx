#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

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

int snprintf(char *out, size_t n, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int length = vsnprintf(out, n, fmt, ap);
    va_end(ap);
    return length;
}

#endif