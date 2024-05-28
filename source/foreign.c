#include <stdio.h>
#include <string.h>
#include <time.h>

int neut_time_v0_4_parse_iso8601(const char *datetime_str, struct timespec *ts) {
  struct tm tm = {0};
  char *rest = strptime(datetime_str, "%Y-%m-%dT%H:%M:%S", &tm);
  if (rest == NULL) {
    return -1;
  }
  int fraction = 0;
  int offset;
  if (sscanf(rest, ".%d%n", &fraction, &offset) == 1) {
    rest += offset;
    if (fraction < 0 || 1000000000 <= fraction) {
      return -1;
    }
    while (fraction * 10 < 1000000000) {
      fraction *= 10;
    }
  }
  if (strcmp(rest, "Z") == 0) {
    ts->tv_sec = timegm(&tm);
    ts->tv_nsec = fraction;
    return 0;
  } else {
    int gmtoff_sign = 1;
    char sign;
    if (sscanf(rest, "%c", &sign) == 1) {
      rest += 1;
      if (sign == '+') {
        gmtoff_sign = 1;
      } else if (sign == '-') {
        gmtoff_sign = -1;
      } else {
        return -1;
      }
    } else {
      return -1;
    }
    struct tm mini_tm = {0};
    char *trail = NULL;
    trail = trail ?: strptime(rest, "%H:%M", &mini_tm);
    trail = trail ?: strptime(rest, "%H%M", &mini_tm);
    trail = trail ?: strptime(rest, "%H", &mini_tm);
    int gmtoff_absmin = 0;
    if (trail == NULL || strcmp(trail, "") != 0) {
      return -1;
    } else {
      gmtoff_absmin = mini_tm.tm_hour * 60 + mini_tm.tm_min;
    }
    int gmtoff_sec = gmtoff_sign * gmtoff_absmin * 60;
    ts->tv_sec = timegm(&tm) - gmtoff_sec;
    ts->tv_nsec = fraction;
    return 0;
  }
}
