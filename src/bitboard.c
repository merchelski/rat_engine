#include <stdio.h>
#include <stdint.h>

#include "bitboard.h"
#include "position.h"

void print_bitboard(uint64_t bitboard)
{
	uint64_t cursor = 1ULL;
	int square;
	
	printf("\n");
	for(int rank = RANK_8; rank >= RANK_1; rank--)
	{
		for(int file = FILE_A; file <= FILE_H; file++)
		{
			square = FILE_RANK_TO_SQUARE(file, rank);
			(bitboard & (cursor << square)) ? printf("X") : printf("-");
		}
		printf("\n");
	}
}

int count_1s(uint64_t bitboard) 
{
	int r;
	for(r = 0; bitboard; r++, bitboard &= bitboard - 1);
	return r;
}


