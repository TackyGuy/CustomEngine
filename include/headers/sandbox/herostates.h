#pragma once

#include <string>
#include <ostream>

namespace Sandbox
{
    struct HeroStates
    {
        #define IDLE_STATE 1
        #define MOVE_STATE 2
        #define COMBAT_STATE 4

        int flags = IDLE_STATE;

        void setFlag(int flag, bool val = true)
        {
            if (hasFlag(flag) != val) 
            {
                if (val) flags |= flag;
                else flags &= ~flag;
            }
        }

        bool hasFlag(int flag) const
        {
            return ((flags & flag) == flag);
        }

        friend std::ostream& operator<<(std::ostream& os, const HeroStates& states)
        {
            std::string res;
            if ((states.flags & IDLE_STATE) == IDLE_STATE) res.append("IDLE_");
            if ((states.flags & MOVE_STATE) == MOVE_STATE) res.append("MOVE_");
            if ((states.flags & COMBAT_STATE) == COMBAT_STATE) res.append("COMBAT");

            os << res;

            return os;
        }
    };
}