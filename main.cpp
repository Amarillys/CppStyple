/*
A simple mixing sample program.
    Email:kami@maikaze.win   (reply in 24 hours)
    QQ:     719862760               (reply in 24 hours)
*/
#include "header/base.hpp"
#include "header/object.hpp"

//Objects to deal with errors.
#include "header/mkzinf.hpp"

const s32 kEXIT_SUCCESS = 0;

using namespace object;
using namespace maikaze;

int main()
{
    Player * player_one = new Player();
    std::cout << sizeof(*player_one) << std::endl;

    MkzInf inf(0x38, "File Not Found.");
    inf.ShowErr();

    //Pausing.
    //also we can use std::getchar().
    //declaration with intilization.
    u32 test_int = 0;
    std::cin >> test_int;

    delete player_one;
    return kEXIT_SUCCESS;
}