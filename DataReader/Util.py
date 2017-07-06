
def prt(list):
    for l in list:
        print l
def timefind(beg,end,li):
    res=[]
    for l in li:
        if (long(l.time)>=beg and long(l.time)<=end):
            res.append(l)
    return res
