-- Create new Entity object
npc = Entity:new()

-- generate a random number
r = math.random(1, 4)

-- set paths
s_path = "../resources/sprites/char" .. tostring(r) .. ".png"
l_path = "../resources/lua/npc" .. tostring(r) .. ".lua"

-- Load NPC
npc:OnLoad(s_path, 3, true)

-- Set the Lua script
npc:SetScript(l_path)

io.write("[LUA] create_npc.lua created a new NPC!\n")
