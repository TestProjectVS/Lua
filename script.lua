persons = {"A", "C", "Z", "X"}
nrOfPersons = 4;
activities = {"walking", "working", "taking a break", "drinking coffe", "running" , "sleeping", "doing a given task" ,"cursing and listening to music"}
rooms = {"Corridor", "A's office", "Z's office", "Cafeteria", "Lab", "Classroom"}
currentRoom = {2, 5, 3, 5}
currentAct = {2, 3, 2, 6}
goal = {0,0,0,0}

function checkRoom(index)
check = 0
	for i = 0, nrOfPersons, 1 do
		if currentRoom[index] == currentRoom[i] and index ~= i then
			check = 1
		end
	end
	return check
end

function behaviour()
	--A
	if goal[1] == 0 then
		if currentRoom[1] == 2 then
			currentRoom[1] = 1
			currentAct[1] = 1
			goal[1] = 4
		else
			currentRoom[1] = 1
			currentAct[1] = 1
			goal[1] = 2
		end
	else 
		if goal[1] == 4 then
			currentAct[1] = 4
			currentRoom[1] = goal[1]
			goal[1] = 0
		else 
			if goal[1] == 2 then
				currentAct[1] = 2
				currentRoom[1] = goal[1]
				goal[1] = 0
			end
		end
	end

	--C
	random = game.random(1,6)
	if checkRoom(2) and currentAct[2] ~= 7 then
		currentAct[2] = 7
	else
	if goal[2] == 0 then
		if random ~= currentRoom[2] then
			currentRoom[2] = 1
			currentAct[2] = 5
			goal[2] = random
		end
	else
		currentAct[2] = 3
		currentRoom[2] = goal[2]
		goal[2] = 0
	end
	end
	--Z
	running = 0
	for i=1, nrOfPersons, 1 do
		if currentRoom[i] == 1 and currentAct[i] == 5  then
			running = 1
		end
	end

	if running == 1 then
		currentAct[3] = 8
	else
		currentAct[3] = 2
	end

	--X
	if goal[4] == 0 then
		if checkRoom(4) == 1 then
			currentRoom[4] = 1
			currentAct[4] = 1
			goal[4] = game.random(1,6)
		end
	else
		currentRoom[4] = goal[4]
		goal[4] = 0
		if checkRoom(4) == 1 then
			currentAct[4] = 3;
		else
			currentAct[4] = 6;
		end
	end
	for k = 1, nrOfPersons, 1 do
		game.print(persons[k] .. " is " .. activities[currentAct[k]] .. " in " .. rooms[currentRoom[k]])
	end
	game.print("\n")
end