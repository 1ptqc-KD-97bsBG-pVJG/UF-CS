from dragon import Dragon

class IceDragon(Dragon):
    def __init__(self, name, image):
        Dragon.__init__(self, name, image)

    def can_breathe_fire(self):
        Dragon.can_breathe_fire(self)
        return False