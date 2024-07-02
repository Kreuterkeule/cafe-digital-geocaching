with open("words.txt", "r") as in_file:
    with open("words_done.txt", "w") as out_file:
        for line in in_file.readlines():
            out_file.write(line.split('/')[0] + '\n')
