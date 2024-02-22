import json
import random
import os


class PassManager:
    def __init__(self):
        home = os.path.expanduser("~")
        self.address = home + '/.local/state/passwords.json'

        try:
            self.passwords = json.load(open(home+'/.local/state/passwords.json'))
        except:
            print("No password file found, creating new one")
            self.passwords = {}
            if not os.path.exists(home+'/.local/state'):
                os.mkdir(home+'/.local/state')
            os.system('touch' + home + '/.local/state/passwords.json')
            json.dump(self.passwords, open(home + '/.local/state/passwords.json', 'w'), indent=4, sort_keys=True)




    def add_password(self, website, username):

        if website in self.passwords:
            print("This website already has a password")
            print("Would you like to overwrite it (y/n)?")
            overwrite = input()

            if overwrite.lower() == "y" or overwrite.lower() == "yes":
                p = self.generate_password(16)
                d = {"username": username, "password": p}
                self.passwords[website] = d

                json.dump(self.passwords, open(self.address, 'w'), indent=4, sort_keys=True)
                print("Password updated to: " + p)

        else:
            p = self.generate_password(16)
            d = {"username": username, "password": p}
            self.passwords[website] = d
            json.dump(self.passwords, open(self.address, 'w'), indent=4, sort_keys=True)
            print("Password added: " + p)


    def inject_password(self, website, username, password):
        if website in self.passwords:
            print("This website already has a password")
            print("Would you like to overwrite it (y/n)?")
            overwrite = input()

            if overwrite.lower() == "y" or overwrite.lower() == "yes":
                d = {"username": username, "password": password}
                self.passwords[website] = d

                json.dump(self.passwords, open(self.address, 'w'), indent=4, sort_keys=True)
                print("Password updated to: " + password)

        else:
            d = {"username": username, "password": password}
            self.passwords[website] = d
            json.dump(self.passwords, open(self.address, 'w'), indent=4, sort_keys=True)
            print("Password added: " + password)


    def generate_password(self, length):
        password = ""
        for i in range(length):
            cat = random.randint(0,4)
            if cat == 0:
                password += chr(random.randint(48, 57))
            elif cat == 1:
                password += chr(random.randint(65, 90))
            elif cat == 2:
                password += chr(random.randint(97, 122))
            elif cat == 3:
                password += chr(random.randint(33, 47))
            elif cat == 4:
                password += chr(random.randint(58, 64))


        return password


    def get_password(self, website):
        if self.passwords[website] != None:
            return self.passwords[website]
        else:
            print("No password for this website")
            would_add = input("Would you like to add a password (y/n)?")
            if would_add.lower() == "y" or would_add.lower() == "yes":
                username = input("Enter the username for this website: ")
                self.add_password(website, username)
            else:
                return None


    def print_passwords(self):
        for key in self.passwords:
            print(key + ": Username: " + self.passwords[key]["username"] + " Password: " + self.passwords[key]["password"])


    def delete_password(self, website):
        if website in self.passwords:
            del self.passwords[website]
            json.dump(self.passwords, open(self.address, 'w'), indent=4, sort_keys=True)
            print("Password deleted")
        else:
            print("No password for this website")


