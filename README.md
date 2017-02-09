# SpringAndPointsSimulation
2D Simulation of points linked by springs using C++ and SDL.

## Examples
Look at screenshots to understand how it works.
On the example 1, you can see the user putting points.
All new points are linked to the selected point with a equilibrium length set to the current distance between the 2 points.
You can also move points or delete them.
When you press space, you set all the springs to a equilibrium length of 1.
Finally you can pause the simulation with P.

## Coding
There is 4 class :

Name | Purpose | Comment
:--: | :--: | :--
Point | Points | Classical 2D mathematical point
Noeud | Nodes | A point with a mass with a point for velocity and acceleration. Can be fixed.
Lien | Springs | Link between 2 points. Have a equilibrium length and a spring constant.
Grille | Field | A list of nodes and springs. Have a set of functions to evolve in the time.
Render | Render of the Field | Render a field on a window

There is one class per file. There is also a file `fonctions.php` that hold all the basic functions.
