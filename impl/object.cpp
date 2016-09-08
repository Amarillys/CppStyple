#include "../header/object.hpp"

namespace object
{
    void Player::Init()
    {
        point_set_.reserve(kSurfaceCapacity / 2 + 1);
    }

    void Player::SkipTime() const
    {

    }

    u32 Player::count(Player p_player) const
    {
        return point_set_.size();
    }

    void Player::DoSomeThing(
        std::string p_name, s32 p_player_type,
        s32 p_player_age, s32 p_player_level)
    {
        if (p_player_age < 0) {
            p_player_age = 0;
            return;
        } else {
            p_player_age++;
        }
    }
}