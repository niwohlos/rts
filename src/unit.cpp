#include <iostream>
#include <fstream>

#include "unit.hpp"

Unit::Unit(const std::string &path)
{
    std::ifstream file;

    file.exceptions(file.exceptions() | std::ios_base::failbit);

    file.open(path);

    YAML::Parser parser(file);
    YAML::Node node;

    if (!parser.GetNextDocument(node))
    {
    }

    std::string script = node >> *this;

    std::cout << "new unit: (" << reinterpret_cast<void *>(this) << ")" << std::endl << "  script: " << script << std::endl << "  config: " << path << std::endl << std::endl;

    file.close();
}

Tank::Tank() : Unit("data/tank.yaml")
{
}

Support::Support() : Unit("data/support.yaml")
{
}

const std::string operator>>(const YAML::Node &node, Unit &unit)
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
