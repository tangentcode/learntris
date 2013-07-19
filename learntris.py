from __future__ import print_function # let's keep it 3.x compatible
import sys, os, glob, subprocess

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

def parse_line_data(line):
    spl = line.lstrip().split(" ")
    if spl[0][0] == '$':
        if spl[0][1:] == "dup-line":
            # duplicate line N times
            n = int(spl[1])
            arg = ' '.join(spl[2:])
            return [arg] * n
        else:
            raise SyntaxError("Unknown command '%s' with line: %s" % (spl[0], line))

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
                test.seq.extend(('out', line) for line in parse_line_data(sline))
    return test

def spawn(program_name):
    program = subprocess.Popen([program_name],
			       stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    return program

def run_test(program, test):
    for command in test.seq:
        if command[0] == "in":
            # write input
            program.stdin.write(command[1] + "\n")
        elif command[0] == "out":
            # write and compare output
            ln = program.stdout.readline() # todo: timeout?
            ln = ln.rstrip() # chomp newlines/whitespace
            if command[1] != ln:
                program.terminate()
                raise TestFailure("Output mismatch: expected '%s', got '%s'"
				  % (command[1], ln))
        else:
            program.terminate()
            raise Exception("Unknown command: " + command)

    program.terminate()
    return True

def run(program_name):
    for i,test in enumerate(glob.glob("tests/*.txt")):
        program = spawn(program_name)
        test_obj = parse_test(test)
        print("Running test %d: %s" % (i+1, test_obj.desc))
        if run_test(program, test_obj):
            print("Test %d passed" % (i+1))

def main():
    program_name = "tetris.exe"
    if len(sys.argv) == 2:
        program_name = sys.argv[1]

    if not os.path.exists(program_name):
        print("Error: The tetris program ('%s') doesn't exist." % program_name)
        sys.exit(1)

    run(program_name)

if __name__ == '__main__':
    main()
