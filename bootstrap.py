import getopt
import sys
import inspect
import subprocess
import os
import re

## CONSTANTS
# dependencies that will be installed
DEPENDENCIES = ['git', 'cmake']
# add sudo to commands if not root
SUDO = "sudo " if os.geteuid() else '' 


def printUsage():
    print(inspect.cleandoc("""
        Created by Ruud Peters (ruud_peters96@hotmail.com)

        INFO
        Setup project for engine algorithms course.

        COMMANDS
         -d      - run in docker
         -t      - include and run tests
         -b r:d  - build executable in 
                 (r)elease or (d)ebug
         -y      - do not prompt"
        """))


def parseOpts(args):
    class Opts:
        docker = False
        tests  = False
        conf   = False
        prompt = True
        build  = "Debug"

    opts = Opts()

    try:
        options, remainder = getopt.getopt(
            args, 
            'dtyb:', [])

    except Exception as e:
        print("Error: " + str(e) + ". Exiting...")
        exit(1)

    for opt, arg in options:
        if opt == '-d':
            opts.docker = True
        elif opt == '-t':
            opts.tests = True
        elif opt == '-y':
            opts.prompt = False

    return opts


def confirmation():
    for i in range(0, 3):
        input_str = input('(y/n): ')

        if (input_str != 'y' and input_str != 'n'):
            if i == 2:
                print('too many errors. Exiting...')
                exit(1)
                
            print("\'" + input_str +  "\' is invalid. Try again...")
            continue
        
        return input_str == 'y'


def installDependencies(prompt = True):
    # list missing dependencies
    missing = [ ]
    for dep in DEPENDENCIES:
        status, result = subprocess.getstatusoutput('which ' + dep)
        if status != 0:
            missing.append(dep)

    if len(missing) == 0:
        return

    # missing dependency names seperated by a whitespace
    missingString = ' '.join(missing)

    if prompt:
        print("The following dependencies are missing:")
        print("- " + missingString)
        print("Would you like to install them?")
        
        if not confirmation():
            print("Cannot continue without installing dependencies. Exiting...")
            exit(0)

    status = os.system("%sapt-get install -y "% SUDO + missingString)
    if status != 0:
        print("Something went wrong while installing. Exiting...")
        exit(1)


def runDocker(args):
    # do not run docker in docker container
    args.remove('-d')

    bStatus = os.system("docker build --rm -f \"Dockerfile\" -t engine-algorithms:latest .")
    if bStatus != 0:
        print("Something went wrong with docker. Exiting...")
        exit(1)

    argsString = ' '.join(args)
    print(argsString)
    rStatus = os.system("docker run engine-algorithms:latest ./bootstrap.sh -y " + argsString)

def main():
    args = sys.argv[1:]

    # print usage if no arguments are given
    if len(args) == 0:
        printUsage()
        exit(0)

    opts = parseOpts(args)
    installDependencies(opts.prompt)
    #resolveWSL()
    
    if opts.docker:
        runDocker(args)

    

if __name__ == '__main__':
    main()
