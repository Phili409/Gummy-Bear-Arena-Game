**Directory Description:**
The following are general descriptions of how the combined { .h & .cpp } files operate within the program.
--------------------------------------------------------------------------

**@Assets ->** holds 6 UI .txt files used to easily render interfaces.
**@Save ->** holds the game’s save file { save.txt }.

**@main.cpp ->** entrance to program, main loop lives here.
**@Actions ->** used to handle user’s actions, i.e., attacking.
**@MemorySystem ->** handles active game session data & save file data, allowing a dynamic memory system.
**@RNG ->** generates random but instructed values for in game mechanics, such as spawning a minion & setting its stats.
**@UI ->** handles terminal interface, updating current interfaces or renders interfaces based on conditions.
**@GameEntities ->** defines game entities, both NPC & user objects. Contains the object’s attributes/stats used for battling.


**Colosseum Mode** is a dynamic combat system that generates dynamic waves of enemy gummies through a RNG system that uniquely creates gummies based on current game factors. This system assures a constant challenge, as well as a sense of game progression.

**Scalability** because of the independent game modules, each file that is included to “main.cpp”, the game can be easily scaled up to include new features such as: new usable moves, gummy types, game modes, & interfaces.

**RNG Mechanic**, the file “RNG.cpp” generates unique values used throughout the system always, which assures the user a fresh feeling every single time.
Example: waves are generated with minion & boss type gummies, but the size of the wave and the probability of bosses spawning is generated randomly with influence from current game factors.
