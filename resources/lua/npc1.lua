-- on initialize
function init()

end

-- this function is called whenever you talk to the entity
function talk()
	-- create our window and return the window index
	mywindow = window:addWindow()
	print("mywindow " .. mywindow)

	-- now we can set our parameters
	window:setPosition(mywindow, 180, 350)
	window:setSize(mywindow, 200, 60)
	window:setMessage(mywindow, "^c3Veteran^c0^n\"Greetings, Hero!\"")
end