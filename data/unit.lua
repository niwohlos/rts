Unit = {}
Unit.__index = Unit

shield_lookup = {
    0,
    25,
    50,
    75
}

function Unit.create(hitpoints, damage, speed)
    local unit = {}

    setmetatable(unit, Unit)

    unit.hitpoints = hitpoints
    unit.damage = damage
    unit.speed = speed
    unit.shield = 0
    unit.supporters = 0

    return unit
end

function Unit:receive_damage(amount)
    self.hitpoints = self.hitpoints - amount

    if self.hitpoints < 1 then
        self:explode()
    end
end

function Unit:add_supporter()
    self.supporters = self.supporters + 1

    if unit.supporters > 3 then
        self:explode()
    end
end

function Unit:remove_supporter()
    self.supporters = self.supporters - 1

    if self.shield > shield_lookup[self.supporters + 1] then
        self.shield = shield_lookup[self.supporters + 1]
    end
end

function Unit:update()
    self.shield = self.shield + self.supporters

    if self.shield > shield_lookup[self.supporters + 1] then
        self.shield = shield_lookup[self.supporters + 1]
    end
end

function Unit:explode()
    -- do something
end
