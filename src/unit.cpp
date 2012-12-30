#include <iostream>
#include <fstream>
#include <stdexcept>

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
        throw std::runtime_error("YAML::Parser::GetNextDocument()");
    }

    std::string script(node >> *this);

    file.close();

    std::cout << "new unit: (" << reinterpret_cast<void *>(this) << ")" << std::endl << "  script: " << script << std::endl << "  config: " << path << std::endl << std::endl;

    L = luaL_newstate();

    if (!L)
    {
        throw std::runtime_error("luaL_newstate()");
    }

    luaL_openlibs(L);
    if (luaL_loadfile(L, script.c_str()) != LUA_OK)
    {
        throw std::runtime_error("luaL_loadfile(L, script.c_str())");
    }

    if (lua_pcall(L, 0, 0, 0) != LUA_OK)
    {
        throw std::runtime_error("lua_pcall(L, 0, 0, 0)");
    }

    lua_getglobal(L, "Unit");
    lua_getfield(L, -1, "create");
    lua_remove(L, -2);
    lua_pushnumber(L, hitpoints);
    lua_pushnumber(L, damage);
    lua_pushnumber(L, speed);
    lua_call(L, 3, 1);
}

Unit::~Unit()
{
    if (L)
        lua_close(L);
}

Tank::Tank() : Unit("data/tank.yaml")
{
}

Tank::~Tank()
{
}

Support::Support() : Unit("data/support.yaml")
{
}

Support::~Support()
{
}

std::string operator>>(const YAML::Node &node, Unit &unit)
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
