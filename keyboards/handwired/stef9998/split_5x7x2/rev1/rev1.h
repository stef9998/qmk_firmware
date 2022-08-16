#pragma once

#include "split_5x7x2.h"

#include "quantum.h"

#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
  #include <avr/io.h>
  #include <avr/interrupt.h>
#endif
#endif

#define LAYOUT( \
  k00, k01, k02, k03, k04, k05, k06,                k07, k08, k09, k10, k11, k12, k13, \
  k14, k15, k16, k17, k18, k19, k20,                k21, k22, k23, k24, k25, k26, k27, \
  k28, k29, k30, k31, k32, k33, k34,                k35, k36, k37, k38, k39, k40, k41, \
  k42, k43, k44, k45, k46, k47, k48,                k49, k50, k51, k52, k53, k54, k55, \
  k56, k57, k58, k59,      k61, k62,                k63, k64,      k66, k67, k68, k69  \
) \
{ \
    { k00, k01, k02, k03, k04  , k05, k06 }, \
    { k14, k15, k16, k17, k18  , k19, k20 }, \
    { k28, k29, k30, k31, k32  , k33, k34 }, \
    { k42, k43, k44, k45, k46  , k47, k48 }, \
    { k56, k57, k58, k59, KC_NO, k61, k62 }, \
    { k13, k12, k11, k10, k09  , k08, k07 }, \
    { k27, k26, k25, k24, k23  , k22, k21 }, \
    { k41, k40, k39, k38, k37  , k36, k35 }, \
    { k55, k54, k53, k52, k51  , k50, k49 }, \
    { k69, k68, k67, k66, KC_NO, k64, k63 }  \
}
