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
- clone this repository into vscode
- click open any files in repository and press f5

---

## Project testing/validating
- not only did we do unit tests, we played through the game
- we played through the game every time we made a change 

---

## UML Diagram
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


## UML Class Descriptions (work in progress)

<details>
  <summary>
    <strong>
      Game
    </strong>
  </summary>
  
  * `saveFile: string`
    * Name of the '.txt' file that contains the game save data
  * `savePoint: int`
    * Indicates the chapter the player is in during the story
  * `calories: int`
    * In-game currency
  * `player: Player`
    * Created during game initialization

  **Methods:**
  * `loadGame(saveFile): void`
    * Creates and initializes all necessary data from `saveFile`
  * `loadStartMenu(): void`
    * Creates UI for the Home screen
  * `loadBattle(): void`
    * Creates UI for the Battle screen
    * Has buttons for player actions
  * `playerTurn(): void`
    * Is used within battle
    * Allows for the player to choose their action
    * Uses on-screen button as input
  * `enemyTurn(): void`
    * Displays dialogue for their action
  * `turnReset(): void`
    * End of battle loop
    * Resets turn
    * Updates statuses
  * `loadDialogue(file: string): void`
    * Opens `file`
    * Reads in each character one at a time for rolling text
    * Used for story scenes
  * `loadShop(): void`
    * Displays UI for the Shop
  * `saveGame(): void`
    * Calls `savePlayer()` and `saveShop()`
    * Saves data into `saveFile.txt`
    * `ofstream`
</details>

<details>
  <summary>
    <strong>
      Shop
    </strong>
  </summary>

  * `itemsFile: string`
    * Name of the file that contains all available items that can be in the shop
    * All items are in `itemsForSale` vector
  * `allItems: vector<item>`
    * Vector of every possible `item`s available to purchase in the shop
  * `itemsForSale: vector<item>`
    * Randomly selected list of `item`s within `allITems` to be put for sale in the shop
    * 6 `item`s
   
  **Methods:**
  * `loadAllItems(): void`
    * Loads all the available items into a vector
  * `purchaseItem(player: Player, item: int): void`
    * `item: int` is for a vector item location; will be determined by the `item` selected which will be a button
    * Adds the `item` to the `player`'s `item`s
    * Removes `item` from `allItems` and `itemsForSale`
  * `saveShop(): void`
</details>

<details>
  <summary>
    <strong>
      Fruit
    </strong>
  </summary>

  * `fileName: string`
  * `name: string`
  * `level: int`
    * tied to `hp`, `attack`, `def`, `arts`, `res,` for bosses
  * `hp: int`
  * `baseMaxHp: int`
  * `baseAttack: int`
  * `baseDefense: int`
  * `baseArts: int`
  * `baseRes: int`
  * `baseCritRate: double`
  * `baseCritDmg: double`
  * `maxHpAdd: int`
  * `attackAdd: int`
  * `defenseAdd: int`
  * `artsAdd: int`
  * `resAdd: int`
  * `critRateAdd: double`
  * `critDmgAdd: double`
  * `rechargeCount: int`
    * For special attack and items for the player
  * `turn: int`
    * Decreases after the player acts
    * Resets after each turn cycle in the battle loop
  * `effects: vector<Status*>`

  **Methods:**
  * `basicAttack(target: Fruit): void`
    * Increments `rechargeCount` by 1
  * `specialAttack(target: Fruit): bool`
    * Returns `true` or `false` based on whether or not there was enough `recharge` to do the special attack
    * Decrements `rechargeCount` by 1
  * `getMaxHp(): int`
  * `getHp(): int`
  * `getDefense(): int`
  * `getArts(): int`
  * `getRes(): int`
  * `getCritRate(): double`
  * `getCritDmg(): double`
  * `getRechargeCount(): int`
  * `getTurn(): int`
  * `setMaxHpAdd(change: int): void`
  * `setHpAdd(change: int): void`
  * `setDefenseAdd(change: int): void`
  * `setArtsAdd(change: int): void`
  * `setResAdd(change: int): void`
  * `setCritRateAdd(change: int): void`
  * `setCritDmgAdd(change: double): void`
  * `setRechargeAccount(change: int): void`
  * `setTurn(change: int): void`
  * `addEffect(effect: Status): void`
  * `endOfTurn(): void`
    * Updates `effects`
    * Not turn charge, rechargeCount
    
</details>

<details>
  <summary>
    <strong>
      Player
    </strong>
  </summary>

  * `items: vector<Item>`
  * `battleItems: vector<Item>`
    * Equipped `item`s that can be used during battle
    * Limited to a maximum of 6

  **Methods:**
  * `basicAttack(target: Fruit): void`
    * Deals an instance of both physical and arts damage
  * `specialAttack(target: Fruit): bool`
    * Deals a concentrated instance of either physical or arts damage
  * `useItem(target: Fruit, item: int): bool`
    * Can only use consumable items
  * `endOfTurn(): void`
    * Needs to go through `items` and remove `item`s with 0 uses left
    * Goes through status to update
  * `savePlayer(): void`
</details>

<details>
  <summary>
    <strong>
      Boss
    </strong>
  </summary>

  * `itemDrop: Item`
  * `bossAttackCharge: int`
    * Unique boss attack that happens after every certain amount of turns
   
  **Methods:**
  * `basicAttack(target: Fruit): void`
    * Bosses' basic attack (different stats for every boss)
  * `specialAttack(target: Fruit): void`
    * Bosses' special attack
    * Can apply debuffs (a `Status`) onto the player, takes a certain amount of `charge`
  * `getBossAttackCharge(): int`
  * `setBossAttackCharge(change: int`
  * `endOfTurn(): void`
</details>

<details>
  <summary>
    <strong>
      Item
    </strong>
  </summary>

  * `name: string`
  * `description: string`
  * `cost: int`
  * `consumable: bool`
  * `uses: int`
    * Doesn't have to be a consumable `item`
    * Set -1
  * `cooldownDefault: int`
  * `cooldown: int`
    * Updates after each turn
  * `effect: Status*`
  * `showProbability: int`
    * Random number between 0-99
    * For having probability variability for items that show in the shope.
    * <details>
      <summary>
        Example
      </summary>
      
      We have 3 items total, but we want `item[0]` to have a probability of appearing in the shop of 25%. So, we set `showProbability` to $\frac{2}{3}$. The equation is:

      ![image](https://github.com/user-attachments/assets/1e9597a1-5480-4864-9dc4-c518efbba42e)


      </details>
      
  **Methods:**
  * `use(target: Fruit): void`
  * `setCooldown(change: int): void`
    * Will be used in `Player.endOfTurn()`
</details>


<details>
  <summary>
    <strong>
      Status
    </strong>
  </summary>
  
  * `name: string`
  * `description: string`
  * `defaultTurns: int`
  * `turns: int`
  * `hpChange: double`
  * `maxHpChange: edouble`
  * `attackChange: double`
  * `defenseChange: double`
  * `artsChange: double`
  * `resChange: double`
  * `critRateChange: double`
  * `critDmgChange: double`
  * `rechargeCountChange: int`
  * `turnChange: int`

  **Methods:**
  * `decreaseTurn(): void`
  * `resetStatus(): void`
    * Changes turns = `defaultTurns`
</details>

Status
+ decreaseTurn(): void 
	decrease
+ resetStatusTurns(): void
+ isDeleteThisStatus(): bool
+ isPercentBased(): bool

