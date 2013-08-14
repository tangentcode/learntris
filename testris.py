#!/usr/bin/env python
"""
Testris is the test runner for Learntris. Learntris is 
the part *you* write, in whatever language you prefer.

If you're seeing this message when you tried to run
testris.py, it means testris can't find your code!

Your first step is to write a *console-mode* program
(one that does absolutely nothing!) and tell testris
where to find it:

    ./testris.py [/path/to/learntris]

The path should refer to a physical file on disk, so if
you need command line arguments, create a wrapper program.
The default path is "./learntris".

Once testris is able to launch your program, this message
will be replaced with instructions for implementing your
first feature.
"""
from __future__ import print_function # let's keep it 3.x compatible
import sys, os, glob, subprocess, difflib, pprint, time

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

def parse_line_data(line):
    spl = line.lstrip().split(" ")
    if spl[0][0] == '$':
        if spl[0][1:] == "dup-line":
            # duplicate line N times
            n = int(spl[1])
            arg = ' '.join(spl[2:])
            return [arg] * n
        else:
            raise SyntaxError("Unknown command '%s' with line: %s"
                              % (spl[0], line))

    return [line]

def parse_test(test_file):
    # todo: fragile
    test = Test()
    with open(test_file, "r") as fp:
        n = 0

        for line in fp:
            n += 1
            if '#' in line:
                line = line[:line.find('#')] # strip comments
            sline = line.strip()

            if sline == "":
                continue # skip empty lines
            elif sline.startswith("TEST: "):
                test.desc = sline[len("TEST: "):]
            elif sline[0] == '>':
                # input
                test.seq.extend(('in', line) for line in
				parse_line_data(sline[1:].lstrip()))
            else:
                test.seq.extend(('out', line)
                                for line in parse_line_data(sline))
    return test

def spawn(program_name):
    return subprocess.Popen([program_name],
                            stdin=subprocess.PIPE,
                            stdout=subprocess.PIPE)


def await_results(program, timeout_seconds=5):
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
        raise TimeoutFailure()
    else: pass

def run_test(program, test):
    # separate the test script into input and output lines:
    given    = [cmd[1] for cmd in test.seq if cmd[0] == 'in']
    expected = [cmd[1] for cmd in test.seq if cmd[0] == 'out']

    # send all the input lines:
    for cmd in given:
        program.stdin.write(cmd + "\n")

    # let the program do its thing:
    await_results(program)

    # read all the actual output lines, and compare to expected:
    actual = program.stdout.read()
    diff = list(difflib.Differ().compare(actual, expected))
    if diff:
        raise TestFailure('output mismatch: %s'
                          % pprint.pformat(diff))
    return True

def run_tests(program_name):
    for i,test in enumerate(sorted(glob.glob("tests/*.txt"))):
        program = spawn(program_name)
        test_obj = parse_test(test)
        print("Running test %d: %s" % (i+1, test_obj.desc))
        if run_test(program, test_obj):
            print("Test %d passed" % (i+1))

def find_learntris():
    default = "./learntris"
    path = sys.argv[1] if len(sys.argv) == 2 else default
    if os.path.exists(path):
        result = path
    else:
        result = None
        if path == default:
            print(__doc__)
        else:
            print("Error: ('%s') not found." % path)
    return result


def main():
    path = find_learntris()
    run_tests(path)

if __name__ == '__main__':
    main()
