# A typical game will play out as follows: 

# The player will be dealt one card at the start of the game (where a game is one round of play). The player, based 
# on the value of their cards, can either ask for another card (a hit) or choose to hold (stand). The dealer will then 
# begin their turn and try to beat the player’s hand. The player is competing against the dealer, who has their own 
# hand. Whomever is closer to 21 at the end of the game (as long as they don’t exceed 21) wins the game. 
 
# 1. Player’s turn: Player tries to reach or come close to 21 without going over (as 21 is the highest hand). 
# 2. Dealer’s turn: Dealer tries to beat exceed the player’s hand without going over 21. 
# 3. Determine the winner at the end of the game and increment the win count. 
# 4. Repeat! 
 
# You will need a while loop in your program. The loop will allow you to play successive games without restarting 
# the program each time; it will also allow you to keep a win count over multiple games.


from p1_random import P1Random

rng = P1Random()

card = rng.next_int(13) + 1
print(card)

game_continue = True
game_num = 0

while game_continue:
    #1. set up inital message
    game_num += 1
    print(f'START GAME #{game_num}')