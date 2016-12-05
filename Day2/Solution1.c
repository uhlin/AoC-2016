#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int position = 5;

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

static bool
get_next_line_from_file(FILE *fp, char **line)
{
    const int LINE_MAX_LEN = 4096;

    if (fp == NULL || line == NULL)
	fatal();

    if (*line) {
	free(*line);
	*line = NULL;
    }

    if ((*line = malloc(LINE_MAX_LEN)) == NULL)
	fatal();

    return (fgets(*line, LINE_MAX_LEN, fp) ? true : false);
}

static void
move_up(int pos)
{
    if (pos == 1 || pos == 2 || pos == 3) {
	return;
    } else if (pos == 4) {
	position = 1;
    } else if (pos == 5) {
	position = 2;
    } else if (pos == 6) {
	position = 3;
    } else if (pos == 7) {
	position = 4;
    } else if (pos == 8) {
	position = 5;
    } else if (pos == 9) {
	position = 6;
    } else {
	assert(false);
    }
}

static void
move_down(int pos)
{
    if (pos == 7 || pos == 8 || pos == 9) {
	return;
    } else if (pos == 1) {
	position = 4;
    } else if (pos == 2) {
	position = 5;
    } else if (pos == 3) {
	position = 6;
    } else if (pos == 4) {
	position = 7;
    } else if (pos == 5) {
	position = 8;
    } else if (pos == 6) {
	position = 9;
    } else {
	assert(false);
    }
}

static void
move_left(int pos)
{
    if (pos == 1 || pos == 4 || pos == 7) {
	return;
    } else if (pos == 2) {
	position = 1;
    } else if (pos == 5) {
	position = 4;
    } else if (pos == 8) {
	position = 7;
    } else if (pos == 3) {
	position = 2;
    } else if (pos == 6) {
	position = 5;
    } else if (pos == 9) {
	position = 8;
    } else {
	assert(false);
    }
}

static void
move_right(int pos)
{
    if (pos == 3 || pos == 6 || pos == 9) {
	return;
    } else if (pos == 2) {
	position = 3;
    } else if (pos == 5) {
	position = 6;
    } else if (pos == 8) {
	position = 9;
    } else if (pos == 1) {
	position = 2;
    } else if (pos == 4) {
	position = 5;
    } else if (pos == 7) {
	position = 8;
    } else {
	assert(false);
    }
}

static void
move_to_new_pos(int pos, char move)
{
    switch (move) {
    case 'U':
	move_up(pos);
	return;
    case 'D':
	move_down(pos);
	return;
    case 'L':
	move_left(pos);
	return;
    case 'R':
	move_right(pos);
    }
}

int
main()
{
    FILE *fp = open_puzzle_input();
    char *line = NULL;
    char *cp = NULL;

    printf("answer: ");

    while (get_next_line_from_file(fp, &line)) {
	/* trim the newline */
	line[strcspn(line, "\n")] = '\0';

	for (cp = line; *cp; cp++) {
	    if (*cp != 'U' && *cp != 'D' && *cp != 'L' && *cp != 'R')
		fatal();
	    move_to_new_pos(position, *cp);
	}

	printf("%d", position);
    }

    putchar('\n');

    fclose(fp);
    free(line);
    return 0;
}
