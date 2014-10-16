#include "Actor.h"
#include "AnimRig.h"

void game_pre_step(float dt)
{
#if 0
    extern ActorId g_actor;
    Actor* actor = g_actorWorld.get_actor(g_actor);
    if(actor)
    {
        extern void* get_anim_rig(Id);
        AnimRigInstance* rig = (AnimRigInstance*)get_anim_rig(g_actor.get_id());
        if(rig)
        {
            bool bPlaying = rig->is_playing_animation();
            if(!bPlaying)
            {
                int xx = 0;
            }
        }
    }
#endif
}

void game_step(float dt)
{

}

void game_post_step(float dt)
{

}

void game_render(float)
{

}