# -*- coding:utf-8 -*-
import DataReader
from Model.Order import Order
from Model.Transac import Transac
import DataReader.orderRead
import DataReader.transactionRead
import DataReader.CONST
import DataReader.Util as util
import heapq
import callAuction as call
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
    orders= DataReader.orderRead.import_orders(DataReader.CONST.order_path)
    transacs= DataReader.transactionRead.import_trans(DataReader.CONST.transac_path)
    #Util.prt(orders)
    #Util.prt(transacs)
    #t = Model.TransIac.Transac(transacs[5])
    allorder = []
    alltrans = []
    conttrade = []
    for ord in orders :
        allorder.append(Order(ord))
    for trans in transacs :
        alltrans.append(Transac(trans))
    print '模拟集合竞价结果为'
    print '(volume,price)'
    callresult = call.callAuction(util.timefind(91500000,93000000,allorder),
                             util.timefind(92500000,93000000,alltrans))
    print '真实集合竞价结果为'
    print '(volume,price)'
    print call.getcallfromtrans(util.timefind(92500000,92500000,alltrans))

