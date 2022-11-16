import pakuri
import pakudex

def main():
    print("Welcome to Pakudex: Tracker Extraordinaire!")
    

    # ensure inputted capacity is valid, if not ask again
    is_repeat = True
    while is_repeat:
        try:
           capacity = int(input("Enter max capacity of the Pakudex: "))
           if capacity < 0:
                raise ValueError
           is_repeat = False
        except:
            print('Please enter a valid size.')
    
    print(f'The Pakudex can hold {capacity} species of Pakuri.')

    # create Pakudex object
    collection = pakudex.pakudex(capacity)


    # main menu function
    def do_menu():
        print(f'\nPakudex Main Menu')
        print('-' * 17 )
        print('1. List Pakuri')
        print('2. Show Pakuri')
        print('3. Add Pakuri')
        print('4. Evolve Pakuri')
        print('5. Sort Pakuri')
        print('6. Exit')

        user_selection = input(f'\nWhat would you like to do? ').lower()

        if user_selection in ('1', 'list'):
            # check if Pakudex is empty
            if collection.get_size() > 0:
                print('Pakuri In Pakudex:')
                # iterate through species_array and print each species
                for i, species in enumerate(collection.get_species_array()):
                    print(f'{i + 1}. {species}')
            else:
                print('No Pakuri in Pakudex yet!')
        elif user_selection in ('2', 'show'):
            user_selection = input('Enter the name of the species to display: ')
            # if species is in Pakudex, print stats
            try:
                # select Pakuri object by getting index of the user input in species_array, then getting that object from collection
                selected_pakuri = collection.species_array[collection.get_species_array().index(user_selection)]
                print(f'\nSpecies: {selected_pakuri.get_species()}')
                print(f'Attack: {selected_pakuri.get_attack()}')
                print(f'Defense: {selected_pakuri.get_defense()}')
                print(f'Speed: {selected_pakuri.get_speed()}')
            except:
                print('Error: No such Pakuri!')
        elif user_selection in ('3', 'add'):
            # check if Pakudex is below capacity
            if collection.get_size() < collection.get_capacity():
                user_species = input('Enter the name of the species to add: ')
                # check if array not empty and if species already exists
                if collection.get_size() > 0 and user_species in collection.get_species_array():
                    print('Error: Pakudex already contains this species!')
                else:
                    collection.add_pakuri(user_species)
                    print(f'Pakuri species {user_species} successfully added!')
            else:
                print('Error: Pakudex is full!')
        elif user_selection in ('4', 'evolve'):
            user_selection = input('Enter the name of the species to evolve: ')
            try:
                # select Pakuri object by getting index of the user input in species_array, then getting that object from collection
                selected_pakuri = collection.species_array[collection.get_species_array().index(user_selection)]
                # call evolve_species method on collection object and pass in selected Pakuri object
                collection.evolve_species(selected_pakuri)
                print(f'{selected_pakuri.get_species()} has evolved!')
            except:
                print('Error: No such Pakuri!')
        elif user_selection in ('5', 'sort'):
            # sort Pakuri objects in species_array
            collection.sort_pakuri()
            print('Pakuri have been sorted!')
        elif user_selection in ('6', 'exit'):
            print('Thanks for using Pakudex! Bye!')
            quit()
        else:
            print('Unrecognized menu selection!')
        # repeat menu
        do_menu()

    # inital menu call
    do_menu()


if __name__ == '__main__':
    main()