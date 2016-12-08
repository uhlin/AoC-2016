#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int
main()
{
    FILE	*fp			       = open_puzzle_input();
    char	*line			       = NULL;
    char	*cp			       = NULL;
    bool	 inside_square_brackets	       = false;
    bool	 abba_within_hypernet_sequence = false;
    bool	 ip_has_abba		       = false;
    size_t	 number_of_ips		       = 0;

    while (get_next_line_from_file(fp, &line)) {
	/* trim the newline */
	line[strcspn(line, "\n")] = '\0';
	cp = &line[0];

	inside_square_brackets	      = false;
	abba_within_hypernet_sequence = false;
	ip_has_abba		      = false;

	while (*cp) {
	    char val1 = 127;
	    char val2 = 127;
	    char val3 = 127;
	    char val4 = 127;

	    if (*cp == '[') {
		inside_square_brackets = true;
		cp++;
		continue;
	    } else if (*cp == ']') {
		inside_square_brackets = false;
		cp++;
		continue;
	    } else {
		;
	    }

	    if (val1 = *cp, !val1)
		break;
	    else if (val2 = *(cp + 1), !val2)
		break;
	    else if (val3 = *(cp + 2), !val3)
		break;
	    else if (val4 = *(cp + 3), !val4)
		break;
	    else {
		/* empty */;
	    }

	    if (val1 == 127 || val2 == 127 || val3 == 127 || val4 == 127)
		break;
	    else if (val1 == val2 && val2 == val3 && val3 == val4) {
		cp += 4;
		continue;
	    } else if (val2 == '[') {
		inside_square_brackets = true;
		cp += 2;
		continue;
	    } else if (val2 == ']') {
		inside_square_brackets = false;
		cp += 2;
		continue;
	    } else if (val3 == '[') {
		inside_square_brackets = true;
		cp += 3;
		continue;
	    } else if (val3 == ']') {
		inside_square_brackets = false;
		cp += 3;
		continue;
	    } else if (val4 == '[') {
		inside_square_brackets = true;
		cp += 4;
		continue;
	    } else if (val4 == ']') {
		inside_square_brackets = false;
		cp += 4;
		continue;
	    } else if (val1 == val4 && val2 == val3) {
		if (inside_square_brackets)
		    abba_within_hypernet_sequence = true;
		else
		    ip_has_abba = true;
		cp += 4;
		continue;
	    } else {
		cp++;
	    }
	} /* while (*cp) */

	if (!abba_within_hypernet_sequence && ip_has_abba)
	    number_of_ips++;
    } /* while (get_next_line_from_file(...)) */

    printf("Number of IPs that supports TLS: %zu\n", number_of_ips);

    fclose(fp);
    free(line);
    return 0;
}
