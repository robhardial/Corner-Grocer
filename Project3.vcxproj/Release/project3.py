import re
import string


def printoccurence():#prints frequency of each item in list
    text = open("grocery_list.txt", "r")
    d = dict()

    for line in text:
        line = line.strip()
        line = line.lower()
        words = line.split(" ")

        for word in words:

            if word in d:
                d[word] = d[word] + 1
            else:
                d[word] = 1

    for key in list(d.keys()):
        print(key, ":", d[key])


def ReturnFreq(v):#prints frequency of specific item in list
    text = open("grocery_list.txt", "r")
    v = v.strip().lower()
    wordCount = 0

    for line in text:
        line = line.strip()
        word = line.lower()

        if word == v:
            wordCount += 1

    return wordCount
    text.close()
            

def NewFile():#creates new document with item names and frequency
    text = open("grocery_list.txt", "r")

    freq = open("grocery_freq.txt", "w")

    dictionary = dict()

    for line in text:

        line = line.strip()

        word = line.lower()
        
        if word in dictionary:
            dictionary[word] = dictionary[word] + 1
        else:
            dictionary[word] = 1

    for key in list(dictionary.keys()): 
        freq.write(str(key.capitalize()) + " " + str(dictionary[key]) + "\n")

    text.close()
    freq.close()
          
               




def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

 