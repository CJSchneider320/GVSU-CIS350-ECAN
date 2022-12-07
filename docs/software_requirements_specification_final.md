# Overview

This document is designed to outline the goals of which we are going to meet by the time that we deliver the game. The document is being split into a few sections, which are the same in the functional and non-functional sections. Then, requirements will be listed for the respective section under the section, which will describe how the object that the section describes will function in the release.

# Functional Requirements

1. General Gameplay Requirements
   1. Our game shall implement common puzzle-game tropes.
   2. The user shall be able to move the player through the levels.
   3. The player shall be able to move between levels.
   4. The layout of the levels shall be predefined.
   5. Additional challenge levels can be unlocked with money after beating the regular levels.
   6. The levels shall take place on a 2d grid of tiles, each object takes up 1 tile.
   7. Objects that the game shall implement include: walls, doors, buttons, pressure plates, levers, spikes, stairs, and robots.
   
2. Player Requirements
   1. Player statistics shall be recorded on player-character death.
   2. The player object shall be moveable based on user input.
   3. Our game shall detect collisions between the player and other non-passable objects.
   4. The player shall die upon touching a spike object.
   5. The player shall have money, which is earned from opening chests and entering new levels. 
   6. The player shall be able to move between levels by using stairs
3. Puzzle Requirements
	1. There shall be Objects that the player can interact with.
	2. Switch objects, like levers or buttons, shall alter the state of other objects.
	3. Robots shall copy the player's movement when not blocked by a wall.
	4. Pressure plates shall be triggered by players or robots stepping on them.
	5. Heavy pressure plates shall only be triggered by robots stepping on them.
	6. Doors shall be closed or open to player and entity movement, and shall be closed and opened by switches.
	7. All objects that have multiple states (on/off, closed/open) shall have a defined initial state on level start.


# Non-Functional Requirements

1. General Gameplay Requirements
	1. Our game shall be accessible to all, with an easy learning curve but enough depth and replayability.
	2. Our game shall provide players with tangible improvement and a feeling of satisfaction and progress, even after a failure.
	3. Our game shall take user input and update the display accordingly.
	4. The layout of the levels shall be hard coded and the user shall not be able to alter them.
	5. Walls and doors shall be rendered based on the surrounding walls / doors, in order to appear to connect with each other.
2. Player Requirements
	1. The player character shall be represented by a unique, unmistakable symbol.
	2. The player shall always be visible on the screen.
	3. The main screen will be updated upon entering a new room, but the player will "remember" how the prior rooms were left.
	4. The game shall inform the user when the player has died.
	5. The player shall be controlled with WASD, and interact with objects with the Spacebar.
3. Graphics/UI Requirements
	1. Our game shall update at a rate of 30 frames per second.
	2. Our game shall have a easily traversed main menu and corresponding sub-menus to access game play, statistics, and other similar pages.
	3. Our game interface shall be able to show all the details without being confusing or overwhelming.
	4. The game shall be rendered using the ncurses library in a terminal.
	5. The user shall be able to differientate between the different objects/tiles/entities, with each having a unique symbol and/or color.
	6.  The interface shall be consistent and visually appealing.