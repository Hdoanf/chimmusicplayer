#include "youtube_ui.h"
#include "search_ui.h"
#include "common/appstate.h"
#include "common/common.h"
#include "common_ui.h"
#include "utils/term.h"
#include "utils/utils.h"
#include <stdio.h>

int chosen_youtube_result_row = 0;

int display_youtube_search_results(int row, int col, int max_list_size, int *chosen_row) {
    YoutubeSearchState search_state = youtube_get_search_state();
    
    if (search_state == YT_SEARCH_RUNNING) {
        printf("\033[%d;%dH   Searching YouTube...", row, col);
        clear_rest_of_line();
        return 0;
    }

    if (search_state == YT_SEARCH_ERROR) {
        printf("\033[%d;%dH   No results found or network error", row, col);
        clear_rest_of_line();
        return 0;
    }

    int count = get_youtube_results_count();
    if (count == 0) return 0;

    if (*chosen_row < 0) *chosen_row = 0;
    if (*chosen_row >= count) *chosen_row = count - 1;

    for (int i = 0; i < count && i < max_list_size; i++) {
        YoutubeResult *res = get_youtube_result(i);
        if (!res) continue;

        printf("\033[%d;%dH", row + i, col);
        if (i == *chosen_row) {
            inverse_text();
            printf(" > [%s] %s ", res->duration, res->title);
            reset_color();
        } else {
            printf("   [%s] %s ", res->duration, res->title);
        }
        clear_rest_of_line();
    }
    return 0;
}

int display_youtube_search(int row, int col, int max_list_size, int *chosen_row) {
    if (youtube_get_search_state() == YT_SEARCH_RUNNING) {
        trigger_refresh();
    }
    display_search_box(row, col);
    display_youtube_search_results(row + 2, col, max_list_size, chosen_row);
    return 0;
}
