/*
 * A stupid approach that relay on TOCTOU of variables with file scope
 * visibility.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Solution1.h"

/* the puzzle input are read into this buffer */
static char puzzle_input[600] = "";
static char *saveptr = "";

/* north is the starting position */
static cardinal_direction_t dir = NORTH;

static int	walk_north = 0;
static int	walk_east  = 0;
static int	walk_south = 0;
static int	walk_west  = 0;

static void
fatal()
{
    fputs("fatal error  --  program must exit!\n", stderr);
    abort();
}

static FILE *
open_puzzle_input()
{
    FILE *fp = NULL;

    if ((fp = fopen("input", "r")) == NULL)
	fatal();

    return fp;
}

static struct move *
get_next_move()
{
    char *token = NULL;
    static int initial_call = 1;
    static struct move m;

    if ((token = strtok_r(initial_call ? puzzle_input : NULL, "\x2c\x20",
			  &saveptr)) != NULL) {
	if (*token == 'L')
	    m.dir = LEFT;
	else if (*token == 'R')
	    m.dir = RIGHT;
	else
	    fatal();
	token++;
	m.walk_forward_blocks = atoi(token);
	initial_call = 0;
	return (&m);
    }

    initial_call = 0;
    return (NULL);
}

static void
handle_left_move()
{
    switch (dir) {
    case NORTH:
	dir = WEST;
	break;
    case EAST:
	dir = NORTH;
	break;
    case SOUTH:
	dir = EAST;
	break;
    case WEST:
	dir = SOUTH;
	break;
    default:
	fatal();
    }
}

static void
handle_right_move()
{
    switch (dir) {
    case NORTH:
	dir = EAST;
	break;
    case EAST:
	dir = SOUTH;
	break;
    case SOUTH:
	dir = WEST;
	break;
    case WEST:
	dir = NORTH;
	break;
    default:
	fatal();
    }
}

static void
walk(int blocks)
{
    switch (dir) {
    case NORTH:
	walk_north += blocks;
	break;
    case EAST:
	walk_east += blocks;
	break;
    case SOUTH:
	walk_south += blocks;
	break;
    case WEST:
	walk_west += blocks;
	break;
    default:
	fatal();
    }
}

static int
get_answer()
{
    int diff1 = 0;
    int diff2 = 0;

    if (walk_north > walk_south)
	diff1 = walk_north - walk_south;
    else
	diff1 = walk_south - walk_north;
    if (walk_west > walk_east)
	diff2 = walk_west - walk_east;
    else
	diff2 = walk_east - walk_west;

    return (diff1 + diff2);
}

int
main()
{
    FILE *fp = NULL;
    struct move *m_ptr = NULL;

    fp = open_puzzle_input();
    /* this puzzle input only contains one line */
    if (fgets(puzzle_input, sizeof puzzle_input, fp) == NULL)
	fatal();
    fclose(fp);

    while ((m_ptr = get_next_move()) != NULL) {
	if (m_ptr->dir == LEFT) {
	    handle_left_move();
	} else {
	    handle_right_move();
	}

	walk(m_ptr->walk_forward_blocks);
    }

    printf("Easter Bunny HQ is %d blocks away\n", get_answer());
    return 0;
}
