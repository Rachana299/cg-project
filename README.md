# Rubik's Cube

This is a simulation of a fully functional Rubik's cube through Computer Graphics using OpenGL in C language.<br>
The cube uses shaded dark plastic, inset stickers with clipped corners, and directional lighting for a more realistic appearance.<br>
Cube turns use a fixed animation speed of 2.5 degrees per animation step.<br>
The live cube map in the lower-right corner shows the colors on all six faces and updates as the cube moves.<br>
The on-screen HUD, game-mode cards, cube map, and controls use a consistent dark theme with clear status accents. The HUD shows the active turn or mode and quick mouse guidance.<br>
Right-click the output screen to open or close the controls panel. It stays open while clicking its move controls or dragging outside it to rotate the cube.<br>
Choose Practice to create an untimed 10-, 20-, or 30-move scramble. Step shows and applies the next reverse-scramble move; Play animates the remaining sequence, Pause stops after the current turn, and Exit, a manual turn, or undo leaves practice mode.<br>
Choose Challenge for the timed 10-, 20-, or 30-move scramble and its 3-2-1-GO countdown. During a challenge, Pause freezes the timer and move input, Resume continues it, and Stop ends the challenge. A challenge also ends when the cube is solved or time runs out. Scramble moves can be undone with `o`. You can also use the keys shown in the controls panel.<br>
Click and drag outside the controls panel to change the orientation of the cube.<br>

## Initiation and Execution

To execute this in a Linux terminal, the commands are:<br>
- To open the file: `gedit RCube.c`
- To compile the file: `gcc RCube.c -lGL -lGLU -lglut -lm`
- To execute the file: `./a.out`

Make sure OpenGL is installed in the system to run this program.
