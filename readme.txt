Submitters:
Ben Liberman: 322465600
Dmytro Kreicherek: 338062755

============<Exercise 3>============
Climbing ghost behavior:
- Climbing ghosts follow Mario (sophisticated algorithm), we don`t follow him directly, but find the closest path to him (if there is a path).
- You cannot jump over Climbing ghosts, because they walk towards you. The only way to deal with them is the Hammer or running away.
- If both Mario and a Climbing ghost are on opposing ladders, the ghost will stay on the ladder until you reach the floor. 
- To allow following behavior, regular ghosts don`t collide with Climbing ghosts. 
- The Climbing ghost`s char in the game is '%' while in file it`s still 'X'

Features:
- The load mode of the Game gets all the recording files and tries to play them in lexicograpghical orded, if for some reason there is no 
  .screen file for one of the recordings, the game will display an error. 

Bonuses:
-   Climbing ghosts following behavior.
============<Exercise 3>============
============<Exercise 2>============

Level file validation:
-   The following entities have to be in the game, if their positions are not
    specified in the level file, the file is considered invalid.
    Mario, Pauline, Donkey Kong and the legend which provides game info

-   Multiple instances of entities listed above in the file is allowed, tho only 
    the first instance matters.

-   Having incomplete lines (<80 characters) or file with <25 lines is allowed,
    the rest of the line/ file is the filled with blank spaces

Features:
-   Because of filesystem namespace that is used, the project should be played on C++ 17 or above

-   Score: You get 25 pts for hitting an enemy with a hammer and 100 pts for reaching the princess (completing a level)

-   The hammer strikes 2 tiles in the direction Mario is facing instead of 1,
    this makes it easier to hit something.
    https://mama.mta.ac.il/mod/forum/discuss.php?d=3638

-   Because Ghosts are supposed to move on a floor and dont have any vertical movement logic,
    all the Ghosts that dont have floor beneath their spawn positions dont get spawned at all.

Bonuses:
-   The Ghosts wait until the next frame to move if they changed direction that frame. See Ghost::moveGhost().
    This made it a little easier to dodge them, and made them look better on screen.

-   The screen with level selection allows selection both with digits 0-8 (9 is reserved for BACK)
    and with an arrow that can be controlled with W, X (up, down).
    If there are more than 9 levels, they are shown in groups of 9 and the user can scroll them!

-   The hammer has an animation when you use it.

============<Exercise 2>============
============<Exercise 1>============

Features:
-   Mario can move freely during fall and change horizontal directions midjump
    We chose free fall option 3 from here: https://mama.mta.ac.il/mod/forum/discuss.php?d=2206
    that Amir accepted - Mario can change his horizontal movement during a fall.

-   If Mario tries to move horizontally ('A', 'D') while on a ladder we chose to stop him, 
    same behaviour as when he presses 'S'. Also after Mario climbs up and down he doesnt 
    continue his horizontal movement, in our experience in provided better control over his movement.

Bonuses:
-   There is a wall character 'W' that Mario cannot pass through, and screen border 'Q'.
    Board holds an array of obstacles, objects that Mario can't pass through so adding a new one
    is easy. Same with things that hurt Mario (hazards).

-   There is a pizzeria building that is climbable with stairs. And parts of it are in the background.
    Moving objects (like Mario and Barrels) don't erase chars that are 
    in the background (non obstacles/hazards).
    
-   On static screen (like game over screen or win screen) there is ascii art.

-   Main menu screen allows navigation with an arrow and pressing ENTER to select in addition
    to the requested hotkeys - 1, 8, 9.

-   The Barrels spawn either left or right, so that they have 2 different routes. In addition they spawn
    with random delay in certain range.

-   Mario can get to the top with 2 different routes (like the Barrels), one is more challenging. 
    So the player can choose which route to take.

-   The exlosion of Barrels is animated (in game loop) and happens in phases
    Mario's death is also animated.
============<Exercise 1>============