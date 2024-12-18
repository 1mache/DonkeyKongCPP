Submitters:
Ben Liberman: 322465600
Dmytro Kreicherek: 338062755

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