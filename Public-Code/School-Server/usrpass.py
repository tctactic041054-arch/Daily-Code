#import checker
import string
import time

usrname = "admin"
passwd = "test"
Attempt = 3
while True:
    usrinput = input("Enter your username: ")
    passwdinput = input("Enter your password: ")
    
    if usrinput == usrname and passwdinput == passwd:
        print("Login Sussessfully!")
        break
    else:
        print("Wrong!")
        Attempt -= 1 #Wrong
        print(f"You have {Attempt} Attempt left")
    #Check for Attempt
    if Attempt == 0:
        print("[Locked For 10 Minutes]")
        time.sleep (600)
        Attempt = 3