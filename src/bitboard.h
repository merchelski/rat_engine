#ifndef BITBOARD_H
#define BITBOARD_H

// needed for -mbmi2 intrinstic functions
#include <immintrin.h>

// requires gcc compiler
// counts the number of 1s set in a bitboard
#define POPCNT(bb) __builtin_popcountll((bb))

// -mbmi2 function (parallel extract bits)
#define PEXT(bb1, bb2) _pext_u64((bb1), (bb2))

/* FUNCTIONS START */
void print_bitboard(uint64_t bitboard);
/* FUNCTIONS END */

#endif
