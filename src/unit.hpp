#ifndef _RTS_UNIT_HPP_
#define _RTS_UNIT_HPP_

#include <iostream>
#include <string>

#include <yaml-cpp/yaml.h>

struct Unit
{
    double hitpoints = 100.0;
    double damage = 0.0;
    double speed = 100.0;
    double charge = 0.0;
    double reload = 1.0;

    Unit() = default;
    Unit(const std::string &path);
};

struct Tank : Unit
{
    Tank();
};

struct Support : Unit
{
    Support();
};

const std::string operator>>(const YAML::Node &node, Unit &unit);

#endif
