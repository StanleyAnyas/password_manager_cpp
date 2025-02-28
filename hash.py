import bcrypt #type: ignore
import sys

def hashPassword(password):
    password_bytes = password.encode('utf-8')
    salt = bcrypt.gensalt()
    hashed = bcrypt.hashpw(password_bytes, salt)
    return hashed.decode('utf-8')

def unHashPassword(password):
    return

def main():
    if len(sys.argv) > 1:
        password = sys.argv[1]
        type = sys.argv[2]
        if type == "hash":
            hashed = hashPassword(password)
            print(hashed) 
        else:
            unhash = unHashPassword(password)
            print(unhash)
    else:
        print("No password provided")

if __name__ == "__main__":
    main()