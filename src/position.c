#include "position.h"

// given a rank and file, return the associated square on the board
int file_rank_to_square(int file, int rank)
{
	return ((NUM_RANKS * rank) + file);
}
