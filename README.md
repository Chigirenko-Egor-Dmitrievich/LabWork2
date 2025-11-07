# LabWork 2
## Author
Чигиренко Егор Дмитриевич, группа: 24.Б81-мм

## Contacts
st128240@student.spbu.ru

## Description
Terminal-based C++ implementation of the TellStones game using Object-Oriented Programming.  
Players interact with a 3×3 board, draw stones from a deck, and use actions such as flip, swap, peek, challenge, brag, or give up.  
The first player to reach 5 points wins. Special stones (Crown, Rune, Dragon) have immediate effects when placed.  
There is no AI-Bot implementation.  
There is also no basics diagrams.

## Build
make

## Tests' dependencies
sudo apt-get install -y g++ make libgtest-dev libgmock-dev

## Run
./run  
./run_tests

## Clean
make clean  
make cleanall
