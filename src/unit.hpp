#ifndef _RTS_UNIT_HPP_
#define _RTS_UNIT_HPP_

#include <iostream>

#include <yaml-cpp/yaml.h>

struct Unit
{
    double hitpoints = 100.0;
    double damage = 0.0;
    double speed = 100.0;
    double charge = 0.0;
    double reload = 1.0;
};

struct Tank : Unit
{
};

struct Support : Unit
{
};

const std::string &&operator>>(const YAML::Node &node, Unit &unit);

#endif
