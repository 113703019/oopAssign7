# 2025 OOP Assignment #6
- Due: 2025/5/27 23:59:59
- Author: 111703003 廖經翔
- Contact: 111703003@g.nccu.edu.tw
- [Assing5 complete version](https://github.com/oopnccucs/25-assign5-complete)
---


# 2D Console Game (Part2)

Obejctive: Building a console-based Rack-Paper-Scissor Royale

Inspiration: https://aslangames.itch.io/rock-paper-scissors-royale
![image](https://github.com/user-attachments/assets/880e5d43-cd23-4b9d-9d5a-5ed0ea09d7bd)

## Game Concepts

- Entities & Types
Every game object is one of three types: **Rock**, **Paper**, or **Scissor**.

- Assimilation Rule
When two objects collide, the winning type “assimilates” (converts) the losing one:

1. Paper assimilates Rock → the Rock becomes Paper
2. Rock assimilates Scissor → the Scissor becomes Rock
3. Scissor assimilates Paper → the Paper becomes Scissor

- Player Role
The player controls a single **Rock**. At any time, they can switch which Rock they control and move it around the grid.

- Win/Loss Conditions
1. Goal: For the “Rock” faction, assimilate as many Scissors as possible while avoiding Papers.
2. Endgame: The simulation ends when one of the three types is completely eliminated.
   
## Assignment Tasks

In this assignment, you are required to:
1. Create  `RPSGameObject` and implement the Collision feature.
2. Handle player's input  to ** move (W, A, S, D)** and **switch (Tab)** between RPSObjects.
3. When the game ends, determine the winner and print out.

### Sample Output
![image](https://github.com/user-attachments/assets/651bcafa-f3cb-4a75-a663-c54e7c015b0d)
![image](https://github.com/user-attachments/assets/c98e44e0-f485-44a4-aa99-f839f256583e)

### Scoreing Criteria
|Description|Score|
|-----|-----|
|Submit the assignment|20|
|Able to compile|20|
|RPS Objects perform assimilation correctly|20|
|Handling key input to control Rock|10|
|Player can switch between different Rocks|10|
|Game break and winner determination|10|
|More features(please create a "Readme.md" to show your additional designs)|10|

### Reminder

1. GameObjects should not move outside the map.
2. Pseudo code of collision:

```
for colliderA, colliderB in all colliders
  if colliderA intersect with colliderB
    perfom onCollision()
```
