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

Once testris is able to launch your program, this message
will be replaced with instructions for implementing your
first feature.
"""
from __future__ import print_function # let's keep it 3.x compatible
import sys, os, subprocess, difflib, pprint, time
import extract

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
    else: pass


def run_test(program, opcodes):
    # send all the input lines:
    print(opcodes['title'])
    print("---- sending commands ----")
    for cmd in opcodes['in']:
        print(cmd)
        program.stdin.write((cmd + "\n").encode('utf-8'))

    # let the program do its thing:
    print("---- awaiting results ----")
    await_results(program)

    # read all the actual output lines and compare to expected:
    actual = [line.strip() for line in
              program.stdout.read().decode('utf-8').split("\n")]
    while actual and actual[-1] == "":
        actual.pop()
    if actual != opcodes['out']:
        print('\n'.join(opcodes['doc']))
        print("---- expected results ----")
        print('\n'.join(opcodes['out']))
        diff = '\n'.join(list(difflib.Differ().compare(actual, opcodes['out'])))
        raise TestFailure('output mismatch:\n' + diff)

def run_tests(program_args, use_shell):
    for i, test in enumerate(extract.tests()):
        program = spawn(program_args, use_shell)
        opcodes = parse_test(test.lines)
        print("Running test %d: %s" % (i+1, test.name))
        try:
            run_test(program, opcodes)
            print("Test %d passed" % (i+1))
        except (TimeoutFailure, TestFailure) as e:
            print("Test %d failed: %s" % (i+1, e))
            break
        print("\n") # add 2 blank lines between tests

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
    else:
        print("Error: ('%s') not found." % program_args[0])
    return None


def main():
    program_args = find_learntris()
    if program_args: run_tests(program_args[0], program_args[1])

if __name__ == '__main__':
    main()


# vim: set expandtab:
