#ifndef YOUTUBE_UI_H
#define YOUTUBE_UI_H

#include "ops/youtube_ops.h"
#include <stdbool.h>

extern int chosen_youtube_result_row;

int display_youtube_search(int row, int col, int max_list_size, int *chosen_row);

#endif
