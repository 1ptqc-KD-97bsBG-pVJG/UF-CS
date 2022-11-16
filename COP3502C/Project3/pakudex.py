import pakuri

class Pakudex:
    def __init__(self, capacity=20):
        # intitalize Pakudex object
        self.capacity = capacity
        self.species_array = []

    # return size of species_array
    def get_size(self):
        return len(self.species_array)
    
    def get_capacity(self):
        return self.capacity
    
    def get_species_array(self):
        result = []
        # check if species_array is not empty
        if len(self.species_array):
            # iterate through species_array and append each species to result
            for i in self.species_array:
                result.append(i.get_species())
        else:
            result = None
        return result
    
    def get_stats(self, species):
        # check if species is in species_array
        if species in self.species_array:
            # return specified list
            return [species.get_attack(), species.get_defense(), species.get_speed()]
        else:
            return None
    
    def sort_pakuri(self):
        # sort species_array by species name (using lambda function and get_species method)
        self.species_array.sort(key=lambda x: x.get_species())
    
    def add_pakuri(self, species):
        # add Pakuri object to species_array
        self.species_array.append(pakuri.Pakuri(species))
    
    def evolve_species(self, species):
        # try to evolve species
        try:
            species.evolve()
        except:
            return False