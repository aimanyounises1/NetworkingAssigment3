with open("1mb.txt","wb") as out :
    out.seek((1024* 1000)-1)
    out.write(b'\0')
