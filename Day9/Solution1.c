#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define MAXLINE 20000

/* the puzzle input are read into this buffer */
static char puzzle_input[MAXLINE] = "";

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

int
main()
{
    FILE	*fp	    = open_puzzle_input();
    const char	*cp	    = &puzzle_input[0];
    size_t	 decomp_len = 0;

    /* this puzzle input only contains one line */
    if (fgets(puzzle_input, sizeof puzzle_input, fp) == NULL)
	fatal();
    fclose(fp);

    /* trim the newline */
    puzzle_input[strcspn(puzzle_input, "\n")] = '\0';

    while (*cp) {
	size_t length, times;

	if (*cp == '(') {
	    if (sscanf(++cp, "%zux%zu", &length, &times) != 2)
		fatal();
	    while (*cp != ')')
		cp++;
	    if (*cp == ')')
		cp++;
	    cp += length;
	    decomp_len += (length * times);
	} else {
	    decomp_len++, cp++;
	}
    }

    printf("decompressed length: %zu\n", decomp_len);

    return 0;
}
