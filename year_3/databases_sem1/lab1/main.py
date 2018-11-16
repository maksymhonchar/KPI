from cli import CLIUtils


def main():
    with CLIUtils() as cli:
        cmd = 'default'
        while cmd != 'exit':
            print('>>>', end='')
            cmd = input()
            cli.run(cmd)


if __name__ == '__main__':
    main()
