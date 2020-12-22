with open("1mb.txt","wb") as out :
    out.seek((1024* 100)-1)
    out.write(b'\0')