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
* Ex of a .txt file input/output:
   * Annie (name)
   * 18 (level)
   * Mage (class: type)
   * 19000 (gold)
   * 126 (hp)
   * 350 (max hp)
   * 12 (breakpoint to mark progress through game)

## Features:
* Option to save character and continue gameplay from where it is saved
* Preset decisions and consequences that the player chooses
* Turn based battle system

# Phase 2
## User Interface Specification: 
* Navigation Diagram:
* Screen Layout: https://docs.google.com/presentation/d/113KIpqxjZn-ZylGX6MBx2rM3WvERidij8RLd5BcQcd8/edit?usp=sharing
* Screen Layout Description:
  * Title Screen: has three options, with “New Game” - prompts to Orange Creation screen, “Load” - prompts user to pick a save file, and “Quit”, which exits out of the UI
  * Orange Creation: prompts user to enter name, and “Next” which would go into story mode
  * Load: Prompts user to pick one out of 3 save files
  * Prologue/Epilogue: Tells story of Orange being bullied by the different Fruit Bosses, with “Next” prompting a shift into a “Tutorial Boss fight”
  * Tutorial Boss Fight: general layout of all boss fights, just cut and insert specific boss. Players have option on a turn-based system of 2 types of attacks, a basic attack (requires no skill points charge_, or a skill attack (pick one of 2, either requires the same # of skill points)
  * Shop Screen: Displays 6 shop items and their visuals + descriptions (will be finalized later)
## UML Diagram
* UML Diagram: https://drive.google.com/file/d/1euJCQomQhLoey8pglOfzLNkVippZvsMd/view?usp=sharing
## UML Class Descriptions
Game
  * - saveFile: string
    * Txt file name the contains game save data
  * - savePoint: int
    * This will indicate where the player is in the story
  * - calories: int
    * Currency 
  * - player: Player
    * Created at initialization of game
  * - shop: Shop
    * Created at initialization of game
  * + loadGame(saveFile): void
    * Creates all the objects and initiates all the necessary data
  * + loadStartMenu(): void
    * Create UI for the start screen (first screen)
  * + loadBattle(): void
    * Create UI for battle screen
    * Has buttons for player action
  * + playerTurn(): void
    * Used within battle
    * Allows for the player to choose action
    * Use button as input
  * + enemyTurn(): void
    * Displays dialogue for their action
  * + turnReset(): void
    * End of battle loop
    * Resets turn
    * Updates statuses 
  * + loadDialogue(file: string): void
    * Opens file
    * Reads in each character one at a time for rolling text
    * For story scenes
  * + loadShop(): void
    * Displays UI for shop
  * + saveGame(): void
    * Calls savePlayer(), saveShop()
    * Save data into saveFile
    * ofstream
   
  
Shop 
  * - itemFile: string
    * Name of file that contains all available items that can be in the shop
    * The items in itemsForSale vector
  * - allItem: vector<items>
    * Loads all the available items into a vector
  * - itemsForSale: vector<item>
    * Randomly selects items within the allItems vector to be put on sale
    * 6 items
  * + purchaseItem(player: Player, item: int): void
    * Item: int is for vector item location, will be determined by item selected which will be a button
    * Add the item to player’s items
    * Removes item from allItems and itemsForSale
  * + saveShop(): void

Fruit
  * - fileName: string
  * - name: string
  * - Level: int 
    * tied to hp, attack, def, arts, res, for bosses it’s levels that they give you
  * - hp: int 
  * - baseMaxHp: int 
  * - baseAttack: int 
  * - baseDefense: int 
  * - baseCitrusArts: int 
  * - baseCitrusRes: int 
  * - baseCritRate: int 
  * - baseCritDmg: double 
  * - maxHpAdd: int 
  * - attackAdd: int 
  * - defenseAdd: int 
    * extra stats added in by items, ex: setDefenseAdd() adds to this data type, not baseDefense
  * - citrusArtsAdd: int 
  * - citrusResAdd: int 
  * - CritRateAdd: int 
  * - CritDmgAdd: double
  * - rechargeCount: int
    * For special attack
    * For items too (for player)
  * - turn: int
    * Decreases after the fruit goes
    * Resets after turn cycle in battle loop
  * - effects: vector<Status*>
  * + basicAttack(target: Fruit): void
    * Add to rechargeCount
  * + specialAttack(target: Fruit): boolean 
    * Returns if there was enough recharge to do attack
    * Reduces rechargeCount
  * + getMaxHp(): int 
  * + getHp(): int + getDefense(): int 
  * + getCitrusArts(): int 
  * + getCitrusRes(): int 
  * + getCritRate(): int 
  * + getCritDmg(): int 
  * + getRechargeCount(): int 
  * + getTurn(): int 
  * + setMaxHpAdd(change: int): void 
  * + setHpAdd(change: int): void 
  * + setDefenseAdd(change: int): void 
  * + setCitrusArtsAdd(change: int): void 
  * + setCitrusResAdd(change: int): void 
  * + setCritRateAdd(change: int): void 
  * + setCritDmgAdd(change: double): void 
  * + setRechargeCount(change: int): void 
  * + setTurn(change: int): void
  * + addEffect(effect: Status): void
  * + endOfTurn(): void
    * Update effects
    * Not turn charge, rechargeCount


Player 
  * - items: vector<item>
  * - battleItems: vector<Item>
    * Equipped items that can be used during battle
    * Limit is 6
  * + basicAttack(target: Fruit): void
    * Does instance of attack and citrus arts
  * + specialAttack(target: Fruit): boolean
    * Does concentrated instance of attack or citrus arts
  * + useItem(target: Fruit, item: int): boolean
    * Can only use items that are consumables
  * + endOfTurn(): void
    * Needs to go through items and remove items w/ 0 uses left
    * Goes through status to update
  * + savePlayer(): void
  
Boss 
  * - itemDrop: Item 
  * - bossAttackCharge: int
    * Unique boss attack that happens every <> turn
  * + basicAttack(target: Fruit): void 
    * Bosses’ basic attack (different stats for every boss)
  * + specialAttack(target: Fruit): void
    * Bosses’ special attack, can apply debuff (Status class) onto player, takes # of charges
  * + getBossAttackCharge(): int 
  * + setBossAttackCharge(change: int): int 
  * + endOfTurn(): void
  
Item
  * - name: string
  * - description: string
  * - cost: int
  * - consumable: boolean
  * - uses: int
    * Doesn’t matter if not consumable
    * Set -1
  * - cooldownDefault: int
  * - cooldown: int 
    * Updates after each turn
  * - effect: Status*
  * - showProbability: int 
    * Random number between 0-99
    * For having probability variability for items that show in shop, example: we have 3 items total but we want item[0] to have a showing probability of 25% so we set showProbability to ⅔. The equation is show% = 1/(total items) * showProbabilitytotalProbabilities + 1/(total items) * showProbability = 1/3 * 2/31/3 + 1/3 + 1/3 * 2/3 = 25% while the other items have 75/2%. Here for spreadsheet
  * + use(target: Fruit): void
  * + setCooldown(change: int): void
    * Will be used in Player.endOfTurn()

Status
  * - name: string
  * - description: string
  * - defaultTurns: int
  * - turns: int
  * - hpChange: double 
  * - maxHpChange: double
  * - attackChange: double 
  * - defenseChange: double 
  * - citrusArtsChange: double 
  * - citrusResChange: double
  * - critRateChange: int 
  * - critDmgChange: double
  * - rechargeCountChange: int
  * - turnChange: int
  * + decreaseTurn(): void
  * + resetStatus(): void
    * Changes turns = defaultTurns

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


