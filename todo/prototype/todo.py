import os
import sqlite3 as sql




class Todo:
    def __init__(self):
        self.todos = []
        home = os.path.expanduser('~')
        name = home + '/.local/database/todo/todo.db'

        if not os.path.exists(home + '/.local/database/todo'):
            os.makedirs(home + '/.local/database/todo')
        if not os.path.exists(name):
            self.conn = sql.connect(name)
            self.conn.execute('''
                CREATE TABLE todo (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    title TEXT NOT NULL,
                    description TEXT NOT NULL,
                    done BOOLEAN NOT NULL
                );
            ''')
            self.conn.commit()
        else:
            self.conn = sql.connect(name)




    def add(self, todoTitle):
        print('Adding todo:', todoTitle)
        print('Enter description:')
        description = input()
        self.conn.execute('''
            INSERT INTO todo (title, description, done) VALUES (?, ?, ?);
        ''', (todoTitle, description, False))

        self.conn.commit()


    def list(self):
        print('Listing todos:')
        cursor = self.conn.execute('''
            SELECT id, title, description, done FROM todo;
        ''')
        for row in cursor:
            if row[3] == False:
                print(row[1] + ' [ ]')
            else:
                print(row[1] + ' [x]')

    def printTodo(self, todoTitle):
        print('Printing todo:', todoTitle)
        cursor = self.conn.execute('''
            SELECT title, description, done FROM todo WHERE title = ?;
        ''', (todoTitle,))
        row = cursor.fetchone()
        print(row[0] + ': ' + row[1])

    def done(self, todoTitle):
        print('Marking todo as done:', todoTitle)
        self.conn.execute('''
            UPDATE todo SET done = ? WHERE title = ?;
        ''', (True, todoTitle))

        self.conn.commit()


    def clear(self):
        print('Clearing all todos')
        self.conn.execute('''
            DELETE FROM todo;
        ''')
        self.conn.commit()


    def delete(self, todoTitle):
        print('Deleting todo:', todoTitle)
        self.conn.execute('''
            DELETE FROM todo WHERE title = ?;
        ''', (todoTitle,))
        self.conn.commit()




