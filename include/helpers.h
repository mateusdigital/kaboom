#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#ifdef NDEBUG
    #define GAME_LOG(_format_, ...)  do {} while(0)

#else
    void _game_log(const char *func,
                   const char *fmt,
                   ...);

    #define GAME_LOG(_format_, ...) \
        _game_log(__func__,         \
                 _format_,          \
                  ##__VA_ARGS__)

#endif /* NDEBUG */

#endif /* HELPERS_H_INCLUDED */
