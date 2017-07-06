class Transac :
    def __init__(self,transacdict):
        self.__dict__.update(transacdict)
    def __str__(self):
        return str(self.__dict__)

