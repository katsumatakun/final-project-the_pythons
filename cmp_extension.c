#include <string.h>
#include "cmp_extension.h"

int contain(char *word, char *words){
  char *s = words;
  int pos = strlen(s) - strlen(word) - 1;
  if (pos >= 0 && strcmp(&s[pos], word) == 0)
  {
    return 0;
  }
  return -1;
}
