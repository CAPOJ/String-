#include "../s21_string.h"
#include "./strerror.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t result = 0;
  for (char *tmp = (char *)str; *tmp != '\0'; tmp++, result++) {
  }
  return result;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest + s21_strlen(dest);
  for (; n && *src != '\0'; ptr++, src++, n--) *ptr = *src;
  *ptr = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *temp = (char *)str;
  void *res = ((char)c == '\0') ? "\0" : S21_NULL;
  s21_size_t i = 0;
  while (*(temp + i) != '\0' && *(temp + i) != c) i++;
  if (*(temp + i) != '\0') res = temp + i;
  return res;
}

char *s21_strrchr(const char *str, int c) {
  const char *res = S21_NULL;
  if (str != S21_NULL) {
    while (*str != '\0') {
      if (*str == c) {
        res = str;
      }
      str++;
    }
  }
  if (*str == c) {
    res = (char *)str;
  }
  return (char *)res;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  for (; n && *str1 && (*str1 == *str2); str1++, str2++, n--) {
  }
  return !n ? 0 : (*(char *)str1 - *(char *)str2);
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) dest[i] = src[i];
  for (; i < n; i++) dest[i] = '\0';
  return dest;
}
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t result = 0;
  for (char *tmp = (char *)str1, k = 0; *tmp != '\0' && !k; tmp++)
    if (!s21_strchr(str2, *tmp))
      result++;
    else
      k = 1;
  return result;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;
  for (; *haystack != '\0' && !result; haystack++) {
    char *tmp1 = (char *)haystack, *tmp2 = (char *)needle;
    for (int isIdenty = 1; tmp1 && tmp2 && isIdenty && *haystack == *needle;) {
      if (*tmp1 != *tmp2 || *tmp1 == '\0') isIdenty = 0;
      if (isIdenty) tmp1++, tmp2++;
    }
    result = *tmp2 == '\0' ? (char *)haystack : S21_NULL;
  }
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *ptr1 = (unsigned char *)dest;
  unsigned char *ptr2 = (unsigned char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    *ptr1 = *ptr2;
    ptr1++;
    ptr2++;
  }
  return dest;
}

// s21_size_t s21_strspn_giveup(const char *haystack, const char *entries) {
//   s21_size_t result = 0;
//   s21_size_t haystack_len = s21_strlen(haystack);
//   int stop = 0;
//   for (s21_size_t i = 0; i < haystack_len && !stop; ++i) {
//     if (s21_strchr(entries, haystack[i]) != S21_NULL) {
//       ++result;
//     } else {
//       stop = 1;
//     }
//   }
//   return result;
// }

// char *s21_strtok_giveup(char *str, const char *delim) {
//   static char *tek = S21_NULL;
//   char *res = S21_NULL;
//   if (str) {
//     tek = str;
//     while (*tek && s21_strchr(delim, *tek)) tek++;
//     if (*tek) {
//       res = tek;
//       while (*tek && !s21_strchr(delim, *tek)) {
//         tek++;
//       }
//       if (*tek) {
//         *tek++ = 0;
//       }
//     } else {
//       tek = S21_NULL;
//     }
//   }
//   return res;
// }

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  const void *result = S21_NULL;
  for (s21_size_t i = 0; i < s21_strlen(str) && i < n; i++) {
    if (*ptr == (unsigned char)c) {
      result = (str + i);
      break;
    }
    ptr++;
  }
  return (void *)result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *temp1 = (unsigned char *)str1;
  unsigned char *temp2 = (unsigned char *)str2;
  for (s21_size_t i = 0; i < n; ++i) {
    if (temp1[i] != temp2[i]) {
      return temp1[i] - temp2[i];
    }
  }
  return 0;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  for (unsigned char *tmp = str; n > 0; n--, tmp++) *tmp = (unsigned char)c;
  return str;
}

char *s21_strerror(int errnum) {
  char *res = S21_NULL;
  static char error[150];
  if (errnum >= 0 || errnum < S21_ERRLIST_SIZE) {
    res = (char *)s21_sys_errlist[errnum];
  } else {
    s21_memset(res, '\0', 100);
    s21_sprintf(res, "Unknown error %d", errnum);
    res = error;
  }
  return res;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *result = S21_NULL;
  for (s21_size_t i = 0; i < s21_strlen(str1) && !result; i++) {
    for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
      if (str1[i] == str2[j]) result = (str1 + i);
    }
  }
  return (char *)result;
}

void *s21_to_upper(const char *str) {
  char *res = S21_NULL;
  if (str) {
    size_t len = s21_strlen(str);
    res = (char *)malloc(sizeof(char) * (len + 1));
    if (res) {
      for (size_t i = 0; i < len; i++)
        if (str[i] >= 'a' && str[i] <= 'z') {
          res[i] = str[i] - 32;
        } else {
          res[i] = str[i];
        }
      res[len] = '\0';
    }
  }
  return res;
}

void *s21_to_lower_giveup(const char *str) {
  char *res = S21_NULL;
  for (s21_size_t i = 0; i < s21_strlen(str); i++) {
    if (res == S21_NULL) res = (char *)str;
    if (str[i] >= 'A' && str[i] <= 'Z')
      res[i] = str[i] + 32;
    else
      res[i] = str[i];
  }
  return res;
}

void *s21_to_lower(const char *str) {
  char *res = S21_NULL;
  if (str) {
    s21_size_t len = s21_strlen(str);
    res = (char *)malloc(sizeof(char) * (len + 1));
    if (res) {
      for (s21_size_t i = 0; i < len; i++)
        if (str[i] >= 'A' && str[i] <= 'Z') {
          res[i] = str[i] + 32;
        } else {
          res[i] = str[i];
        }
      res[len] = '\0';
    }
  }
  return res;
}
char *s21_strcpy(char *dest, const char *src) {
  int slen = s21_strlen(src);
  for (int i = 0; src[i]; i++) {
    dest[i] = src[i];
  }
  dest[slen] = '\0';

  return dest;
}

void *s21_insert(const char *src, const char *str, size_t start_index) {
  char *res = NULL;
  if (src != NULL && str != NULL) {
    size_t srclen = s21_strlen(src);
    size_t strle = s21_strlen(str);
    size_t newlen = srclen + strle;
    if (start_index > srclen) {
      return NULL;
    }
    res = (char *)malloc(sizeof(char) * (newlen + 1));
    if (res) {
      size_t i = 0;
      size_t j = 0;
      while (i < start_index) {
        res[i] = src[i];
        i++;
        j++;
      }
      for (size_t k = 0; k < strle; k++) {
        res[i] = str[k];
        i++;
      }
      while (j < srclen) {
        res[i] = src[j];
        i++;
        j++;
      }
      res[newlen] = '\0';
    }
  } else if (str == NULL && src != NULL) {
    res = (char *)malloc(sizeof(char) * (s21_strlen(src) + 1));
    s21_strcpy(res, src);
  }
  return res;
}

size_t s21_strspn(const char *str1, const char *str2) {
  size_t count = 0;
  for (const char *s1 = str1; *s1; s1++) {
    int flag = 0;
    for (const char *s2 = str2; *s2; s2++) {
      if (*s1 == *s2) {
        count++;
        flag = 1;
        break;
      }
    }
    if (!flag) {
      break;
    }
  }
  return count;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (!src) {
    // Обработка случая, когда входная строка равна NULL
    return NULL;
  }
  char *res = NULL;
  if (trim_chars && trim_chars[0]) {
    int beg_offset = s21_strspn(src, trim_chars);
    int end_offset = s21_strlen(src);
    res = calloc(s21_strlen(src) + 1, sizeof(char));
    if (end_offset != beg_offset) {
      // strspn, но справа
      while (s21_end_trim(src, trim_chars, end_offset)) end_offset--;
    } else {
      res[0] = '\0';
    }
    for (int i = 0; beg_offset < end_offset && src[beg_offset] != '\0'; i++) {
      res[i] = src[beg_offset];
      beg_offset++;
    }
  } else {
    res = s21_trim(src, "\t\n ");
  }
  return res;
}

int s21_end_trim(const char *src, const char *trim_chars, int end_offset) {
  int res = 0;
  end_offset--;  // потому что адрес
  int size = s21_strlen(trim_chars);
  for (int i = 0; i < size; i++) {
    if (src[end_offset] == trim_chars[i]) res = 1;
  }
  return res;
}

char *s21_strtok(char *str, const char *delim) {
  // все обязательно статики
  static int non_delim_str;
  static size_t ind;
  static char *max_ptr;
  static char *curr;
  // активируется только в первый прогон, тк после этого вместо сроки подаётся
  // NULL
  if (str) {
    ind = 0, non_delim_str = 0;
    /////
    curr = str + s21_strspn(str, delim);
    ////
    max_ptr = str + s21_strlen(str);
  }
  char *res = NULL;
  if (curr <= max_ptr && !(non_delim_str)) {
    int non_delim = 1;  // если не зайдёт в step, то не изменится

    for (int i = 0; curr[i]; i++) {
      size_t step = s21_strspn(curr + i, delim);
      if (step) {
        non_delim = 0;
        for (size_t j = i; j < i + step; j++) curr[j] = '\0';
        ind = step + i;
        break;
      }
    }
    if (non_delim)
      non_delim_str = 1;  // обработка случая, когда в строке нет разделителей
    res = curr;
    curr += ind;
  }
  return res;
}