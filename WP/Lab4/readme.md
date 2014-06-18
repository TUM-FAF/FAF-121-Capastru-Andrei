Laboratory Work №2
==================

## Title
*Arkanoid*

## Mandatory Objectives
* Create an animation based on Windows timer which involves at least 5 different drawn objects

## Objectives With Points
* Increase and decrease animation speed using mouse wheel **(2 pt)**
* Solve flicking problem **(2 pt)** _please describe in your readme/report how you did it_
* Add animated objects which interact with each other **(2-6 pt)**, ex.:
  * Few balls which have different velocity and moving angles. In order to get max points, add balls with mouse, make balls to change color on interaction and any other things that will show your engineering spirit
  * Any other interesting and reach in animation application

I've choosed to do a Arkanoid game because it is the game of my childhood.

## Developement

1. The application screencapture:

    ![Screenshot1](https://raw.githubusercontent.com/TUM-FAF/FAF-121-Capastru-Andrei/master/WP/Lab4/screen.JPG)
    
2. Developement process
  I have used timer to call each frame. It is updated at each `WM_TIMER` message received. The acceleration was simple because at mouse wheel movement I'm calling the `WM_TIMER` message again. Interaction between tiles and ball was also simple, since I've worked with interaction in developement a simple DirectX game. It is not a rich-animation application, but it is a full game, which I want to achieve more. 
