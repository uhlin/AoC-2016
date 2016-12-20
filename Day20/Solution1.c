#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RANGEMAX 1080

typedef struct tagRANGE {
    uint32_t start;
    uint32_t end;
} RANGE, *PRANGE;

static RANGE ranges[RANGEMAX];

static const uint32_t UPPER_BOUND = 4294967295;

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
    const int LINE_MAX_LEN = 512;

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
ranges_init(size_t *ar_memb)
{
    FILE *fp = open_puzzle_input();
    char *line = NULL;
    PRANGE element = &ranges[0];

    while (get_next_line_from_file(fp, &line)) {
	uint32_t start, end;

	if (sscanf(line, "%" SCNu32 "-" "%" SCNu32, &start, &end) != 2) {
	    fatal();
	} else if (element < &ranges[RANGEMAX]) {
	    element->start = start;
	    element->end = end;
	    element++;
	    (*ar_memb)++;
	} else {
	    fatal();
	}
    }

    fclose(fp);
    free(line);
}

static inline bool
is_blacklisted(uint32_t ip, size_t ar_memb)
{
    PRANGE element = NULL;

    for (element = &ranges[0]; element < &ranges[ar_memb]; element++) {
	if (ip >= element->start && ip <= element->end)
	    return (true);
    }

    return (false);
}

int
main()
{
    size_t ar_memb = 0;
    uint32_t ip = 0;

    ranges_init(&ar_memb);
    puts("please stand by. processing...");

    while (ip < UPPER_BOUND) {
	if (!is_blacklisted(ip, ar_memb)) {
	    printf("answer: " "%" PRIu32 "\n", ip);
	    break;
	}

	ip++;
    }

    return (0);
}
