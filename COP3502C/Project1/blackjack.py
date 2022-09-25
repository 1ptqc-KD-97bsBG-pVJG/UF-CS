from p1_random import P1Random
import time



def main():
    user_cards = []
    global game_continue
    game_continue = True
    games = []
    rng = P1Random()

    def get_card():
        # time.sleep(.3)
        deez = rng.next_int(13) + 1
        user_cards.append(deez)
        if get_deck_value(user_cards) > 21:
            print('You exceeded 21! You lose.')
            games.append('dealer')
            return False
        elif get_deck_value(user_cards) == 21:
            print('BLACKJACK! You win!')
            games.append('user')
            return False
        else:
            print(f'Your card is a {get_card_name(user_cards[-1])}!')
            print(f'Your hand is: {get_deck_value(user_cards)}')
            return True
        
    def get_card_name(card):
        if card == 1:
            return 'ACE'
        elif card == 11:
            return 'JACK'
        elif card == 12:
            return 'QUEEN'
        elif card == 13:
            return 'KING'
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

    def menu():
        # time.sleep(.3)
        print('1. Get another card')
        print('2. Hold hand')
        print('3. Print statistics')
        print('4. Exit')
        selection = input('Choose an option: ')
        if selection == '1':
            if get_card():
                menu()
        elif selection == '2':
            print(f'Dealer\'s hand: {dealer_value}')
            print(f'Your hand is: {get_deck_value(user_cards)}')
            if get_deck_value(user_cards) > dealer_value:
                print('You win!')
                games.append('user')
            elif get_deck_value(user_cards) == dealer_value:
                print('It\'s a tie! No one wins!')
                games.append('tie')
            else:
                print('Dealer wins!')
                games.append('dealer')
        elif selection == '3':
            print(f'Number of Player wins: {games.count("user")}')
            print(f'Number of Dealer wins: {games.count("dealer")}')
            print(f'Numberof tie games: {games.count("tie")}')
            print(f'Total # of games played is: {len(games)}')
            print(f'Percentage of Player wins: {games.count("user") / len(games)}')
            menu()
        elif selection in ('4', 'exit'):
            global game_continue
            game_continue = False
        else:
            print('Invalid input!\nPlease enter an integer value between 1 and 4.')
            menu()

    while game_continue:
        print(f'START GAME #{len(games) + 1}')
        user_cards = []
        dealer_value = rng.next_int(11) + 16
        print(f'DEALER DEEZ NUTS: {dealer_value}')
        # time.sleep(1)

        get_card()
        menu()
        
    
if __name__ == '__main__':
    main()