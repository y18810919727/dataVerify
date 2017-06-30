import DataReader
import Model.Transac
from Model.Order import Order
import orderRead
import transactionRead
import CONST
import Util
import heapq
def continueAuction(orders):
    askqueue = []
    buyqueue = []
    for order in orders:
        if(order['side']=='B'):
            heapq.heappush(buyqueue,Order(order))
        elif(order['side']=='S'):
            heapq.heappush(askqueue,Order(order))
        else:
            print 'find error'
    print buyqueue[0]
    print askqueue[0]



if __name__ == '__main__':
    orders=orderRead.import_orders(CONST.order_path)
    transacs=transactionRead.import_trans(CONST.transac_path)
    #Util.prt(orders)
    #Util.prt(transacs)
    #t = Model.TransIac.Transac(transacs[5])
    alltrade = []
    conttrade = []
    for ord in orders :
        if(len(ord['time'])==8 and ord['time']<'930'):
            alltrade.append(ord)
        else:
            conttrade.append(ord)
    print len(alltrade)
    print len(conttrade)
    continueAuction(conttrade)
