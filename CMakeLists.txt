cmake_minimum_required(VERSION 3.10)
project(chimmusicplayer LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# Options
option(USE_DBUS "Enable DBUS notifications" ON)
option(USE_FAAD "Enable faad2 support" ON)

# Find Packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 REQUIRED glib-2.0 gio-2.0 gobject-2.0)
pkg_check_modules(TAGLIB REQUIRED taglib)
pkg_check_modules(CHAFA REQUIRED chafa)
pkg_check_modules(FFTW3 REQUIRED fftw3f)
pkg_check_modules(OPUS REQUIRED opus opusfile)
pkg_check_modules(VORBIS REQUIRED vorbis vorbisfile ogg)

# Include directories
include_directories(
    src
    include
    include/minimp4
    include/stb_image
    include/miniaudio
    include/nestegg
    ${GLIB2_INCLUDE_DIRS}
    ${TAGLIB_INCLUDE_DIRS}
    ${CHAFA_INCLUDE_DIRS}
    ${FFTW3_INCLUDE_DIRS}
    ${OPUS_INCLUDE_DIRS}
    ${VORBIS_INCLUDE_DIRS}
)

# Source files
set(SOURCES
    src/common/appstate.c
    src/common/common.c
    src/ui/common_ui.c
    src/ui/control_ui.c
    src/ui/input.c
    src/ui/playlist_ui.c
    src/ui/search_ui.c
    src/ui/player_ui.c
    src/ui/youtube_ui.c
    src/ui/visuals.c
    src/ui/chroma.c
    src/ui/queue_ui.c
    src/ui/settings.c
    src/ui/cli.c
    src/utils/utils.c
    src/utils/file.c
    src/utils/cache.c
    src/utils/term.c
    src/sound/sound.c
    src/sound/m4a.c
    src/sound/sound_builtin.c
    src/sound/audiobuffer.c
    src/sound/decoders.c
    src/sound/audio_file_info.c
    src/sound/playback.c
    src/sound/volume.c
    src/sys/sys_integration.c
    src/sys/notifications.c
    src/sys/mpris.c
    src/sys/discord_rpc.c
    src/ops/playback_ops.c
    src/ops/playback_clock.c
    src/ops/playback_system.c
    src/ops/playlist_ops.c
    src/ops/library_ops.c
    src/ops/track_manager.c
    src/ops/playback_state.c
    src/ops/youtube_ops.c
    src/data/theme.c
    src/data/directorytree.c
    src/data/lyrics.cpp
    src/data/img_func.c
    src/data/song_loader.c
    src/data/playlist.c
    src/data/tagLibWrapper.cpp
    src/chimmusicplay.c
    include/nestegg/nestegg.c
)

# Executable
add_executable(chimmusicplayer ${SOURCES})

# Definitions
target_compile_definitions(chimmusicplayer PRIVATE 
    KEW_VERSION="v4.0.0-chimmusic"
    DMA_NO_AAUDIO
)

if(USE_DBUS)
    target_compile_definitions(chimmusicplayer PRIVATE USE_DBUS)
endif()

if(USE_FAAD)
    target_compile_definitions(chimmusicplayer PRIVATE USE_FAAD)
    target_link_libraries(chimmusicplayer PRIVATE faad)
endif()

# Linking
target_link_libraries(chimmusicplayer PRIVATE
    ${GLIB2_LIBRARIES}
    ${TAGLIB_LIBRARIES}
    ${CHAFA_LIBRARIES}
    ${FFTW3_LIBRARIES}
    ${OPUS_LIBRARIES}
    ${VORBIS_LIBRARIES}
    pthread
    m
    atomic
)

# Installation
install(TARGETS chimmusicplayer DESTINATION bin)
