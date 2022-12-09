# Overview

This document is designed to outline the goals of which we are going to meet by the time that we deliver the game. The document is being split into a few sections, which are the same in the functional and non-functional sections. Then, requirements will be listed for the respective section under the section, which will describe how the object that the section describes will function in the release.

# Functional Requirements

1. General Gameplay Requirements
   1. Our game shall implement common puzzle-game tropes.
   2. The user shall be able to move the player through the levels.
   3. The player shall be able to move between levels.
   4. The layout of the levels shall be predefined.
   5. The levels shall take place on a 2d grid of tiles, each object takes up 1 tile.
   6. Objects that the game shall implement include: walls, doors, buttons, pressure plates, levers, spikes, stairs, and robots.
   
2. Player Requirements
   1. The Player statistics shall be recorded upon completing the game.
   2. The player object shall be moveable based on user input.
   3. Our game shall detect collisions between the player and other non-passable objects.
   4. The player shall die and return to the start of the level upon contact with damaging obstacles.
   5. The player shall have money, which is earned from opening chests and entering new levels. 
   6. The player shall be able to move between levels by using stairs
3. Puzzle Requirements
	1. There shall be Objects that the player can interact with.
	2. Switch objects, like levers or buttons, shall alter the state of other objects.
	3. Robots shall copy the player's movement when not blocked by a wall
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
	3. The player's position will be updated upon the player entering a new room.
	4. The user shall be able to check the amount of money collected by the player
	5. The player shall be controlled with WASD or the arrow keys, and interact with objects with the Spacebar.
3. Graphics/UI Requirements
	1. Our game shall update at a rate of 30 frames per second.
	2. Our game shall inform the user of events such as opening doors, death of the player, or entering a new level, through text at the bottom of the screen.
	3. Our game interface shall be able to show all the details without being confusing or overwhelming.
	4. The game shall be rendered using the ncurses library in a terminal.
	5. The user shall be able to differientate between the different objects/tiles/entities, with each having a unique symbol and/or color.
	6.  The interface shall be consistent and visually appealing.
	7. The UI shall update the screen smoothly when changing levels.
	
	
# Software Artifacts
This is the list of all artifacts created for this project
[Project Proposal](https://github.com/CJSchneider320/GVSU-CIS350-ECAN/blob/master/docs/proposal.md)

[Tasks](https://github.com/CJSchneider320/GVSU-CIS350-ECAN/blob/master/docs/tasks.md)

[Original SRS](https://github.com/CJSchneider320/GVSU-CIS350-ECAN/blob/master/docs/software_requirements_specification.md)

[Midterm Presentation](https://github.com/CJSchneider320/GVSU-CIS350-ECAN/blob/master/docs/midterm_presentation_projectECAN.pdf)

[Final Presentation](https://github.com/CJSchneider320/GVSU-CIS350-ECAN/blob/master/docs/final_presentation_projectECAN.pdf)