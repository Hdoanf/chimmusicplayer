#ifndef YOUTUBE_OPS_H
#define YOUTUBE_OPS_H

#include <stdbool.h>

typedef struct {
    char title[256];
    char video_id[32];
    char duration[16];
} YoutubeResult;

typedef enum {
    YT_SEARCH_IDLE,
    YT_SEARCH_RUNNING,
    YT_SEARCH_FINISHED,
    YT_SEARCH_ERROR
} YoutubeSearchState;

void youtube_search_start(const char *query);
YoutubeSearchState youtube_get_search_state(void);
void youtube_set_search_state(YoutubeSearchState state);
int get_youtube_results_count(void);
YoutubeResult *get_youtube_result(int index);
char *youtube_get_stream_url(const char *video_id, const char *title);
void free_youtube_results(void);
void youtube_cleanup_temp_files(void);
void youtube_clear_playlist(void);

#endif
