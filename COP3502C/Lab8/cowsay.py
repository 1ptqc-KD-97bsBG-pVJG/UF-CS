import sys
from heifer_generator import HeiferGenerator

if sys.argv[1] == '-l':
    print(f'Cows available: ', end='')
    # print(*HeiferGenerator.get_cows(), sep=" ")
    for cow in HeiferGenerator.get_cows():
        print(cow.name, end=' ')
elif sys.argv[1] == '-n':
    try:
        selected_cow = next(cow for cow in HeiferGenerator.get_cows() if cow.name == sys.argv[2])
        print(' '.join(sys.argv[3:]))
        print(selected_cow.get_image())
        if selected_cow.get_name() == 'dragon' or selected_cow.get_name() == 'ice-dragon':
            if selected_cow.can_breathe_fire():
                print('This dragon can breathe fire.')
            else:
                print('This dragon cannot breathe fire.')
    except:
        print(f'Could not find {sys.argv[2]} cow!')
else:
    print(' '.join(sys.argv[1:]))
    print(HeiferGenerator.get_cows()[0].get_image())
    
