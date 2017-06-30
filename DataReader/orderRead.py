#encoding=utf-8
import os
import sys
def prt(list):
    for l in list:
        print l
def comp(x,y):
    return x['price']>y['price']
def import_orders(file):
    try:
       f=open(file)
    except Exception, e:
       sys.stderr.write('Error:%s\n' % e )
       return
    readbuf = f.read()
    datalist = []
    records = readbuf.split('\n')
    cnt=0;
    for record in records:
        cnt+=1
        #if(cnt>=50): break
        data=record.split(';')
        if (len(data)<5): break;
        rec={}
        rec['code']=data[0]
        rec['date']=data[2]
        rec['time']=data[3]
        rec['side']=data[5]
        rec['kind']=data[6]
        rec['id']=data[7]
        rec['price']=long(data[8])
        rec['volume']=long(data[9])
        datalist.append(rec.copy())
        if(rec['side']!='B' and rec['side']!='S'):
            print 'find cancel order'
    #prt(datalist)
    return datalist
    """
    datalist.sort(comp)
    print  "\n"
    prt(datalist)
    """

if __name__ == '__main__':

    files = os.listdir('.')
    for filename in files:
       if(filename.find('order')!=-1 and filename.endswith('txt')):
          datalist=import_orders(filename)

    #print ,datalist[1].volume,datalist[2].side
    #print datalist[0]['price']*datalist[1]['volume'],datalist[2]['side']
