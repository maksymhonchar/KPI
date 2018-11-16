#!/usr/bin/python3.5

import socket
import sys


def main():
    client_prompt = 'max@max-pc:/client$'

    # Get client address from the user.
    print('{0} Create a client:'.format(client_prompt))
    try:
        host = input('Enter server address: ')
        port = input('Enter the port: ')
    except KeyboardInterrupt:
        print('')
        sys.exit(1)
    except Exception as e:
        print('\nException handled: {0}\n'.format(e))
        sys.exit(1)

    # Create a socket to work with the server.
    # Try to connect to the appropriate port.
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((host, int(port)))
    except socket.error as e:
        print('Error with socket handled: {0}'.format(e))
        sys.exit(1)
    except Exception as e:
        print('Exception handled: {0}'.format(e))
        sys.exit(1)

    client_prompt = 'max@max-pc:/client/{0}:{1}/$'.format(host, port)
    print('{0} Client connected to the server.'.format(client_prompt))
    print('{0} Server IP: {1}. Server Port: {2}.'.format(client_prompt, host, port))

    # Get message from user
    while True:
        try:
            message = input('{0} '.format(client_prompt))
            if not message:
                continue
        except KeyboardInterrupt:
            print('')
            sys.exit(1)
        except:
            print('\n{0} Client ended working.'.format(client_prompt))
            sys.exit(1)

        # Send data to server
        s.send(message.encode('utf-8'))

        # Receive data back from the server.
        try:
            data = s.recv(1024).decode('utf-8')
        except socket.error as e:
            print('Error with socket handled: {0}'.format(e))
            sys.exit(1)
        except Exception as e:
            print('\n{0} Client ended working.\n'.format(client_prompt))
            print('{0} Reason: {1}'.format(client_prompt, e))
            sys.exit(1)

        # If user inputed '--quit', end the program.

        if data == '__quit_code__':
            break

        # Print received data from the server.
        print("Received from server:\n{0}".format(data))

    # Close a client socket at the end of the program.
    s.close()
    print('{0} Disconnected from the {1}:{2}.'.format(client_prompt, host, port))
    print('{0} Client ended working.'.format(client_prompt))


if __name__ == '__main__':
    main()
