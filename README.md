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

## User Interface Specification: 
* Navigation Diagram:
* Screen Layout: https://docs.google.com/presentation/d/113KIpqxjZn-ZylGX6MBx2rM3WvERidij8RLd5BcQcd8/edit?usp=sharing
* Screen Layout Description:
  * Title Screen: has three options, with “New Game” - prompts to Orange Creation screen, “Load” - prompts user to pick a save file, and “Quit”, which exits out of the UI
  <p align="center">
  <img src="https://github.com/user-attachments/assets/d25c9881-e3ee-4996-9ca8-7050b0adc859" alt="diagram" width="700"/>
  </p>
  * Orange Creation: prompts user to enter name, and “Next” which would go into story mode
  <p align="center">
  <img src="https://github.com/user-attachments/assets/67d99450-23dc-4008-b240-787e83978087" alt="diagram" width="700"/>
  </p>
  * Load: Prompts user to pick one out of 3 save files
  <p align="center">
  <img src="https://github.com/user-attachments/assets/cb4d35de-4223-4fb8-b763-8def18832c31" alt="diagram" width="700"/>
  </p>
  * Prologue/Epilogue: Tells story of Orange being bullied by the different Fruit Bosses, with “Next” prompting a shift into a “Tutorial Boss fight”
  <p align="center">
  <img src="https://github.com/user-attachments/assets/b13360dc-8f08-466c-8615-1d468484b6b5" alt="diagram" width="700"/>
  <img src="https://github.com/user-attachments/assets/25559367-a38f-492b-b05f-c661c68d9f39" alt="diagram" width="700"/>
  </p>
  * Tutorial Boss Fight: general layout of all boss fights, just cut and insert specific boss. Players have option on a turn-based system of 2 types of attacks, a basic attack (requires no skill points charge_, or a skill attack (pick one of 2, either requires the same # of skill points)
  <p align="center">
  <img src="https://github.com/user-attachments/assets/bced573f-70ff-42c2-989f-a9dc62a3fb72" alt="diagram" width="700"/>
  </p>
  * Shop Screen: Displays 6 shop items and their visuals + descriptions (will be finalized later)
  <p align="center">
  <img src="https://github.com/user-attachments/assets/9533f0f6-0dd4-4807-95ca-6befc6fe0c18" alt="diagram" width="700"/>
  </p>
  * Inventory Loadout: Displays current items in inventory (that were bought from the shop/earned in boss fights) and current items equipped, available to swap them out
  <p align="center">
  <img src="https://github.com/user-attachments/assets/d354d00b-f125-4c1d-ae36-1a3b2b070b14" alt="diagram" width="700"/>
  </p>


## UML Diagram
* UML Diagram: https://drive.google.com/file/d/1euJCQomQhLoey8pglOfzLNkVippZvsMd/view?usp=sharing
## UML Class Descriptions
* Class Descriptions: https://docs.google.com/document/d/1DtSvtzcY8Od5k7YifmCQHc-F2pDksYqDAzuY5ZFx3sw/edit?tab=t.0
