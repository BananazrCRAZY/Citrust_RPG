# Fruit RPG

Authors: [Annie Le](https://github.com/anniele2006), [Brandon Hatamoto](https://github.com/BananazrCRAZY), [Eva Bao](https://github.com/evabao007), [Sebastian Chou](https://github.com/stricker1)

## Project Description
Important/Interesting:
* We are able to combine elements of storytelling, game design, and OOP into a personally loved project. We want to be able to think like programmers and game designers, taking into account the compelling narrative and a smoother gameplay, for our users!

### Languages/Tools/Technologies:
* C++
* VSCode
* Github
* Raylib and RayGUI

## Input/Output of Project:
* Keyboard and mouse input, GUI output.
* User .txt file input for character files, and option to output their character information to a .txt file as well

## Features:
* Turn based battle system featuring two types of damage
* A variety of equippable and consumable items to be purchased
* Unique boss items
* An immersive story

## Navigation Diagram  
<p align="center"><img src="https://github.com/user-attachments/assets/12a2ceaf-acd8-4d76-871e-ca21b2bbf826" width = "700"</p>


---
## Screen Layouts
- **Screen Layout:** [View Presentation](https://docs.google.com/presentation/d/113KIpqxjZn-ZylGX6MBx2rM3WvERidij8RLd5BcQcd8/edit?usp=sharing)
## Screen Layout Description

### Title Screen
- **New Game** – Prompts to Orange Creation screen  
- **Load** – Prompts user to pick a save file  
- **Quit** – Exits the UI  

<p align="center">
  <img src="https://github.com/user-attachments/assets/d25c9881-e3ee-4996-9ca8-7050b0adc859" alt="Title Screen Diagram" width="700"/>
</p>

---

### Orange Creation
- Prompts user to enter name  
- **Next** – Goes into story mode  

<p align="center">
  <img src="https://github.com/user-attachments/assets/67d99450-23dc-4008-b240-787e83978087" alt="Orange Creation Diagram" width="700"/>
</p>

---

### Load Screen
- Prompts user to pick one out of 3 save files  

<p align="center">
  <img src="https://github.com/user-attachments/assets/cb4d35de-4223-4fb8-b763-8def18832c31" alt="Load Screen Diagram" width="700"/>
</p>

---

### Prologue 
- Tells the story of Orange being bullied by the different Fruit Bosses  

<p align="center">
  <img src="https://github.com/user-attachments/assets/b52301f8-b3c8-4777-838b-0dca3bb7111e" alt="Prologue Diagram 1" width="700"/>
  <img src="https://github.com/user-attachments/assets/4e4d4a37-2d1b-4461-b387-5b1e8b4f48b5" alt="Prologue Diagram 2" width="700"/>
</p>


---

### Suspense
- Filler story page

<p align="center">
  <img src="https://github.com/user-attachments/assets/098ed379-30ba-4474-8f9a-7aa8a9ebf911" alt="Prologue Diagram 1" width="700"/>
</p>

---

### Tutorial in battle view
- General layout for all boss fights (template)  
- Players have three turn-based options:
  - **Basic Attack** – Requires no skill points  
  - **Skill Attack** – Requires one skill point
  - **Inventory** - Use equippable items purchased
- Reference the linked presentation above for the full tutorial

<p align="center">
  <img src="https://github.com/user-attachments/assets/8d433f8b-5e45-4f8b-bd16-21bda0eabc56" alt="Boss Fight Tutorial Diagram" width="700"/>
</p>

---

### Boss battle
- General layout for all boss fights (template)  
- Players have three turn-based options:
  - **Basic Attack** – Requires no skill points  
  - **Skill Attack** – Requires one skill point
  - **Equipment** - Use equippable items purchased
- Reference the linked presentation above for visuals with other boss types 

<p align="center">
  <img src="https://github.com/user-attachments/assets/9a5b0f6d-819b-42be-a61f-018f9ca8effc" alt="Boss Fight Diagram" width="700"/>
</p>

---

### Interlude
- Players are given three choices:
  - **Shop** – takes player to a screen to purchase items
  - **Inventory** – takes player to view their current inventory of items
  - **Boss** - go onto the next battle

<p align="center">
  <img src="https://github.com/user-attachments/assets/56a40d4a-a109-46be-b57f-8664a6184009" alt="Boss Fight Diagram" width="700"/>
</p>

---

### Shop Screen
- Displays 6 shop items, including visuals and descriptions (final details pending)

<p align="center">
  <img src="https://github.com/user-attachments/assets/9533f0f6-0dd4-4807-95ca-6befc6fe0c18" alt="Shop Screen Diagram" width="700"/>
</p>

---

### Inventory Loadout
- Shows items currently owned (earned or purchased)  
- Displays equipped items and allows swapping

<p align="center">
  <img src="https://github.com/user-attachments/assets/d354d00b-f125-4c1d-ae36-1a3b2b070b14" alt="Inventory Loadout Diagram" width="700"/>
</p>

---

## Installation/usage instructions
- download and run raylib
- clone this repository into vscode
- click open any files in repository and press f5

---

## Project testing/validating
- not only did we do unit tests, we played through the game
- we played through the game every time we made a change 

---

## UML Diagram
- **UML:** [View UML in draw.io](https://app.diagrams.net/#G1euJCQomQhLoey8pglOfzLNkVippZvsMd#%7B%22pageId%22%3A%22oiYqd9vRAGfTHePaKK0A%22%7D)
  
<p align="center">
  <img src="https://github.com/user-attachments/assets/275f8565-2e8a-4bec-8488-40a50249acfc" alt="UML Diagram" width="700"/>
</p>

## SOLID Principle Description
### Single Responsibility Principle
* All the functions within Fruit, Boss, Player, Item, and Status have the single responsibility principle in mind.
* We need to edit Game and UI with this principle in mind.

### Open/Closed Principle
* When resetting status and cycling through items we don’t have specific implementation for each item

### Liskov Substitution 
* Fruit class implemented in Game.cpp uses Fruit*. Inputting Boss* and Player* into a Fruit* does not break the code.

### Interface segregation
* We created a UI class for all user interface
* All classes the output use UI

### Dependency Inversion
* Shop purchaseItem() function relies on abstraction of the Fruit class
* This way it can take either Player or Boss items


## UML Class Descriptions

<details>
  <summary>
    <strong>
      Fruit
    </strong>
  </summary>
	
* `checkIfCrit(): bool`
	* Compares a randomly generated integer between 1 and 100 (inclusive) and compares it 
	to the Fruit’s CRIT Rate. If RNG int <= CRIT Rate, then returns true. Otherwise, false.
* `removeStats(Status*): void`
	* Removes, from Fruit, the bonuses of the Status that is passed in. Typically when a buff expires. Accounts for both flat and percentage-based changes.
* `addStats(Status*): void`
	* Applies, unto Fruit, the bonuses of the Status that is passed in.
* `clearStats(): void`
	* Called by clearStatus() and levelUp(). Removes any bonuses given by any Statuses.
* `reAddStats(): void`
	* Called by levelUp(). Goes through every Status and adds the bonuses it provides to Fruit
* `clearEffectsVector(): void`
	* Clears the effect vector and deletes any effects not linked to items
* `basicAttack(target: Fruit*): string`
	* Deals damage to the target based on the attacker’s attack and the target’s defense
* `specialAttack(target: Fruit*): string`
	* virtual
* `addEffect(effect: Status*): void`
	* Adds effect to the effects vector 
* `isDead(): bool` 
	* Checks if the fruit is dead
* `endOfTurn(): void`
	* Checks if effects to see if duration ran out, updates hp effects, recharges, and decreases turn
* `clearStatus(): void`
</details>


<details>
  <summary>
    <strong>
      Boss
    </strong>
  </summary>

* `specialAttack(target: Fruit*): string`
	* Implemented a special attack with features based on the boss who implemented it.
* `bossAbility(): string`
	* Unique ability of a boss
* `endOfTurn(): void`
	* Same as fruit but bossCharge increments.
</details>


<details>
  <summary>
    <strong>
      Game
    </strong>
  </summary>
	
* `startGame(int): void`
* `gameLoop(): void`
* `loadInterlude(): void`
* `loadEndOfGame(): void`
* `loadLose(): void`
* `saveGame(): void`
* `battleLoop(Boss*): int`
* `playerTurn(Boss*): void`
* `enemyTurn(Boss*): void`
* `checkBuyItem(int): string`
* `resetGame(): void`
* `uiDraw(): void`
* `runGame(): void`
* `openFile(string): void`
</details>


<details>
  <summary>
    <strong>
      IScreen
    </strong>
  </summary>
	
* `Update(Vector2&, bool): void`
	* Abstract method that serves as a skeleton for implementations Screen’s updates
* `Draw(): void`
	* Abstract method that serves as a skeleton for drawing in Screens
</details>


<details>
  <summary>
    <strong>
      ScreenManager
    </strong>
  </summary>
	
* `PushScreen(unique_ptr<IScreen>): void`
	* Pushes 1 IScreen on top of the existing stack, a pause of sorts, the screen underneath still exists
* `ChangeScreen(unique_ptr<IScreen>): void`
	* Completely replace whatever was on the stack with a new screen, clearing the vector and pushing 1 IScreen
* `Update(Vector2&, bool): void`
	* On each frame, call update on the topmost screen
* `Draw(): void`
	* On each frame, call draw on the topmost screen
* `PopScreen(): void`
	* Removes the topmost screen from the stack
</details>


<details>
  <summary>
    <strong>
      Shop
    </strong>
  </summary>
	
* `purchaseItem(player: Fruit, itemIndex: int): void` 
	* Adds an item from the vector of shop items to the player.
* `resetShop(): void` 
	* Clears the shop and then repopulates it.
* `saveShop(): void`
	* Saves the shop into a save text file. The contents of the text file are all of the items that have not shown up yet.
* `populateShop(): void`
	* Selects an item at random, then uses an RNG to determine if that selected item will
	appear in the shop. Do this until there are 6 items.
</details>


<details>
  <summary>
    <strong>
      Item
    </strong>
  </summary>
	
* `use(target: Fruit*): void` 
	* Adds the corresponding effect linked to the item to the Fruit.
* `decreaseCooldown(): void`
	* Decrease the cooldown of the item by 11.
* `isConsumableTrue(): bool`
	* Returns true if the item is a consumable item. False otherwise.
* `isUseOnPlayer(): bool`
	* Returns true if the item is supposed to be used on the player, false if the item is
	supposed to be used on a boss enemy.
</details>


<details>
  <summary>
    <strong>
      Status
    </strong>
  </summary>
	
* `decreaseTurn(): void` 
	* Decreases turn by 1.
* `resetStatusTurns(): void`
	* Sets turns equal to the default turns to ensure the status continues to be in effect.
* `isDeleteThisStatus(): bool`
	*Used to determine when Fruit is clearing effects, what statuses to remove (such as DoT)
* `isPercentBased(): bool`
	*Returns true if the status is percent-based. False otherwise.
</details>


<details>
  <summary>
    <strong>
      Player
    </strong>
  </summary>
	 
* `specialAttack(target: Fruit*): string`
* Implementation. Uses both attack and arts, minus target defense and res to deal damage to the target
* `useItem(Fruit*, unsigned): string`
* `savePlayer(): void`
* `unequipItem(unsigned): void`
* `equipItem(unsigned): void`
* `newItem(Item*): void`
	* Adds a new item to the inventory
</details>


 <details>
  <summary>
    <strong>
      Stat
    </strong>
  </summary>
	
* `add(int): void`
* `removeAdd(): void`
* `addBase(int): void`
</details>

### UNIT TESTS
![image](https://github.com/user-attachments/assets/46a1b487-41d7-4563-b045-fcd6c05be155)
![image](https://github.com/user-attachments/assets/b8d5339e-733f-4971-8676-1002abbddbb5)
![image](https://github.com/user-attachments/assets/6df8a15c-8f70-4456-8b25-968fb089fb77)
![image](https://github.com/user-attachments/assets/47621a86-4124-40e0-b8de-0088626cc64f)


