#include "youtube_ops.h"
#include "common/appstate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

#define MAX_YOUTUBE_RESULTS 10

static YoutubeResult youtube_results[MAX_YOUTUBE_RESULTS];
static int youtube_results_count = 0;
static YoutubeSearchState search_state = YT_SEARCH_IDLE;
static char current_query[256];
static pthread_t search_thread;

void free_youtube_results(void) {
    youtube_results_count = 0;
}

int get_youtube_results_count(void) {
    return youtube_results_count;
}

YoutubeResult *get_youtube_result(int index) {
    if (index >= 0 && index < youtube_results_count) {
        return &youtube_results[index];
    }
    return NULL;
}

YoutubeSearchState youtube_get_search_state(void) {
    return search_state;
}

void youtube_set_search_state(YoutubeSearchState state) {
    search_state = state;
}

static void *youtube_search_thread_func(void *arg) {
    (void)arg;
    free_youtube_results();
    
    char cmd[2048];
    snprintf(cmd, sizeof(cmd), "/usr/local/bin/yt-dlp --flat-playlist --print \"%%(title)s\" --print \"%%(id)s\" --print \"%%(duration_string)s\" --default-search \"ytsearch%d:\" \"%s\" 2>/dev/null", MAX_YOUTUBE_RESULTS, current_query);

    FILE *fp = popen(cmd, "r");
    if (!fp) {
        search_state = YT_SEARCH_ERROR;
        return NULL;
    }

    char line[1024];
    while (youtube_results_count < MAX_YOUTUBE_RESULTS) {
        if (!fgets(line, sizeof(line), fp)) break;
        line[strcspn(line, "\n")] = 0;
        strncpy(youtube_results[youtube_results_count].title, line, 255);

        if (!fgets(line, sizeof(line), fp)) break;
        line[strcspn(line, "\n")] = 0;
        strncpy(youtube_results[youtube_results_count].video_id, line, 31);

        if (!fgets(line, sizeof(line), fp)) break;
        line[strcspn(line, "\n")] = 0;
        strncpy(youtube_results[youtube_results_count].duration, line, 15);
        
        youtube_results_count++;
    }
    pclose(fp);

    search_state = (youtube_results_count > 0) ? YT_SEARCH_FINISHED : YT_SEARCH_ERROR;
    return NULL;
}

void youtube_search_start(const char *query) {
    if (!query || strlen(query) == 0) return;
    if (search_state == YT_SEARCH_RUNNING) return;

    strncpy(current_query, query, 255);
    search_state = YT_SEARCH_RUNNING;
    pthread_create(&search_thread, NULL, youtube_search_thread_func, NULL);
    pthread_detach(search_thread);
}

// More permissive sanitization for Linux filesystems
static void sanitize_for_filesystem(char *str) {
    for (; *str; str++) {
        // Only replace characters that are strictly illegal or problematic in shell commands
        if (*str == '/' || *str == '\'' || *str == '\"' || *str == '`' || *str == '$') {
            *str = '_';
        }
    }
}

char *youtube_get_stream_url(const char *video_id, const char *title) {
    if (!video_id || strlen(video_id) == 0) return NULL;

    static char final_path[512];
    char clean_title[256];
    
    if (title && strlen(title) > 0) {
        strncpy(clean_title, title, 255);
        clean_title[255] = '\0';
        sanitize_for_filesystem(clean_title);
        snprintf(final_path, sizeof(final_path), "/home/doanchim/Music/%s.mp3", clean_title);
    } else {
        snprintf(final_path, sizeof(final_path), "/home/doanchim/Music/YT_%s.mp3", video_id);
    }

    if (access(final_path, F_OK) != -1) {
        struct stat st;
        if (stat(final_path, &st) == 0 && st.st_size > 50000) {
            return strdup(final_path);
        }
    }

    char cmd[2048];
    // Download and convert to mp3 with full metadata and thumbnail
    // Use --ffmpeg-location if needed, but standard path should work
    snprintf(cmd, sizeof(cmd), "/usr/local/bin/yt-dlp -x --audio-format mp3 --embed-thumbnail --add-metadata -o \"%s\" \"https://www.youtube.com/watch?v=%s\" --no-continue 2>/dev/null", final_path, video_id);
    
    if (system(cmd) == 0 && access(final_path, F_OK) != -1) {
        return strdup(final_path);
    }

    return NULL;
}

void youtube_cleanup_temp_files(void) {
}

void youtube_clear_playlist(void) {
}
