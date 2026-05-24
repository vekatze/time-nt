# time

`time` is a Neut module to perform time-related operations.

## Installation

```sh
neut get time https://github.com/vekatze/time-nt/raw/main/archive/0-4-59.tar.zst
```

## Types

### Main Definitions

```neut
// A UNIX timestamp.
data time {
| Time(
    seconds: int,
    nanoseconds: int,
  )
}

// A timestamp with timezone.
data clock {
| Clock(
    nanoseconds: int,
    seconds: int,
    minutes: int,
    hours: int,
    day: int,
    month: int,
    year: int,
    weekday: int,
    yearday: int,
    is-dst: bool,
    gmt-offset: int,
    timezone: string,
  )
}

// Gets the current time.
define get-time() -> time

// Gets the current local time in ISO8601 string format.
define now() -> string
```

### Converters

```neut
// time => local clock. Uses localtime(3) internally.
define to-local-clock(t: time) -> clock

// time => UTC clock (i.e. gmt-offset == 0). Uses gmtime(3) internally.
define to-UTC-clock(t: time) -> clock

// clock => local time. The timezone info in the `clock` is ignored.
// Essentially the same as mktime(3).
define from-local-clock(t: clock) -> time

// clock => UTC time. The timezone info in the `clock` is ignored.
// Essentially the same as timegm(3).
define from-UTC-clock(t: clock) -> time

// Converts a UNIX timestamp into a human-readable string in the ISO8601 format.
// The resulting string is a local one such as "2024-05-27T11:11:40.553393+09:00".
define to-ISO8601-local(ts: time, nanosecond-digits: int) -> string

// Converts a UNIX timestamp into a human-readable string in the ISO8601 format.
// The resulting string is a UTC one such as "1973-11-29T20:33:54.000056Z".
define to-ISO8601-UTC(ts: time, nanosecond-digits: int) -> string

// Parses a string in the ISO8601 format into a UNIX timestamp.
define from-ISO8601(datetime-string: &string) -> ?time

// Converts a UNIX timestamp into a string such as "1728478571.524727".
define show-time(m: time, decimals: int) -> string
```

### Numeric Operations

```neut
// Adds a time to another time.
define add-time(m1: time, m2: time) -> time

// Subtracts a time from another time.
define sub-time(m1: time, m2: time) -> time

// Compares two times.
define eq-time(m1: &time, m2: &time) -> bool
define lt-time(m1: &time, m2: &time) -> bool
define le-time(m1: &time, m2: &time) -> bool
define gt-time(m1: &time, m2: &time) -> bool
define ge-time(m1: &time, m2: &time) -> bool
```
