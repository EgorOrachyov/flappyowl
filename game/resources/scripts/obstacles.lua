--[[ Columns, money generation and movement --]]
Obstacles = { game = nil,
              scroll_speed = 0,
              do_scroll = true }

--[[ Generate scene coins and columns --]]
function Obstacles:generate()
    self.parent:remove_children()

    local coin_resource = wmoge.ResourceManager.load("res://sprites/coin")
    local column_resource = wmoge.ResourceManager.load("res://sprites/column")

    for i = 1, self.game.num_columns do
        local transform = wmoge.Transform2d()
        transform:translate(wmoge.Vec2f.new(10 + i * 70, self.game.screen_size.y / 2 + wmoge.Random.next_float_in_range(-20, 20)))

        local obstacle = wmoge.SceneManager.make_object("obstacle-" .. tostring(i))
        obstacle:get_or_create("Spatial2d"):update_transform(transform)

        local coin = wmoge.SceneManager.make_object("coin")
        coin:get_or_create("Spatial2d")
        local coin_sprite = coin:get_or_create("SpriteInstance")
        coin_sprite:create(coin_resource)
        coin_sprite:play_animation(0)
        obstacle:add_child(coin)

        local lower_column = wmoge.SceneManager.make_object("lower")
        local lower_column_transform = wmoge.Transform2d()
        lower_column_transform:translate(wmoge.Vec2f.new(0, -10))
        lower_column_transform:scale(wmoge.Vec2f.new(1, 1.5))
        lower_column:get_or_create("Spatial2d"):update_transform(lower_column_transform)
        local lower_column_sprite = lower_column:get_or_create("SpriteInstance")
        lower_column_sprite:create(column_resource)
        obstacle:add_child(lower_column)

        local upper_column = wmoge.SceneManager.make_object("upper")
        local upper_column_transform = wmoge.Transform2d()
        upper_column_transform:translate(wmoge.Vec2f.new(0, 10))
        upper_column_transform:scale(wmoge.Vec2f.new(1, -1.5))
        upper_column:get_or_create("Spatial2d"):update_transform(upper_column_transform)
        local upper_column_sprite = upper_column:get_or_create("SpriteInstance")
        upper_column_sprite:create(column_resource)
        obstacle:add_child(upper_column)

        self.parent:add_child(obstacle)
    end

    wmoge.Log.log(wmoge.Log.Info, "generate scene obstacles", "obstacles.lua", "generate", 47)
end

function Obstacles:on_scene_enter()
    self.game = self.parent:get_scene():find_child("game"):get("ScriptComponent")
    self.scroll_speed = self.game.scroll_speed_initial
    self:generate()

    wmoge.GameTokenManager.set("scroll_speed", 0)

    self.on_restart = wmoge.EventManager.subscribe("restart", function(_)
        self:generate()
        self.do_scroll = true
        self.scroll_speed = self.game.scroll_speed_initial
    end)

    self.on_dead = wmoge.EventManager.subscribe("dead", function(_)
        self.do_scroll = false
    end)
end

--[[ Unsubscribe callbacks for events --]]
function Obstacles:on_scene_exit()
    self.on_restart:unsubscribe()
    self.on_dead:unsubscribe()
end

--[[ Move columns towards player, if first out of the screen, push it back --]]
function Obstacles:on_update(delta_time)
    if self.do_scroll then
        local shift = -self.scroll_speed * delta_time
        self.scroll_speed = self.scroll_speed + self.game.scroll_acceleration * delta_time

        wmoge.GameTokenManager.set("scroll_speed", self.scroll_speed)

        for i = 0, self.game.num_columns - 1 do
            local obstacle = self.parent:get_child(i)
            local spatial = obstacle:get("Spatial2d")
            local transform = spatial:get_transform()

            transform:translate(wmoge.Vec2f.new(shift, 0))

            if transform.translation.x < -10 then
                local new_pos_x = transform.translation.x + 70 * self.game.num_columns
                local new_pos_y = self.game.screen_size.y / 2 + wmoge.Random.next_float_in_range(-20, 20)
                transform.translation = wmoge.Vec2f.new(new_pos_x, new_pos_y)
                obstacle:get_child("coin"):get("SpriteInstance"):show()
            end

            spatial:update_transform(transform)
        end
    end
end

return new(Obstacles, wmoge.SceneObject)