
// file: main.c

#include <stdio.h>

#include "position.h"
#include "bitboard.h"
#include "misc.h"
#include "init.h"

int main(void)
{
	init_all();
	
	struct POSITION pos;
	
	reset_position(&pos);
	parse_fen(&pos, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	print_position(&pos);
	
	reset_position(&pos);
	parse_fen(&pos, "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
	print_position(&pos);
	
	reset_position(&pos);
	parse_fen(&pos, "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2");
	print_position(&pos);
	
	reset_position(&pos);
	parse_fen(&pos, "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2");
	print_position(&pos);
	
	return 0;
}

