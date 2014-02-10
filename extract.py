"""
Implements a finite state machine to extract the learntris
test descriptions from testplan.org.

The org file format is described here:

  http://orgmode.org/worg/dev/org-syntax.html

However, there is no need to fully parse the outline
structure, since we are only interested in the actual
test cases, and these are clearly marked off by lines
in the following format:

   #+name: testname
   #+begin_src
    <test code winds up here>
   #+end_src

Test lines are simple sequences of lines in the
following format:

- Lines that begin with ">" are input lines.
  The test runner will send these to your program.

- Lines that begin with "'" are test descriptions,
  explaining the purpose of the test to the user.

- The "#" character indicates a comment, which is
  shown to the user but not part of the expected
  output.

- The "\" character can be used to escape any of
  these special characters (including itself).

"""
from __future__ import print_function
from collections import namedtuple
import os

TestDescription = namedtuple("TestDescription", ['name', 'lines'])

class TestReaderStateMachine:
    """
    A simple finite state machine to extract tests from an outline.
    """
    def __init__(self):
        self.states = [
            (0, self.do_nothing),
            (1, self.on_test_code)]
        self.transitions = [
            (0, '#+name:', 0, self.on_test_name),
            (0, '#+begin_src', 1, self.on_begin_test),
            (1, '#+end_src',   0, self.on_end_test)]
        self.state = 0
        self.lineno = 0 # line count
        self.io = None  # file object
        self.next_name = self.prev_name = ""
        self.test_names = []
        self.tests = [] # collected tests

    def __call__(self, line):
        """
        Act as a callable, allowing map() over an input stream.
        """
        self.on_line(line)

    #-- event handlers -----------------------------------------

    def on_line(self, line):
        self.lineno += 1
        match = [row[2:] for row in self.transitions 
                 if row[0]==self.state and line.startswith(row[1])]
        if match: # match :: [( to_state, method )] of len 1
            self.state = match[0][0]
            match[0][1](line)
        else: self.states[self.state][1](line)

    def do_nothing(self, line):
        pass
    
    def on_test_name(self, line):
        self.next_name = line.split(":")[1].strip()
        assert self.next_name not in self.test_names, (
            "duplicate name {0!r} on line {1}"
            .format(self.next_name, self.lineno))
        self.test_names.append(self.next_name)

    def on_begin_test(self, line):
        assert self.next_name != self.prev_name, (
            "missing or duplicate name for test on line {0}"
            .format(self.lineno))
        self.tests.append(TestDescription(self.next_name, []))
        self.focus = self.tests[-1].lines
        self.prev_name = self.next_name

    def on_test_code(self, line):
        self.focus.append(line)

    def on_end_test(self, line):
        pass

    #-- main public interface ----------------------------------

    def extract_tests(self, path):
        """
        Generates a sequence of TestDescription named tuples:
        Format is: (name:Str, lines:[Str])
        """
        for line in open(path): self(line)
        return self.tests

def tests(path=None):
    """
    Convenience function to instantiate a TestReaderStateMatchine
    and invoke .extract_tests on the given path.
    """
    if path is None:
        path = os.path.join(os.path.dirname(__file__), 'testplan.org')
    return TestReaderStateMachine().extract_tests(path)

if __name__=="__main__":
    if not os.path.exists('tests'): os.mkdir('tests')
    for i, test in enumerate(tests()):
        path = "tests/test{0:03}.txt".format(i)
        print("generating '{0}' in {1}"
              .format(test.name, path))
        io = open(path, 'w')
        for line in test.lines:
            io.write(line)
        io.close()
