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
import sys, os, glob, subprocess, difflib, pprint, time, threading
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
    """
    :: [Str] -> [(Op, Str)] , where Op in { 'in', 'out' }
    """
    while lines and lines[-1].strip() == "": lines.pop()
    for line in lines:
        if line.startswith('#'): continue
        if '#' in line:                # strip trailing comments
            line = line[:line.find('#')]
        sline = line.strip()
        if sline == "":
            yield ('out', sline)
        elif sline[0] == '>':          # input to send
            yield ('in', sline[1:].strip())
        else:                          # expected output
            yield ('out', sline)

def spawn(program_args, use_shell):
    return subprocess.Popen(program_args,
                            shell=use_shell,
                            stdin=subprocess.PIPE,
                            stdout=subprocess.PIPE)

def await_results(childproc, cmds, timeout_seconds=2):
    """
    This runs the child process until it finishes executing,
    *or* until =timeout_seconds= have passed, in which case it
    kills the process and raises a =TimeoutFailure=.

    Return value is (stdout_data, stderr_data), from Popen.communicate().

    Timeout logic adapted from:
    http://stackoverflow.com/questions/1191374/subprocess-with-timeout
    """
    result = []
    def job():
        result.extend(childproc.communicate(cmds))

    thread = threading.Thread(target=job)
    thread.start()
    thread.join(timeout_seconds)

    if thread.is_alive():
        childproc.kill()
        raise TimeoutFailure("<childproc timed out>")
    else:
        return result

def run_test(childproc, opcodes):
    # separate the test script into input and output lines:
    given    = [op[1] for op in opcodes if op[0] == 'in']
    expected = [op[1] for op in opcodes if op[0] == 'out']

    # send all the input lines:
    print("---- sending commands ----")
    cmds = '\n'.join(given) + '\n'

    # let the childproc do its thing:
    print("---- expected results ----")
    for line in expected:
        print(line)

    print("---- awaiting results ----")
    out_text, _ = await_results(childproc, cmds)

    # compare output lines to expected:
    actual = [line.strip() for line in out_text.split("\n")]
    while actual and actual[-1] == "": actual.pop()
    if actual != expected:
        diff = list(difflib.Differ().compare(actual, expected))
        raise TestFailure('output mismatch:\n%s'
                          % pprint.pformat(diff))

def run_tests(program_args, use_shell):
    for i, test in enumerate(extract.tests()):
        program = spawn(program_args, use_shell)
        opcodes = list(parse_test(test.lines))
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
    use_shell = False
    if "--shell" in program_args: # --shell option
        use_shell = True
        program_args.remove("--shell")
    if os.path.exists(program_args[0]):
        return (program_args, use_shell)

    if program_args[0] == default:
        print(__doc__)
    else:
        print("Error: ('%s') not found." % program_args[0])
    return None


def main():
    program_args = find_learntris()
    if program_args: run_tests(program_args[0], program_args[1])

if __name__ == '__main__':
    main()
