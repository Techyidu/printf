#include <stdio.h>
#include <stdarg.h>

#define BUFF_SIZE 1024

void print_buffer(char buffer[], int *buff_ind) {
  if (*buff_ind > 0) {
    write(1, &buffer[0], *buff_ind);
    *buff_ind = 0;
  }
}

int get_flags(const char *format, int *i) {
  int flags = 0;
  while (format[*i] == ' ') {
    *i++;
  }
  if (format[*i] == '-') {
    flags |= FLAG_LEFT_JUSTIFY;
    *i++;
  } else if (format[*i] == '+') {
    flags |= FLAG_SIGN;
    *i++;
  } else if (format[*i] == '#') {
    flags |= FLAG_ALTERNATE;
    *i++;
  }
  return flags;
}

int get_width(const char *format, int *i, va_list list) {
  int width = 0;
  while (format[*i] >= '0' && format[*i] <= '9') {
    width = width * 10 + (format[*i] - '0');
    *i++;
  }
  if (format[*i] == '*') {
    width = va_arg(list, int);
    *i++;
  }
  return width;
}

int get_precision(const char *format, int *i, va_list list) {
  int precision = -1;
  if (format[*i] == '.') {
    *i++;
    if (format[*i] == '*') {
      precision = va_arg(list, int);
      *i++;
    } else {
      while (format[*i] >= '0' && format[*i] <= '9') {
        precision = precision * 10 + (format[*i] - '0');
        *i++;
      }
    }
  }
  return precision;
}

int get_size(const char *format, int *i) {
  int size = 0;
  if (format[*i] == 'h') {
    size |= SIZE_H;
    *i++;
  } else if (format[*i] == 'l') {
    size |= SIZE_L;
    *i++;
  }
  return size;
}

int handle_print(const char *format, int *i, va_list list, char buffer[],
                 int flags, int width, int precision, int size) {
  int printed = 0;
  switch (format[*i]) {
    case 'c': {
      char ch = va_arg(list, int);
      buffer[printed++] = ch;
      break;
    }
    case 's': {
      char *str = va_arg(list, char *);
      int len = strlen(str);
      if (precision >= 0 && len > precision) {
        len = precision;
      }
      for (int j = 0; j < len; j++) {
        buffer[printed++] = str[j];
      }
      break;
    }
    case 'd': {
      int val = va_arg(list, int);
      if (flags & FLAG_LEFT_JUSTIFY) {
        while (printed < width) {
          buffer[printed++] = ' ';
        }
      }
      if (flags & FLAG_SIGN) {
        if (val < 0) {
          buffer[printed++] = '-';
          val = -val;
        }
      }
      if (size & SIZE_H) {
        val = (short)val;
      } else if (size & SIZE_L) {
        val = (long)val;
      }
      len = snprintf(buffer + printed, BUFF_SIZE - printed, "%d", val);
      printed += len;
      break;
    }
    default: {
      return -1;
    }
  }
  return printed;
}
