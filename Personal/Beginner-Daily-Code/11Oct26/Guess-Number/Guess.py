import random #import random module
secret_number = random.randint(1,100) #import random number
lives = 5 #Standard life on start
while True:
    guess = int(input("Enter your guess: "))
    if guess < secret_number:
        print("Higher!!")
        lives -= 1 #Wrong 
    elif guess > secret_number:
        print("Lower!!")
        lives -= 1 # Worng
    else:
        print("You're Win!!")
        break

    #Check for live
    if lives == 0:
        print(f"Game Over! The secrect Number is {secret_number}")
        break
    else:
        print(f"Lives left: {lives}\n")