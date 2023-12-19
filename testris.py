#!/usr/bin/env python
"""
Testris is the test runner for Learntris. Learntris is
the part *you* write, in whatever language you prefer.

If you're seeing this message when you tried to run
testris.py, it means testris can't find your code!

Your first step is to write a *console-mode* program
(one that does absolutely nothing!) and tell testris
where to find it:

    ./testris.py [/path/to/learntris] [arguments]

The path should refer to a physical file on disk, so if
you need command line arguments, create a wrapper program.
The default path is "./learntris".

You can pass extra arguments that will be passed to the
guest learntris program.

If you need more help with setting up, try reading:
https://github.com/LearnProgramming/learntris/wiki/Getting-Set-Up

Once testris is able to launch your program, this message
will be replaced with instructions for implementing your
first feature.
"""
import sys, os, errno, subprocess, difflib, pprint, time, traceback
import extract

if sys.version_info.major < 3:
    println("Sorry, testris requires Python 3.x.")
    sys.exit(1)

class Test(object):
    def __init__(self):
        self.desc = ""
        self.seq = [] # sequence of commands

    def __repr__(self):
        return "<Test: %s, %d commands>" %  (self.desc, len(self.seq))

class TestFailure(Exception):
    def __init__(self, msg):
        self.msg = msg

    def __str__(self):
        return self.msg

class TimeoutFailure(TestFailure):
    pass


def parse_test(lines):
    while lines and lines[-1].strip() == "":
        lines.pop()
    opcodes = {
        'title': None,
        'doc': [],
        'in': [],
        'out': [],
    }
    for line in lines:
        if line.startswith('#'): continue
        if '#' in line:                # strip trailing comments
            line = line[:line.find('#')]
        sline = line.strip()
        if sline.startswith('='):      # test title
            opcodes['title'] = sline[2:]
        elif sline.startswith(':'):    # test description
            opcodes['doc'].append(sline)
        elif sline.startswith('>'):    # input to send
            opcodes['in'].append(sline[1:].lstrip())
        else:                          # expected output
            opcodes['out'].append(sline)
    return opcodes

def spawn(program_args, use_shell):
    return subprocess.Popen(program_args,
                            shell=use_shell,
                            universal_newlines=True,
                            stdin=subprocess.PIPE,
                            stdout=subprocess.PIPE)


def await_results(program, timeout_seconds=2):
    """
    This polls the child program until it finishes
    executing. If it takes more than =timeout_seconds=,
    kill the program and raise a TimeoutFailure.
    """
    countdown = timeout_seconds * 10
    while program.poll() is None and countdown > 0:
        time.sleep(0.1) # seep for 1/10 of a second
        countdown -= 1
    if countdown == 0:
        program.kill()
        raise TimeoutFailure("<program timed out>")


def send_cmds(program, opcodes):
    for cmd in opcodes['in']:
        program.stdin.write(cmd + "\n")
        program.stdin.flush()

def run_test(program, opcodes):
    send_cmds(program, opcodes)
    # send all the input lines:
    (actual, errs) = program.communicate(timeout=2)
    actual = [line.strip() for line in actual.splitlines()]
    while actual and actual[-1] == "":
        actual.pop()
    if actual != opcodes['out']:
        print()
        print("test [%s] failed" % opcodes['title'])
        print("---- input ----")
        for cmd in opcodes['in']:
            print(cmd)
        print('\n'.join(opcodes['doc']))
        #print("---- expected results ----")
        #print('\n'.join(opcodes['out']))
        print("---- diff from expected ----")
        diff = '\n'.join(list(difflib.Differ().compare(actual, opcodes['out'])))
        print(diff)
        raise TestFailure('output mismatch')

def run_tests(program_args, use_shell):
    num_passed = 0
    try:
        for i, test in enumerate(extract.tests()):
            opcodes = parse_test(test.lines)
            program = spawn(program_args, use_shell)
            run_test(program, opcodes)
            # either it passed or threw exception
            print('.', end='')
            num_passed += 1
        else:
            print()
            print("All %d tests passed." % num_passed)
    except (TimeoutFailure, TestFailure) as e:
        print()
        print("%d tests passed." % num_passed)
        print("Test %d [%s] failed." % (i+1, test.name))


def find_learntris():
    default = "./learntris"
    program_args = sys.argv[1:] if len(sys.argv) >= 2 else [default]
    if "--shell" in program_args: # --shell option
        program_args.remove("--shell")
        return (program_args, True)
    elif os.path.exists(program_args[0]):
        return (program_args, False)
    elif program_args[0] == default:
        print(__doc__)
        raise FileNotFoundError(default)
    else:
        raise FileNotFoundError("%s" % program_args[0])


def main():
    try: cmdline, use_shell = find_learntris()
    except FileNotFoundError as e:
        print('File not found:', e)
    else:
        cmd = cmdline[0]
        try:
            try:
                run_tests(cmdline, use_shell)
            except EnvironmentError as e:
                if e.errno in [errno.EPERM, errno.EACCES]:
                    print(); print(e)
                    print("Couldn't run %r due to a permission error." % cmd)
                    print("Make sure your program is marked as an executable.")
                elif e.errno == errno.EPIPE:
                    print(); print(e)
                    print("%r quit before reading any input." % cmd)
                    print("Make sure you are reading commands from standard input,")
                    print("not trying to take arguments from the command line.")
                else:
                    raise
        except:
            print('-'*50)
            traceback.print_exc()
            print('-'*50)
            print("Oh no! Testris encountered an unexpected problem while")
            print("attempting to run your program. Please report the above")
            print("traceback in the issue tracker, so that we can help you")
            print("with the problem and provide a better error message in")
            print("the future.")
            print()
            print("  https://github.com/LearnProgramming/learntris/issues")
            print()


if __name__ == '__main__':
    main()


# vim: set expandtab:
