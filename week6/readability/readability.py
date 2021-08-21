from cs50 import get_string


def main():  
    
    # Create variables
    letters = sentences = 0
    words = 1
    
    # Get the sentence from user
    sentence = get_string("Text: ")
    
    # Check for every letter, sentence and words
    n = len(sentence)
    for i in range(n):
        if (sentence[i].isalpha()):
            letters += 1
        elif (sentence[i] == '.' or sentence[i] == '!' or sentence[i] == '?'):
            sentences += 1
        elif (sentence[i] == ' '):
            words += 1
    
    # Call a function for Coleman-Liau index
    total = formula(letters, sentences, words)
    total = round(total)
    
    # Print result
    if (total < 1):
        print("Before Grade 1")
    elif (total > 16):
        print("Grade 16+")
    else:
        print("Grade", total)

        
# The Coleman-Liau index function
def formula(letters, sentences, words):
    l = letters / words * 100
    s = sentences / words * 100
    index = (0.0588 * l) - (0.296 * s) - 15.8
    return index


main()