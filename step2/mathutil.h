#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <stdint.h>

uint8_t wrap_add(uint8_t a, uint8_t b){
  return a + b;
}

int clamp(int value, int lo, int hi){
  if (value < lo) return lo;
  if (value > hi) return hi;
  return value;
}

#endif