
// lifegame.h

#pragma once

#include "base.h"

class LifeGame : public InstanceTem<LifeGame>
{
    friend class InstanceTem<LifeGame>;

public:
    int Run();

private:
};
