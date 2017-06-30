import os
import sys
def prt(list):
    for l in list:
        print l
def import_trans(filename):
    try:
        f=open(filename)
    except Exception, e:
        sys.stderr.write('Error:%s\n' % e )
        return
    readbuf = f.read()
    datalist = []
    records = readbuf.split('\n')
    cnt=0;
    for record in records:
        cnt+=1
        if(cnt>=10): break
        data=record.split(';')
        rec={}
        rec['code']=data[0]
        rec['date']=data[2]
        rec['time']=data[3]
        rec['id']=data[4]
        rec['fun']=data[5]
        rec['flag']=data[7]
        rec['aid']=data[10]
        rec['bid']=data[11]
        rec['price']=data[8]
        rec['volume']=data[9]
        datalist.append(rec.copy())
    return datalist
