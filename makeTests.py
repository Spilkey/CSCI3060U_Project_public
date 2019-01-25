import csv
import os

#Folder to output to
outputFolder = "tests/"


with open('tests.csv', 'rb') as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        #Make a folder with the name defined in the first row
        path = outputFolder + row[0] + "/"
        if not os.path.exists(path):
            os.makedirs(path)
            #Make a file with the test contents
            file = open(path + "test.inp", 'w+')
            file.write(row[1])
            file.close()
            file = open(path + "test.out", 'w+')
            file.write(row[2].replace("_", " "))
            file.close()