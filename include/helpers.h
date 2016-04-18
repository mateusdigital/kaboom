#ifndef __Game_Kaboom_include_helpers_h__
#define __Game_Kaboom_include_helpers_h__

void _game_fatal(const char *fmt, ...);

#define GAME_VERIFY(_expr_, _format_, ...)        \
        if(!(_expr_)) {                           \
            _game_fatal(_format_, ##__VA_ARGS__); \
        }


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

#endif /* __Game_Kaboom_include_helpers_h__ */
