#pragma once

#include <string>

#include "stage.hpp"

namespace Core
{
    class StageManager
    {
        public:
            virtual ~StageManager(){}

            virtual void setStage(std::string stageName) = 0;

    };
}