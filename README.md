# DNDProject
An unfinished Unreal Engine 4 project, intended to be a Top-Down MMO taking inspiration from the tabletop game Dungeons And Dragons.

Most of the things I did with this project I did them with C++, blueprints are still used but are much simpler with the help of C++ methods.

The DND/GameMode folder has anything related to game mode (Player controller, player state, and so forth).
This game uses the GAS plugin (Gameplay Ability System), and everything related to the plugin is inside the AbilitySystem folder.
The DND/AbilitySystem folder has only one character named "Bard", in which ability logic has been created, there are also custom calculations (MMC) and Target Actors.
To know more about the Gameplay Ability System plugin you can check [this documentation](https://github.com/tranek/GASDocumentation)
The DND/Characters folder contains the base class, the Hero class is what the players are given. The Enemy Class is just used as a target dummy.
The DND/AI folder is not relevant yet.
