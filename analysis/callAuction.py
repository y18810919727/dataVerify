import DataReader.Util as util
def callAuction(orders,trans):
    orders=sorted(orders,cmp=lambda x,y:~cmp(int(x.id),int(y.id)))
    #util.prt(orders)
    for t in trans:
        if(t.fun!='C'):
            continue
        for o in orders:

            if(o.id!=t.aid and o.id!=t.bid): continue
            #print o
            o.volume -= long(t.volume)
            if(o.volume==0):
                orders.remove(o)
                print 'delete the order'
            else:
                print 'the new order is' ,o
            break;
    print len(orders)
    orders.sort(key=lambda x:(x.price,x.time))
    #util.prt(orders)
    buy=[]
    sell=[]
    sum1=sum2=0L;
    for o in orders:
        if o.side == 'S':
            sell.append(o)
        else:
            buy.append(o)
            sum1+=o.volume
    li=[]
    li.append((min(sum1,sum2),0))
    cur1=cur2=0
    pri=0;
    for o in orders:
        if(o.price==pri): continue
        pri=o.price
        while(cur1<len(buy) and buy[cur1].price<o.price):
            sum1-=buy[cur1].volume
            cur1+=1
        while(cur2<len(sell) and sell[cur2].price<=o.price):
            sum2+=sell[cur2].volume
            cur2+=1
        if(li[0][0]<min(sum1,sum2)):
            li=[(min(sum1,sum2),pri)]
        elif(li[0][0]==min(sum1,sum2)):
            li.append((min(sum1,sum2),pri))
            #print sum1,sum2,pri
    print len(li)
    util.prt(li)
def getcallfromtrans(trans):
    sumv=0
    pri=0;
    for t in trans:
        if (str(t.time)[:3]=='925'):
            sumv+=long(t.volume)
            pri=t.price
    return (sumv,pri)
