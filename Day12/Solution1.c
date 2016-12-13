/* Copyright (c) 2016 Markus Uhlin */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Set to 1 for part two of the puzzle */
#define PART_TWO 0

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

    if ((fp = fopen("inputM", "r")) == NULL)
	fatal();

    return fp;
}

static bool
get_next_line_from_file(FILE *fp, char **line)
{
    const int LINE_MAX_LEN = 64;

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

static char *
get_instruction(int at_line)
{
    FILE *fp = open_puzzle_input();
    char *line = NULL;
    int i = 0;

    while (get_next_line_from_file(fp, &line)) {
	/* trim the newline */
	line[strcspn(line, "\n")] = '\0';

	if (i++ == at_line) {
	    fclose(fp);
	    return (line);
	}
    }

    fclose(fp);
    free(line);
    return (NULL);
}

static inline int
get_value(char src, int a, int b, int c, int d)
{
    switch (src) {
    case 'a':
	return a;
    case 'b':
	return b;
    case 'c':
	return c;
    case 'd':
	return d;
    default:
	fatal();
    }

    fatal();
    return 0;
}

int
main()
{
    char *line = NULL;
    int position = 0;
    int a, b, c, d;

    a = b = c = d = 0;

#if PART_TWO
    c = 1;
#endif

    while ((line = get_instruction(position)) != NULL) {
	if (!strncmp(line, "cpy ", 4)) {
	    int i;
	    char dest, src;

	    if (sscanf(line, "cpy %d %c", &i, &dest) == 2) {
		switch (dest) {
		case 'a': a = i; break;
		case 'b': b = i; break;
		case 'c': c = i; break;
		case 'd': d = i; break;
		default:
		    fatal();
		}
	    } else if (sscanf(line, "cpy %c %c", &src, &dest) == 2) {
		switch (dest) {
		case 'a': a = get_value(src, a, b, c, d); break;
		case 'b': b = get_value(src, a, b, c, d); break;
		case 'c': c = get_value(src, a, b, c, d); break;
		case 'd': d = get_value(src, a, b, c, d); break;
		default:
		    fatal();
		}
	    } else {
		fatal();
	    }
	} else if (!strncmp(line, "inc ", 4)) {
	    char target;

	    if (sscanf(line, "inc %c", &target) != 1)
		fatal();

	    switch (target) {
	    case 'a': a++; break;
	    case 'b': b++; break;
	    case 'c': c++; break;
	    case 'd': d++; break;
	    default:
		fatal();
	    }
	} else if (!strncmp(line, "dec ", 4)) {
	    char target;

	    if (sscanf(line, "dec %c", &target) != 1)
		fatal();

	    switch (target) {
	    case 'a': a--; break;
	    case 'b': b--; break;
	    case 'c': c--; break;
	    case 'd': d--; break;
	    default:
		fatal();
	    }
	} else if (!strncmp(line, "jnz ", 4)) {
	    int i;
	    int jump;
	    char var;

	    if (sscanf(line, "jnz %d %d", &i, &jump) == 2) {
		if (i != 0) {
		    if (jump < 0)
			position -= abs(jump);
		    else
			position += jump;
		    free(line);
		    line = NULL;
		    continue;
		}
	    } else if (sscanf(line, "jnz %c %d", &var, &jump) == 2) {
		if (get_value(var, a, b, c, d) != 0) {
		    if (jump < 0)
			position -= abs(jump);
		    else
			position += jump;
		    free(line);
		    line = NULL;
		    continue;
		}
	    } else {
		fatal();
	    }
	} else {
	    fatal();
	}

	free(line);
	line = NULL;
	position++;
    }

    printf("a = %d\n", a);
    return 0;
}
