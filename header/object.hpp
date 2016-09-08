#pragma once

#ifndef  STYLE_OBJECT_H_
#define STYLE_OBJECT_H_

#include "base.hpp"

namespace object
{
    const int kSurfaceWidth = 19;
    const int kSurfaceHeight = 19;
    constexpr int kSurfaceCapacity = kSurfaceWidth * kSurfaceHeight;

    const bool kBlack = false;
    const bool kWhite = true;

    struct SurfacePoint
    {
        s32 x;
        s32 y;
        bool type;
    };

    class Player
    {
    public:
        Player() {}
        ~Player() {}
        void DoSomeThing(
            std::string p_name, s32 p_player_type,
            s32 p_player_age, s32 p_player_level);
        void Init();
        void SkipTime() const;

        //A cheap function to return the size of member->point_set_.
        u32 count(Player p_player) const;

    private:
        bool type_;
        std::vector<SurfacePoint> point_set_;
    };
}
#endif // ! STYLE_OBJECT_H_
