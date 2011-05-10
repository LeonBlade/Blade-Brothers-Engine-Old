-- Blade Brothers Engine
-- main.lua

-- create instances of the classes we need
entity = Entity:new()
player = Player:new()
window = Window:new()

-- called when the engine is initialized
function init()
	-- print a lua initializing message
	print("[LUA] initializing ...\n")
	
	-- create our player
	hero = player:addPlayer("player")
	
	-- create the debug_window
	debug_window = window:addWindow()
	
	-- set the position and size
	window:setPosition(debug_window, 5, 5)
	window:setSize(debug_window, 165, 45)	
	window:setMessage(debug_window, "^c5Blade Brothers Engine^n^c0Debug Window")
end

-- called on each game loop
function loop()	
	-- set the debug window's text
	window:setMessage(debug_window, "^c5Blade Brothers Engine^n^c0Debug Window")
end

-- called whenever a key is pressed
function key_press(key)
	if key == 32 then
		print("[LUA] The SPACE key was pressed!")
	end
end
