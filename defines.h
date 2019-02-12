#pragma once

// size of hash table as a prime number
static const size_t tableSize = 250007;
#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 86969 /* yet another prime */
#define FIRSTH 37 /* also prime */

// Macros to safe delete objects and arrays
#define SAFE_DELETE(p)                                                         \
  {                                                                            \
    if (p) {                                                                   \
      delete p;                                                                \
      p = 0;                                                                   \
    }                                                                          \
  }

#define SAFE_DELETEA(p)                                                        \
  {                                                                         \
    if (p) {                                                                   \
      delete[] p;                                                              \
      p = 0;                                                                   \
    }                                                                          \
  }