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

static int
cmp(const void *a, const void *b)
{
    char val1[64] = "";
    char val2[64] = "";
    const PRANGE range1 = (const PRANGE) a;
    const PRANGE range2 = (const PRANGE) b;
    int ret = -1;

    ret = snprintf(val1, sizeof val1, "%" PRIu32 "\n", range1->start);
    if (ret == -1 || ret >= sizeof val1)
	fatal();

    ret = snprintf(val2, sizeof val2, "%" PRIu32 "\n", range2->start);
    if (ret == -1 || ret >= sizeof val2)
	fatal();

    if (strlen(val1) > strlen(val2))
	ret = 1;
    else if (strlen(val1) < strlen(val2))
	ret = -1;
    else
	ret = strcmp(val1, val2);

    return ret;
}

static void
output_ranges(const size_t max_ips, const size_t ar_memb)
{
    PRANGE element = NULL;

    if (max_ips > ar_memb)
	fatal();

    for (element = &ranges[0]; element < &ranges[max_ips]; element++)
	printf("%" PRIu32 "-" "%" PRIu32 "\n", element->start, element->end);
}

int
main()
{
    size_t ar_memb = 0;
    PRANGE element = NULL;
    uint32_t ip = 0;

    ranges_init(&ar_memb);
    qsort(&ranges[0], ar_memb, sizeof (PRANGE), cmp);

    if (false) {
	output_ranges(ar_memb, ar_memb);
	exit(1);
    }

    for (element = &ranges[0]; element < &ranges[ar_memb]; element++) {
	if (ip < element->start)
	    continue;
	ip = element->end + 1;
    }

    printf("%" PRIu32 "\n", ip);
    return (0);
}
