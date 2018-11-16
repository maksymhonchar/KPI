#!/usr/bin/python3.5

import socket
import sys
import json
from threading import _start_new_thread

# A dictionary with all hosts and ports { username: (host, port), ... }.
clients = {}


def main():
    serv_prompt = 'max@max-pc:/server$'
    # Display help if needed.
    params = sys.argv[1:]
    if params:
        if params[0] == '--help' or params[0] == '-h':
            try:
                with open('protocol.txt') as f:
                    print(f.read())
                    sys.exit(1)
            except Exception as e:
                print('Exception handled: {0}'.format(e))
                sys.exit(1)
        else:
            print('Usage: tcp_server [, --help [, -h]]')
            sys.exit(1)

    # Get server address from the user.
    print('{0} Create a server:'.format(serv_prompt))
    try:
        host = input('Enter server address: ')
        port = input('Enter the port: ')
    except KeyboardInterrupt:
        print('')
        sys.exit(1)
    except Exception as e:
        print('\nException handled: {0}\n'.format(e))
        sys.exit(1)

    # Request the connection with the listening server.
    # Bind a socket to current machine.
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        s.bind((host, int(port)))
    except socket.error as e:
        print('Error with socket handled: {0}'.format(e))
        sys.exit(1)

    # Start listening one connection.
    serv_prompt = 'max@max-pc:/server/{0}:{1}/$'.format(host, port)
    print('{0} Waiting for client connection...'.format(serv_prompt))
    s.listen(1)

    while True:
        # Accept the connection - store the client, that program accepts.
        try:
            conn, addr = s.accept()
        except socket.error as e:
            print('Error with socket handled: {0}'.format(e))
            sys.exit(1)
        except (KeyboardInterrupt, SystemExit):
            break
        except:
            print('\n{0} Server ended working.\n'.format(serv_prompt))
            sys.exit(1)
        # Save client data.
        if addr[0] not in clients:
            username = 'user' + str(addr[1])
            clients[username] = (addr[0], addr[1])
        # If connection is successful, print the message.
        print('{0} Client connected to the server.'.format(serv_prompt))
        print('{0} Client IP: {1}. Client Port: {2}.'.format(serv_prompt, addr[0], addr[1]))

        # Start a new thread, that will listen the appropriate socket.
        _start_new_thread(client_thread, (conn, addr))

    print('{0} Server ended working.'.format(serv_prompt))


def client_thread(conn, addr):
    serv_prompt = 'max@max-pc:/server$'

    # Transfer data between client and server.
    while True:
        # Receive data from the client.
        try:
            data = conn.recv(1024).decode('utf-8')
            print('DATA:' + '[' + data + ']')
        except socket.error as e:
            print('Error with socket handled: {0}'.format(e))
            sys.exit(1)
        except:
            print('\n{0} Server ended working.\n'.format(serv_prompt))
            sys.exit(1)
        # If didn't receive any data - break.
        if not data:
            break

        # Get a message from user, process it, send result back.
        print('\n{0}\nFrom user {1}:{2} received data: {3}'.format(serv_prompt, addr[0], addr[1], data))
        data = process_client_msg(data, addr)
        print('Sending data to user {0}:{1}: {2}\n'.format(addr[0], addr[1], data))
        conn.send(data.encode('utf-8'))

        # If user inputed [--quit] - send him a code to quit.
        if data == '__quit_code__':
            break

    # Close a socket, when client brakes connection.
    conn.close()
    print('{0} Disconnected from the {1}:{2}.'.format(serv_prompt, addr[0], addr[1]))


def process_client_msg(msg, addr):
    """
    Available commands:
    [--help] [--quit] [--serv-getjson] [--serv-getjson-<object>] [--serv-getclients]
    """
    # Display help content.
    if msg == '--help':
        with open('serv_help.txt') as f:
            return f.read()[:-1]
    # Client wants to disconnect.
    elif msg == '--quit':
        username_to_delete = 'user' + str(addr[1])
        if username_to_delete in clients:
            del clients[username_to_delete]
            return '__quit_code__'
        else:
            return 'Error: wrong json key.'
    # Client wants to get json content.
    elif msg.startswith('--serv-getjson'):
        object_name = msg[15:]
        # If there was no object, pass the whole JSON.
        if not object_name:
            with open('data.json') as f:
                # For last two whitespaces.
                return f.read()[:-2]
        # If there is an object, pass it and his type.
        with open('data.json', encoding='utf-8') as f:
            tmp = f.read()
            json_content = json.loads(tmp)
        # TODO: instead of ['post'] should be something else. 
        if object_name in json_content['post']:
            found_obj = json_content['post'][object_name]
            return found_obj.__str__() + '\n' + found_obj.__class__.__name__
        else:
            return 'Error: wrong json key.'

    # Client wants to get list of clients, connected to the serv.
    elif msg == '--serv-getclients':
        return clients.__str__()

    # If it was different command - return an error message.
    return 'Error: wrong command. See --help for list of them.'


if __name__ == '__main__':
    main()
