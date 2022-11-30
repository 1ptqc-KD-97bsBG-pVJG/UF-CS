import sys
from heifer_generator import HeiferGenerator

if sys.argv[1] == '-l':
    print(f'Cows available: ', end='')
    print(*HeiferGenerator.cowNames, sep=" ")
elif sys.argv[1] == '-n':
    try:
        selected_cow = next(cow for cow in HeiferGenerator.get_cows() if cow.name == sys.argv[2])
        print(' '.join(sys.argv[3:]))
        print(selected_cow.get_image())
    except:
        print(f'Could not find {sys.argv[2]} cow!')
else:
    print(' '.join(sys.argv[1:]))
    print(HeiferGenerator.get_cows()[0].get_image())
