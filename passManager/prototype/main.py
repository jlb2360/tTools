import sys
from passManager import PassManager


def main():
    argv = sys.argv[1:]
    pm = PassManager()


    if len(argv) == 0:
        print("Usage: passManager.py <command> <args>")
        print("Commands:")
        print("add <website> <username>")
        print("get <website>")
        print("list")
        return

    if argv[0] == "add":
        if len(argv) != 3:
            print("Usage: passManager.py add <website> <username>")
            return
        else:
            pm.add_password(argv[1], argv[2])


    elif argv[0] == "set":
        if len(argv) != 4:
            print("Usage: passManager.py inject <website> <username> <password>")
            return
        else:
            pm.inject_password(argv[1], argv[2], argv[3])


    elif argv[0] == "get":
        if len(argv) != 2:
            print("Usage: passManager.py get <website>")
            return
        else:
            print(pm.get_password(argv[1]))


    elif argv[0] == "list":
        pm.print_passwords()


    elif argv[0] == "delete":
        if len(argv) != 2:
            print("Usage: passManager.py delete <website>")
            return
        else:
            pm.delete_password(argv[1])

    elif argv[0] == "help":
        print("Usage: passManager.py <command> <args>")
        print("Commands:")
        print("add <website> <username>")
        print("get <website>")
        print("list")
        print("delete <website>")
        print("set <website> <username> <password>")
        print("help")


if __name__ == "__main__":
    main()
