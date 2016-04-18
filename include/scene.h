#ifndef __Game_Kaboom_include_scene_h__
#define __Game_Kaboom_include_scene_h__

/*******************************************************************************
*                                                                              *
*******************************************************************************/
typedef struct _scene_t
{
    int id;

    void (*load_func        )(void);
    void (*unload_func      )(void);
    void (*update_func      )(float dt);
    void (*draw_func        )(void);
    void (*handle_event_func)(SDL_Event *event);

} scene_t;

#endif /* __Game_Kaboom_include_scene_h__ */
