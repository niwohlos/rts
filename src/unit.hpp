#ifndef _RTS_UNIT_HPP_
#define _RTS_UNIT_HPP_

#include <iostream>
#include <string>

#include <yaml-cpp/yaml.h>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

struct Unit
{
    double hitpoints = 100.0;
    double damage = 0.0;
    double speed = 100.0;
    double charge = 0.0;
    double reload = 1.0;

    lua_State *L = nullptr;

    Unit() = default;
    Unit(const std::string &path);
    ~Unit();
};

struct Tank : Unit
{
    Tank();
    ~Tank();
};

struct Support : Unit
{
    Support();
    ~Support();
};

std::string operator>>(const YAML::Node &node, Unit &unit);

#endif
