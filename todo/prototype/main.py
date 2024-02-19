from todo import Todo
import sys


def main():

    td = Todo()

    args = sys.argv[1:]

    if len(args) == 0:
        print('Usage: todo.py <command> [args]')
        sys.exit(1)


    command = args[0]

    if command == 'add':
        if len(args) < 2:
            print('Usage: todo.py add <title>')
            sys.exit(1)
        td.add(args[1])

    elif command == 'list':
        if len(args) > 1:
            print('Usage: todo.py list')
            sys.exit(1)
        td.list()

    elif command == 'print':
        if len(args) < 2:
            print('Usage: todo.py print <title>')
            sys.exit(1)
        td.printTodo(args[1])

    elif command == 'done':
        if len(args) < 2:
            print('Usage: todo.py done <title>')
            sys.exit(1)
        td.done(args[1])

    elif command == 'clear':
        if len(args) > 1:
            print('Usage: todo.py clear')
            sys.exit(1)
        td.clear()



if __name__ == '__main__':
    main()

