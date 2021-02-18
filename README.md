# Tic-tac-toe
## Purpose
The objective is to create a game that plays Tic-tac-toe optimally against the player no matter if the player starts first or second.

[Tic-tac-toe Wikipedia](https://en.wikipedia.org/wiki/Tic-tac-toe)

## Rules
- The player can choose if he starts first or second.
- The game should display the current state.
- The game should display who is the winner.
- The program should play optimally against the opponent.

## About the program
The program uses the algorithm **Min-Max** with **Alpha-Beta pruning** to play the game. When the game is started the user chooses if he wants to play first or second. According to that the program adapts and chooses the best move.

### To run the program
- Build it using `make`
- Run `./main`

### Output
- Initially the program asks the user if he wants to start first.
- Displays current state.
- Displays who won the game or 'Draw' in case of draw.

### Output - initial
![Output-initial](https://github.com/luntropy/tic-tac-toe/blob/main/images/output-initial.png)

### Output - current state - part 1
![Output-current-state-1](https://github.com/luntropy/tic-tac-toe/blob/main/images/output-current-state-1.png)

### Output - current state - part 2
![Output-current-state-2](https://github.com/luntropy/tic-tac-toe/blob/main/images/output-current-state-2.png)

### Output when the AI won
![Output-AI-won](https://github.com/luntropy/tic-tac-toe/blob/main/images/finished-game-example-ai-won.png)

### Output - draw
![Output-Draw](https://github.com/luntropy/tic-tac-toe/blob/main/images/finished-game-example-draw.png)
