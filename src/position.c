// file: position.c

#include "position.h"
#include "string.h"
#include "bitboard.h"
#include "hashkeys.h"

static char print_pieces[NUMBER_OF_PIECES] = {'.', 'P','N','B','R','Q','K','p','n','b','r','q','k'};
static char print_castling_rights[4] = {'K', 'Q', 'k', 'q'};
static char print_file[NUM_FILES] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
static char print_rank[NUM_RANKS] = {'1', '2', '3', '4', '5', '6', '7', '8'};

void reset_position(struct POSITION* pos)
{
	memset(pos->move_history, 0, sizeof(struct UNDO) * MAX_NUMBER_OF_MOVES);
	
	pos->position_key = 0ULL;
	
	pos->pawns_bb = 0ULL;
	pos->knights_bb = 0ULL;
	pos->bishops_bb = 0ULL;
	pos->rooks_bb = 0ULL;
	pos->queens_bb = 0ULL;
	pos->kings_bb = 0ULL;
	pos->white_pieces_bb = 0ULL;
	pos->black_pieces_bb = 0ULL;
	
	pos->ply = 0ULL;
	pos->history_ply = 0ULL;
	
	pos->piece_counts[EMPTY] = NUMBER_OF_BOARD_SQUARES;
	
	for(int piece = WHITE_PAWN; piece <= BLACK_KING; piece++)
	{
		pos->piece_counts[piece] = 0ULL;
	}
	
	pos->side_to_move = BOTH;
	pos->en_passant_square = NO_SQ;
	pos->fifty_move_rule = 0ULL;
	pos->castling_rights = 0ULL;
	
	for(int sq = 0; sq < NUMBER_OF_BOARD_SQUARES; sq++)
	{
		pos->board_mb[sq] = EMPTY;
	}
}

void _fen_add_piece_helper(struct POSITION* pos, int piece, int sq)
{
	uint64_t* piece_bb_ptr;
	uint64_t* color_bb_ptr;
	switch(piece)
	{
		case WHITE_PAWN:
			piece_bb_ptr = &pos->pawns_bb;
			color_bb_ptr = &pos->white_pieces_bb;
			break;
		case WHITE_KNIGHT:
			piece_bb_ptr = &pos->knights_bb;
			color_bb_ptr = &pos->white_pieces_bb;
			break;
		case WHITE_BISHOP:
			piece_bb_ptr = &pos->bishops_bb;
			color_bb_ptr = &pos->white_pieces_bb;
			break;
		case WHITE_ROOK:
			piece_bb_ptr = &pos->rooks_bb;
			color_bb_ptr = &pos->white_pieces_bb;
			break;
		case WHITE_QUEEN:
			piece_bb_ptr = &pos->queens_bb;
			color_bb_ptr = &pos->white_pieces_bb;
			break;
		case WHITE_KING:
			piece_bb_ptr = &pos->kings_bb;
			color_bb_ptr = &pos->white_pieces_bb;
			break;
		case BLACK_PAWN:
			piece_bb_ptr = &pos->pawns_bb;
			color_bb_ptr = &pos->black_pieces_bb;
			break;
		case BLACK_KNIGHT:
			piece_bb_ptr = &pos->knights_bb;
			color_bb_ptr = &pos->black_pieces_bb;
			break;
		case BLACK_BISHOP:
			piece_bb_ptr = &pos->bishops_bb;
			color_bb_ptr = &pos->black_pieces_bb;
			break;
		case BLACK_ROOK:
			piece_bb_ptr = &pos->rooks_bb;
			color_bb_ptr = &pos->black_pieces_bb;
			break;
		case BLACK_QUEEN:
			piece_bb_ptr = &pos->queens_bb;
			color_bb_ptr = &pos->black_pieces_bb;
			break;
		case BLACK_KING:
			piece_bb_ptr = &pos->kings_bb;
			color_bb_ptr = &pos->black_pieces_bb;
			break;
	}
	
	pos->board_mb[sq] = piece;
	pos->piece_counts[piece]++;
	pos->piece_counts[EMPTY]--;
	SET_SQUARE(*piece_bb_ptr, sq);
	SET_SQUARE(*color_bb_ptr, sq);
}

int parse_fen(struct POSITION* pos, const char* fen)
{
	int file = FILE_A;
	int rank = RANK_8;
	int en_passant_file;
	int en_passant_rank;
	int ply;
	char temp_fifty_move_rule[2];
	reset_position(pos);
	
	/* --- Pieces --- */
	while(*fen != ' ')
	{
		switch((char)*fen)
		{
			case '/':
				rank--;
				file = FILE_A;
				break;
			case 'p': 
				_fen_add_piece_helper(pos, BLACK_PAWN, FILE_RANK_TO_SQUARE(file, rank));
				file++;
				break;
			case 'n': 
				_fen_add_piece_helper(pos, BLACK_KNIGHT, FILE_RANK_TO_SQUARE(file, rank));
				file++;
				break;
			case 'b': 
				_fen_add_piece_helper(pos, BLACK_BISHOP, FILE_RANK_TO_SQUARE(file, rank));
				file++;
				break;
			case 'r': 
				_fen_add_piece_helper(pos, BLACK_ROOK, FILE_RANK_TO_SQUARE(file, rank));
				file++;
				break;
			case 'q': 
				_fen_add_piece_helper(pos, BLACK_QUEEN, FILE_RANK_TO_SQUARE(file, rank));
				file++;
				break;
			case 'k': 
				_fen_add_piece_helper(pos, BLACK_KING, FILE_RANK_TO_SQUARE(file, rank));
				file++;
				break;
			case 'P': 
				_fen_add_piece_helper(pos, WHITE_PAWN, FILE_RANK_TO_SQUARE(file, rank));
				file++;
				break;
			case 'N': 
				_fen_add_piece_helper(pos, WHITE_KNIGHT, FILE_RANK_TO_SQUARE(file, rank));
				file++;
				break;
			case 'B': 
				_fen_add_piece_helper(pos, WHITE_BISHOP, FILE_RANK_TO_SQUARE(file, rank));
				file++;
				break;
			case 'R': 
				_fen_add_piece_helper(pos, WHITE_ROOK, FILE_RANK_TO_SQUARE(file, rank));
				file++;
				break;
			case 'Q': 
				_fen_add_piece_helper(pos, WHITE_QUEEN, FILE_RANK_TO_SQUARE(file, rank));
				file++;
				break;
			case 'K': 
				_fen_add_piece_helper(pos, WHITE_KING, FILE_RANK_TO_SQUARE(file, rank));
				file++;
				break;
			case '8':
			case '7':
			case '6':
			case '5':
			case '4':
			case '3':
			case '2':
			case '1':
				file += (*fen - '0'); // skip empty squares
				break;
			default:
				printf("%c\n", *fen);
				printf("PARSING FEN ERROR\n");
				return -1;
		}
		fen++;
	}
	
	fen++; // move past space
	ASSERT( (*fen == 'w') || (*fen == 'b') );
	
	/* --- Side to Move --- */
	
	if(*fen == 'w')
	{
		pos->side_to_move = WHITE;
	}
	else if(*fen == 'b')
	{
		pos->side_to_move = BLACK;
	}
	
	ASSERT(pos->side_to_move != BOTH);
	
	fen+= 2; // move past side to move and space
	
	/* --- Castling Rights --- */
	for(int i = 0; i < 4; i++)
	{
		switch(*fen)
		{
			case 'k':
				pos->castling_rights |= BLACK_KINGSIDE_CASTLING_RIGHTS_MASK;
				break;
			case 'q':
				pos->castling_rights |= BLACK_QUEENSIDE_CASTLING_RIGHTS_MASK;
				break;
			case 'K':
				pos->castling_rights |= WHITE_KINGSIDE_CASTLING_RIGHTS_MASK;
				break;
			case 'Q':
				pos->castling_rights |= WHITE_QUEENSIDE_CASTLING_RIGHTS_MASK;
				break;
				
		}
		
		fen++;
	}
	
	fen++; // move past space
	
	/* --- En Passant Square --- */
	if(*fen == '-')
	{
		pos->en_passant_square = NO_SQ;
		fen+=2;
	}
	else
	{
		en_passant_file = fen[0] - 'a';
		en_passant_rank = fen[1] - '1';
		
		ASSERT((en_passant_file >= FILE_A) && (en_passant_file <= FILE_H));
		ASSERT((en_passant_rank >= RANK_1) && (en_passant_rank <= RANK_8));

		pos->en_passant_square = FILE_RANK_TO_SQUARE((en_passant_file), (en_passant_rank));
		fen+=3;
	}
	
	/* --- Fifty-Move Rule --- */
	temp_fifty_move_rule[0] = fen[0];
	temp_fifty_move_rule[1] = fen[1];
	if(temp_fifty_move_rule[1] != ' ')
	{
		pos->fifty_move_rule = atoi(temp_fifty_move_rule);
		fen+=3;
	}
	else
	{
		pos->fifty_move_rule = temp_fifty_move_rule[0] - '0';
		fen+=2;
	}
	
	/* --- Number of Full Moves --- */
	ply = 2 * (atoi(fen) - 1);
	if(pos->side_to_move == BLACK)
	{
		ply++;
	}
	pos->history_ply = ply;
	ASSERT(pos->history_ply >= 0);
	
	pos->position_key = generate_position_key(pos);
	ASSERT(pos->position_key != 0ULL);
	
	return 0;
}

void print_position(const struct POSITION* pos)
{
	int square;
	
	printf("\nPOSITION KEY: %" PRIu64 "\n", pos->position_key);
	for(int rank = RANK_8; rank >= RANK_1; rank--)
	{
		printf("%d ", rank + 1);
		for(int file = FILE_A; file <= FILE_H; file++)
		{
			square = FILE_RANK_TO_SQUARE(file, rank);
			printf("%3c", print_pieces[pos->board_mb[square]]);
		}
		printf("\n");
	}
	
	printf("\n  ");
	for(int file = FILE_A; file <= FILE_H; file++)
	{
		printf("%3c", 'A' + file);
	}
	printf("\n\n");
	
	
	printf("SIDE TO MOVE: ");
	if(pos->side_to_move == WHITE)
	{
		printf("WHITE\n");
	}
	else
	{
		printf("BLACK\n");
	}
	
	printf("CASTLING RIGHTS: ");
	for(int i = 0; i < 4; i++)
	{
		if(pos->castling_rights & (1ULL << i))
		{
			printf("%c", print_castling_rights[i]);
		}
		else
		{
			printf("-");
		}
	}
	printf("\n");
	
	printf("EN PASSANT SQUARE: ");
	if(pos->en_passant_square != NO_SQ)
	{
		int temp_rank = pos->en_passant_square / NUM_RANKS;
		int temp_file = pos->en_passant_square - (temp_rank * NUM_RANKS);
		printf("%c%c\n", print_file[temp_file], print_rank[temp_rank]);
	}
	else
	{
		printf("-\n");
	}
	
	printf("FIFTY-MOVE RULE (PLY): %d\n", pos->fifty_move_rule);
	
	printf("NUMBER OF HALF-MOVES PLAYED (PLY): %d\n", pos->history_ply);
} 
