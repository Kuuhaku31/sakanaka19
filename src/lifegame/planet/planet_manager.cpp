
// planet_manager.cpp

#include "planet_manager.h"

PlanetManager::PlanetManager()
{
    planets.push_back(Planet({ 0, 0 }, 50000, { 0x00, 0xff, 0x00, 0x88 }));
}

void
PlanetManager::On_update(float delta_time)
{
    for(Planet& planet : planets)
    {
        planet.On_update(delta_time);
    }
}

void
PlanetManager::On_render() const
{
    for(const Planet& planet : planets)
    {
        planet.On_render();
    }
}

const PlanetManager::Planets&
PlanetManager::Get_planets() const
{
    return planets;
}
