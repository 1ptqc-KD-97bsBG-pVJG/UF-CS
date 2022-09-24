import time

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

# After the card is dealt, print the menu to the screen. The menu should look like this: 
# 1. Get another card 
# 2. Hold hand 
# 3. Print statistics 
# 4. Exit 

# If  the  player  has  a  hand  of  21,  they 
# automatically win and “BLACKJACK! You win!” is printed; then a new game is started. If the player’s hand 
# exceeds 21, the dealer automatically wins; print, "You exceeded 21! You lose.”, then start a new game. 
 
# If the player chooses option 3, you will print the statistics of the game. Throughout your program you will need 
# to keep track of the number of games played, the player’s number of wins, the dealer's’ number of wins and the 
# number of ties. Print out all these values as well as the percentage of player wins to the total number games played. 
# Format your percentage value to one decimal point. See sample output for format. 
 
# If option 4 is selected, exit the program. 
 
# If any other input is entered, print the following text: 
 
# Invalid input! 
# Please enter an integer value between 1 and 4. 
 
# Then redisplay the menu. You can assume that the input will be numeric for this project (but not future projects.) 

from p1_random import P1Random



def main():
    def get_card():
        user_cards.append(P1Random().next_int(13) + 1)
        print(f'Your card is a {get_card_name(user_cards[-1])}!')
        print(f'Your hand is: {get_deck_value(user_cards)}')
        
    def get_card_name(card):
        if card == 1:
            return "Ace"
        elif card == 11:
            return "Jack"
        elif card == 12:
            return "Queen"
        elif card == 13:
            return "King"
        else:
            return str(card)
    
    def get_deck_value(deck):
        value = 0
        for card in deck:
            if card == 1:
                value += 1
            elif card > 10:
                value += 10
            else:
                value += card
        return value

    def print_menu():
        print("1. Get another card")
        print("2. Hold hand")
        print("3. Print statistics")
        print("4. Exit")

    user_cards = []
    dealer_value = 0

    game_continue = True
    game_num = 0

    while game_continue:
        game_num += 1
        print(f'START GAME #{game_num}')
        dealer_value = P1Random().next_int(11) + 16
        time.sleep(1)

        get_card()
        print_menu()
        selection = input(f'Choose an option:')
        
        if selection == '1':
            get_card()
            print_menu()
        elif selection == '2':
            print(f'Dealer\'s hand: {dealer_value}')
            print(f'Your hand is: {get_deck_value(user_cards)}')
            if get_deck_value(user_cards) > dealer_value:
                print('You win!')
            elif get_deck_value(user_cards) == dealer_value:
                print('It\'s a tie! No one wins!')
            else:
                print('Dealer wins!')
            continue
        elif selection == '3':
            # Number of Player wins: 2
            # Number of Dealer wins: 2
            # Number of tie games: 1
            # Total # of games played is: 5
            # Percentage of Player wins: 40.0
            continue
        
        game_continue = False



main()