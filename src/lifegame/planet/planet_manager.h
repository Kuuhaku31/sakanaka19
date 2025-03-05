
// planet_manager.h

#pragma once

#include "base.h"

#include "planet.h"

class PlanetManager : public InstanceTem<PlanetManager>
{
    friend class InstanceTem<PlanetManager>;

public:
    typedef std::vector<Planet> Planets;

public:
    void On_update(float delta_time);
    void On_render() const;

public:
    const Planets& Get_planets() const;

public:
    void Set_planets0_pos(const Vector2& pos)
    {
        planets[0].Set_position(pos);
    }

    void Set_planets0_radius(float radius)
    {
        planets[0].Set_planet_radius(radius);
    }

private:
    Planets planets;

private:
    PlanetManager();
    ~PlanetManager() = default;
};
