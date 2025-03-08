
// sekibako.h

#pragma once

#include "base.h"

class SEKIBAKO : public InstanceTem<SEKIBAKO>
{
    friend class InstanceTem<SEKIBAKO>;

public:
    int Run(InitArgs& args);

private:
    void init(InitArgs& args);
    void loop();
    void quit();
};
