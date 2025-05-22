# Fruit RPG

Authors: [Annie Le](https://github.com/anniele2006), [Brandon Hatamoto](https://github.com/BananazrCRAZY), [Eva Bao](https://github.com/evabao007), [Sebastian Chou](https://github.com/stricker1)

## Project Description
Important/Interesting:
* We are able to combine elements of storytelling, game design, and OOP into a personally loved project. We want to be able to think like programmers and game designers, taking into account the compelling narrative and a smoother gameplay, for our users!

### Languages/Tools/Technologies:
* C++
* VSCode
* Github
* qt GUI

## Input/Output of Project:
* Keyboard input, terminal output
* Optional: User .txt file input for character files, and option to output their character information to a .txt file as well

#### Example of `.txt` file format (will be updated as we progress):
```
user_name: Annie
lv: 18
class: mage
cals: 19000
m_hp: 126
hp: 350
progress: 12
```

## Features:
* Option to save character and continue gameplay from where it is saved
* Preset decisions and consequences that the player chooses
* Turn based battle system

## Navigation Diagram  
<p align="center"><img src="https://github.com/user-attachments/assets/d8d62409-2685-4d92-b59b-edddf6708117" alt="User Navigation Diagram" width = "700"</p>

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

### Prologue / Epilogue
- Tells the story of Orange being bullied by the different Fruit Bosses  
- **Next** – Prompts a shift into a Tutorial Boss Fight  

<p align="center">
  <img src="https://github.com/user-attachments/assets/b13360dc-8f08-466c-8615-1d468484b6b5" alt="Prologue Diagram 1" width="700"/>
  <img src="https://github.com/user-attachments/assets/25559367-a38f-492b-b05f-c661c68d9f39" alt="Prologue Diagram 2" width="700"/>
</p>

---

### Tutorial Boss Fight
- General layout for all boss fights (template)  
- Players have two turn-based options:
  - **Basic Attack** – Requires no skill points  
  - **Skill Attack** – Choose 1 of 2, each requires same number of skill points  

<p align="center">
  <img src="https://github.com/user-attachments/assets/bced573f-70ff-42c2-989f-a9dc62a3fb72" alt="Boss Fight Diagram" width="700"/>
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


## UML Diagram
<p align="center">
  <img src="https://github.com/user-attachments/assets/85e9e2dc-d1e9-40ed-9839-9b41ca72efe2" alt="UML Diagram" width="700"/>
</p>

## UML Class Descriptions

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

## Compositions and Aggregation
  * Item
    * Boss comp
    * Player aggregation
  * Status 
    * Fruit aggregation
    * Item comp
  * Player
    * Fruit inherit
    * Game comp
  * Boss
    * Fruit inherit
  * Shop
    * Game comp
    * Item comp
