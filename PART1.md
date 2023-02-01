# Part 1

## Video Demo

Please provide the YouTube link to your [https://youtu.be/vRWY-Lpeg0k]

## Minimum Requirements

### Completed

List all the features completed.

1. Game Board
2. Attributes
3. Movements and Attacks
4. Multiple Zombies
5. Game Objects
6. Game Controls

### To Do

List all the features not yet done. Remove this section if there is no incomplete requirements.

1. Saving and loading game file
2. Game Flow is still incompleted
3. Set the life limit for Alien
4. Arrow of turn for attacks

## Additional Features

We haven't contributed to any Additional Features.

## Contributions

List down the contribution of each group members.

For example:

### MUHAMMAD AMIRUL HAIQAL BIN ZAMERI

1. Doing Game Objects
2. Doing Game Contols
3. Commands

### MUHAMMAD AFIF JAZIMIN BIN IDRIS

1. Doing Game Board
2. Doing Game Flow
3. Doing the Win or Dead

### LEE JUN YAO

1. Attributes
2. Movement and Attacks
3. Multiple Zombies
4. Reset Path

## Problems Encountered & Solutions

1.  Problem: Unable to make path reseting    
    Solution: Finding help from other people
2.  Problem: Unable to figure out valid position for zombies    
    Solution: It first checks if the position is occupied by an alien by comparing the input position with the values stored in the alienX and alienY variables. If they are equal, the function returns false, indicating that the position is not valid.

    Next, it loops through the zombies and checks if any of the zombies occupy the position by comparing the input position with the values stored in the zombiesX and zombiesY arrays. If there is a match, the function returns false.

    If none of the checks return false, the function returns true, indicating that the position is valid. r and c, and returns a boolean value indicating whether the position (r, c) is valid or not.
