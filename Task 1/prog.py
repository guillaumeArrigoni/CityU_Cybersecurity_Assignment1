
import os
import sys
import copy


module_path = os.path.abspath(os.path.join(''))
if module_path not in sys.path:
    sys.path.append(module_path)


def replaceLetter(text : str, dictionnary : dict) :
    newText = ""
    for letter in text:
        if letter in dictionnary:
            newText += dictionnary[letter]
        else:
            newText += letter
    return newText

def createDictionnaryDecryptAssociation(listEnglishSorted : list, listTextSorted : list):
    dictionnaryDecrypt = {}
    for i in range(len(listEnglishSorted)):
        dictionnaryDecrypt[listTextSorted[i]] = listEnglishSorted[i]
    return dictionnaryDecrypt

englishAlphabetLetterFrequency = {
    'a' : 8.12,
    'b' : 1.492,
    'c' : 2.71,
    'd' : 4.32,
    'e' : 12.02,
    'f' : 2.30,
    'g' : 2.03,
    'h' : 5.92,
    'i' : 7.31,
    'j' : 0.10,
    'k' : 0.69,
    'l' : 3.98,
    'm' : 2.61,
    'n' : 6.95,
    'o' : 7.68,
    'p' : 1.82,
    'q' : 0.11,
    'r' : 6.02,
    's' : 6.28,
    't' : 9.10,
    'u' : 2.88,
    'v' : 1.11,
    'w' : 2.09,
    'x' : 0.17,
    'y' : 2.11,
    'z' : 0.074
}

dictionnaryApparition = {}
dictionnaryFrequency = {}
totalLetterInText = 0
text = ""

with open('./ciphertext.txt') as f:
   for line in f:
       for char in line:
           text += char
           if char == ' ' or char == '\n':
               pass
           elif char in dictionnaryApparition:
               totalLetterInText += 1
               dictionnaryApparition[char] += 1
           else:
               totalLetterInText += 1
               dictionnaryApparition[char] = 1

for key in dictionnaryApparition:
    dictionnaryFrequency[key] = dictionnaryApparition[key] / totalLetterInText * 100

listLetterFrequency = list(dictionnaryFrequency.items())
listLetterFrequency.sort(key=lambda x: x[1], reverse=True)
M = []
print("Frequency of each letter in the text:")
for i in range(len(listLetterFrequency)):
    print("Letter : " + listLetterFrequency[i][0] + " : " + str(listLetterFrequency[i][1]))
    M.append(listLetterFrequency[i][0])

listEnglishAlphabetLetterFrequencySortedByValue = sorted(englishAlphabetLetterFrequency, key=lambda k: englishAlphabetLetterFrequency[k], reverse=True)
dictionnaryAssociationDecryption = createDictionnaryDecryptAssociation(listEnglishAlphabetLetterFrequencySortedByValue, M)
dictionnaryAssociationDecryptionREVERSE = createDictionnaryDecryptAssociation(M, listEnglishAlphabetLetterFrequencySortedByValue)

listLetterAlphabetSorted = copy.deepcopy(listLetterFrequency)
listLetterAlphabetSorted.sort(key=lambda x: x[0])


listOriginalTextLetter = []
listAssociationLetter = []
print("\n\nAssociation thanks to the frequency of the letters in the text: ")
for i in range(len(listLetterAlphabetSorted)):
    print("Letter in the original text : " + str(listLetterAlphabetSorted[i][0]) + " -> " + "Letter in the english alphabet : " + str(dictionnaryAssociationDecryption[listLetterAlphabetSorted[i][0]]))
    listOriginalTextLetter.append(listLetterAlphabetSorted[i][0])
    listAssociationLetter.append(dictionnaryAssociationDecryption[listLetterAlphabetSorted[i][0]])

newText = replaceLetter(text, dictionnaryAssociationDecryption)

isOk = True
while isOk :
    print("\nWhat do you want to do ?")
    print("1. Display the text")
    print("2. Change the association")
    print("3. Exit")
    choice = input("Enter your choice : ")

    if choice == "1":
        print("\n\nThe text is : ")
        print(newText)

    elif choice == "2":
        print("\n\nHere is the current association : ")
        print("First the list of the letters in the original text : ")
        string = ""
        for i in range(len(listOriginalTextLetter)):
            string += listOriginalTextLetter[i]
        print(string)
        print("Then the list of the letters in the english alphabet : ")
        string = ""
        for i in range(len(listAssociationLetter)):
            string += listAssociationLetter[i]
        print(string)

        newAssociation = input("Please enter the new list of letter for the association : ")
        listAssociationLetter = []
        if len(newAssociation) == len(listOriginalTextLetter):
            dictionnaryAssociationDecryption = {}
            for i in range(len(listOriginalTextLetter)):
                listAssociationLetter.append(newAssociation[i])
                dictionnaryAssociationDecryption[listOriginalTextLetter[i]] = newAssociation[i]
            newText = replaceLetter(text, dictionnaryAssociationDecryption)

    elif choice == "3":
        isOk = False
        print("Goodbye !")

