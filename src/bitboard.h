#ifndef BITBOARD_H
#define BITBOARD_H

// file: bitboard.h

// needed for -mbmi2 intrinstic functions
#include <immintrin.h>

#define SET_SQUARE(bb, sq) ((bb) |= (1ULL << (sq)))
#define CLEAR_SQUARE(bb, sq) ((bb) &= ~(1ULL << (sq)))
#define TOGGLE_SQUARE(bb, sq) ((bb) ^= (1ULL << (sq)))

// requires gcc compiler
// counts the number of 1s set in a bitboard
#define POPCNT(bb) __builtin_popcountll((bb))
// -mbmi2 function (parallel extract bits)
#define PEXT(bb1, bb2) _pext_u64((bb1), (bb2))


extern void print_bitboard(uint64_t bitboard);
#endif
