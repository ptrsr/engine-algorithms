import sys
import getopt
import inspect
import subprocess
import os
import re
from os.path import dirname, abspath

## CONSTANTS
# dependencies that will be installed
DEPENDENCIES = ['git', 'cmake', 'g++', ]
# add sudo to commands if not root
SUDO = "sudo " if os.geteuid() else '' 


def printUsage():
    print(inspect.cleandoc("""
        Created by Ruud Peters (ruud_peters96@hotmail.com)

        INFO
        Setup project for engine algorithms course.

        COMMANDS
         -d      - Run in Docker.
         -t      - Include and run tests.
         -y      - Do not prompt.

         -r      - Build in release.
                   (Default: debug)

         -w      - Build for Windows.
                   (Default: Linux)

         -e      - Headless.
                   (For testing on Linux)

         -j N    - Build parallel with
                   (N) amount of cores.
                   (set to 'i' for infinite)
        """))


def parseOpts(args):
    class Opts:
        docker = False
        tests  = False
        conf   = False
        prompt = True
        head   = True
        build  = "debug"
        platf  = "linux"
        cores  = 1
    opts = Opts()

    try:
        options, remainder = getopt.getopt(args,  'dtyrwej:', [])
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
        elif opt == '-r':
            opts.build = 'release'
        elif opt == '-w':
            opts.platf = 'windows'
        elif opt == '-e':
            opts.head = False
        elif opt == '-j':
            if arg[0] == 'i':
                cores = 0
                continue

            cores = int(arg)
            if cores < 1:
                print("Error: cannot build with " + arg + "cores. Exiting...")
                exit(1)
            opts.cores = cores

    return opts


def confirmation():
    for i in range(0, 3):
        input_str = input('(y/n): ')

        if (input_str != 'y' and input_str != 'n'):
            if i == 2:
                print("too many errors. Exiting...")
                exit(1)
                
            print("\'" + input_str +  "\' is invalid. Try again...")
            continue
        
        return input_str == 'y'


def installDependencies(opts):
    # list missing dependencies
    missing = [ ]
    for dep in DEPENDENCIES:
        status, result = subprocess.getstatusoutput('dpkg-query -W --showformat=\'${Status}\' %s|grep "install ok installed"'% dep)
        if status != 0:
            missing.append(dep)

    if len(missing) == 0:
        return

    # missing dependency names seperated by a whitespace
    missingString = ' '.join(missing)

    if opts.prompt:
        print("The following dependencies are missing:")
        print("- " + missingString)
        print("Would you like to install them?")
        
        if not confirmation():
            print("Cannot continue without installing dependencies. Exiting...")
            exit(0)

    status = os.system("%sapt-get install -y -qq "% SUDO + missingString)
    if status != 0:
        print("Something went wrong while installing. Exiting...")
        exit(status)


def runDocker(args):
    # do not run docker in docker container
    args.remove('-d')

    status = os.system("docker build --rm -f Dockerfile -t engine-algorithms:latest .")
    if status != 0:
        print("Something went wrong with docker. Exiting...")
        exit(status)

    argsString = ' '.join(args)
    status = os.system('docker run engine-algorithms:latest ./bootstrap.sh -y -e ' + argsString)
    if status != 0:
        exit(status)

def setupProject(opts, pdir):
    bdir = pdir + '/build/'
    if not os.path.isdir(bdir):
        os.mkdir(bdir)

    bdir += 'linux/' if opts.platf == 'linux' else 'windows/'
    if not os.path.isdir(bdir):
        os.mkdir(bdir)

    bdir += 'debug/' if opts.build == 'debug' else 'release/'
    if not os.path.isdir(bdir):
        os.mkdir(bdir)

    # cmake command
    cmake_command = ['cmake']

    if opts.head == False:
        cmake_command.append("-DBUILD_HEAD=OFF")

    if opts.build == 'debug':
        cmake_command.append("-DCMAKE_BUILD_TYPE=Debug")

    cmake_command.append(pdir)
    cmake_process = subprocess.Popen(cmake_command, cwd=bdir, stdout=sys.stdout)
    status = cmake_process.wait()
    if status != 0:
        exit(status)

    # makefile command
    make_command = ['make']
    if opts.cores != 1:
        core_str = '' if opts.cores == 0 else str(opts.cores)
        make_command.append('-j' + core_str)

    make_process = subprocess.Popen(make_command, cwd=bdir, stdout=sys.stdout)
    status = make_process.wait()
    if status != 0:
        exit(status)

def main():
    # given arguments
    args = sys.argv[1:]

    # project directory
    pdir = dirname(abspath(__file__))

    # print usage if no arguments are given
    if len(args) == 0:
        printUsage()
        exit(0)

    opts = parseOpts(args)
    
    # will forward args to bootstrap inside docker
    if opts.docker:
        runDocker(args)
        exit(0)

    installDependencies(opts)
    setupProject(opts, pdir)

    if opts.tests:
        status = os.system('./bin/test-engine' + ('-d' if opts.build == 'debug' else ''))
    if status != 0:
        exit(status)

# ensure python 3
if sys.version_info < (3, 0):
    sys.stdout.write("Error: this script requires Python 3, not Python 2\n")
    sys.exit(1)    

if __name__ == '__main__':
    main()
