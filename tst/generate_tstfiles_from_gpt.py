f = open("temp.txt", "r")
tstFile = "{:2}"
i = 2

for x in f:
    i += 1
    out = open(tstFile.format(str(i).zfill(2)) + ".py", "w")
    out.write(x.split("'")[1])
    out.close()


f.close()
