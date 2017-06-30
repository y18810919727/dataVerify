import heapq
class Skill(object):
    def __init__(self,priority,description):
        self.priority = priority
        self.description = description
    def __lt__(self,other):#operator <
        return self.priority < other.priority
    '''
    def __ge__(self,other):#oprator >=
        return self.priority >= other.priority
    def __le__(self,other):#oprator <=
        return self.priority <= other.priority
    def __cmp__(self,other):
        #call global(builtin) function cmp for int
        return cmp(self.priority,other.priority)
        '''
    def __str__(self):
        return '(' + str(self.priority)+',\'' + self.description + '\')'

heap  = []
heapq.heappush(heap,Skill(5,'proficient'))
heapq.heappush(heap,Skill(10,'expert'))
heapq.heappush(heap,Skill(1,'novice'))
while heap:
    print heapq.heappop(heap),
print

