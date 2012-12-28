#include <iostream>

#include "unit.hpp"

Tank::Tank() : Unit()
{
    lua_dofile(YAML::Load("data/tank.yaml") >> *this);
}

const std::string &&operator>>(const YAML::Node &node, Unit &unit)
{
    Unit tmp;
    std::string script("data/unit.lua");

    if (node.Type() == YAML::NodeType::Map)
    {
        if (node.FindValue("hitpoints"))
            node["hitpoints"] >> tmp.hitpoints;

        if (node.FindValue("damage"))
            node["damage"] >> tmp.damage;

        if (node.FindValue("speed"))
            node["speed"] >> tmp.speed;

        if (node.FindValue("charge"))
            node["charge"] >> tmp.charge;

        if (node.FindValue("reload"))
            node["reload"] >> tmp.reload;

        if (node.FindValue("script"))
            node["script"] >> script;
    }

    unit = tmp;

    return script;
}
