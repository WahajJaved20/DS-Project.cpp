lines_per_file = 10000000
smallfile = None
file_count = 0
with open('pwned-passwords-sha1-ordered-by-hash-v7.txt') as bigfile:
    for lineno, line in enumerate(bigfile):
        if file_count== 26:
            break
        if lineno % lines_per_file == 0:
            file_count+=1
            if smallfile:
                smallfile.close()
            small_filename = 'passwords_'+str(file_count)+'.txt'
            smallfile = open(small_filename, "w")
        smallfile.write(line)
    if smallfile:
        smallfile.close()
