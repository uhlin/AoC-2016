#ifndef SOL1_H
#define SOL1_H

typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} cardinal_direction_t;

typedef enum {
    LEFT,
    RIGHT
} direction_t;

struct move {
    direction_t dir;
    int walk_forward_blocks;
};

#endif
