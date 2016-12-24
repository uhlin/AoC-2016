#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* safety for memcpy() and memmove() */
static const size_t EXTRA_SIZE = 10;

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
    const int LINE_MAX_LEN = 1024;

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
swap(char *s, int i, int j)
{
    char temp;

    temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

/* K&R */
static void
reverse(char *s)
{
    char c;
    int i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
	c = s[i];
	s[i] = s[j];
	s[j] = c;
    }
}

/*
 * swap position I with position J
 */
static void
swap_position(char *data, int i, int j)
{
    swap(data, i, j);
}

/*
 * swap letter A with letter B
 */
static void
swap_letter(char *data, char a, char b)
{
    char str1[] = { a, 0 };
    char str2[] = { b, 0 };

    if (!strchr(data, a) || !strchr(data, b))
	fatal();
    swap(data, strcspn(data, str1), strcspn(data, str2));
}

/*
 * rotate left X steps
 */
static void
rotate_left(char *data, int steps)
{
    char temp;
    int i;

    for (i = 0; i < steps; i++) {
	const size_t index = strlen(data) - 1;

	temp = data[0];
	memmove(data, data + 1, strlen(data + 1));
	data[index] = temp;
    }
}

/*
 * rotate right X steps
 */
static void
rotate_right(char *data, int steps)
{
    char temp;
    int i;

    for (i = 0; i < steps; i++) {
	temp = data[strlen(data) - 1];
	memmove(data + 1, data, strlen(data) - 1);
	data[0] = temp;
    }
}

/*
 * rotate based on position of letter X
 */
static void
rotate_based_on_position(char *data, char a)
{
    char s[] = { a, 0 };

    if (!strchr(data, a))
	fatal();
    const size_t index = strcspn(data, s);
    rotate_right(data, 1);
    rotate_right(data, index);
    if (index >= 4)
	rotate_right(data, 1);
}

/*
 * reverse positions I through J
 */
static void
reverse_positions(char *data, int i, int j)
{
    char *buf;
    int diff;

    if (i < 0 || j > strlen(data) || i > j)
	fatal();
    if ((diff = j - i) == 0)
	return;
    if ((buf = calloc(diff + EXTRA_SIZE, 1)) == NULL)
	fatal();
    memcpy(buf, &data[i], diff + 1);
    reverse(buf);
    memcpy(&data[i], buf, diff + 1);
    free(buf);
}

/*
 * move position I to position J
 */
static void
move_position(char *data, int i, int j)
{
    char temp;
    size_t data_length;
    size_t index;

    data_length = strlen(data);
    temp = data[i];
    data[i] = 'X';
    memmove(&data[j + 1], &data[j], strlen(&data[j]));
    index = strcspn(data, "X");
    memmove(&data[index], &data[index + 1], strlen(&data[index + 1]));
    data[data_length] = '\0';
    data[j] = temp;
}

int
main()
{
    FILE *fp = open_puzzle_input();
    char *data = NULL;
    char *line = NULL;
    const char *start_data = "abcdefgh";

    if ((data = calloc(strlen(start_data) + EXTRA_SIZE, 1)) == NULL)
	fatal();
    strcpy(data, start_data);

    while (get_next_line_from_file(fp, &line)) {
	char a, b;
	int i, j;

	/* trim the newline */
	line[strcspn(line, "\n")] = '\0';

	if (*line == '#') /*ignore lines with leading hashtag (for debugging)*/
	    continue;
	else if (sscanf(line, "swap position %d with position %d", &i, &j) == 2)
	    swap_position(data, i, j);
	else if (sscanf(line, "swap letter %c with letter %c", &a, &b) == 2)
	    swap_letter(data, a, b);
	else if (sscanf(line, "rotate left %d steps", &i) == 1)
	    rotate_left(data, i);
	else if (sscanf(line, "rotate right %d steps", &i) == 1)
	    rotate_right(data, i);
	else if (sscanf(line, "rotate based on position of letter %c", &a) == 1)
	    rotate_based_on_position(data, a);
	else if (sscanf(line, "reverse positions %d through %d", &i, &j) == 2)
	    reverse_positions(data, i, j);
	else if (sscanf(line, "move position %d to position %d", &i, &j) == 2)
	    move_position(data, i, j);
	else
	    fatal();
    }

    fclose(fp);
    free(line);
    puts(data);
    free(data);
    return (0);
}
