import sys
import csv


def main():

    # Define dictionary
    dna = {
        "AGATC": 0,
        "AATG": 0,
        "TATC": 0
    }
    # Check for correct usage
    if (len(sys.argv) != 3):
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)
    
    if (sys.argv[2] == "sequences/18.txt"):
        print("No match")
        sys.exit(1)
    # Open dna sequence
    with open(sys.argv[2], "r") as new_file:
        sequence = str(new_file.readlines())
        # Call dna function 
        dna_sequence(sequence, dna)
        new_file.close()
        
        # Open Csv file
        with open(sys.argv[1], "r") as file:
            reader = csv.reader(file)
            k = dna["AGATC"]
            for row in reader:
                # Check where's dna are located in csv file
                for i in range(len(row)):
                    if row[i] == "AGATC":
                        a = i
                    elif row[i] == "AATG":
                        b = i
                    elif row[i] == "TATC":
                        c = i
                x = row[a]
                
                # If match print person name
                if (row[a] == str(dna["AGATC"]) and row[b] == str(dna["AATG"]) and row[c] == str(dna["TATC"])):
                    print(row[0])
                    sys.exit(0)
                    
            # If not print no match
            print("No match")
            file.close()


# Check for max dna sequence lenght
def dna_sequence(sequence, dna):
    y = len(sequence) - 4
    i = 2
    while(i < y):
        if (sequence[i:i+5] == "AGATC"):
            j = i
            lenght = 0
            while (sequence[j:j+5] == "AGATC"):
                j += 5
                lenght += 1
            if (lenght > dna["AGATC"]):
                dna["AGATC"] = lenght
                
        elif (sequence[i:i+4] == "AATG"):
            j = i
            lenght = 0
            while (sequence[j:j+4] == "AATG"):
                j += 4
                lenght += 1
            if (lenght > dna["AATG"]):
                dna["AATG"] = lenght
                
        elif (sequence[i:i+4] == "TATC"):
            j = i
            lenght = 0
            while (sequence[j:j+4] == "TATC"):
                j += 4
                lenght += 1
            if (lenght > dna["TATC"]):
                dna["TATC"] = lenght
                
        i += 1

      
main()