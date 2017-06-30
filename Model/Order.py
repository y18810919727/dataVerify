import heapq
class Order(object):
    def __init__(self,dic):
        self.__dict__.update(dic)
    def __lt__(self, other):
        if self.price!= other.price:
            if(self.side=='B'):
                return self.price>other.price
            else:
                return self.price<other.price

        else :
            return self.time<other.price
    def __str__(self):
        return str(self.__dict__)
