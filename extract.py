"""
extract the tests from the outline.
"""

class CuteLittleStateMachine:
    # This state machine is overkill for such a simple little
    # parser, but I was prototyping something.

    def __init__(self):
        self.states = [
            (0, self.do_nothing),
            (1, self.on_test_code)]
        self.transitions = [
            (0, '#+name:', 0, self.on_test_name),
            (0, '#+begin_src', 1, self.on_begin_test),
            (1, '#+end_src',   0, self.on_end_test)]
        self.state = 0
        self.test_names = []
        self.count = 0  # test count
        self.lineno = 0 # line count
        self.io = None  # file object
        self.next_name = self.prev_name = ""

    def __call__(self, line):
        """
        This makes the machine callable, allows us to map() it over the input.
        """
        self.lineno += 1
        match = [row[2:] for row in self.transitions 
                 if row[0]==self.state and line.startswith(row[1])]
        if match: # match :: [( to_state, method )] of len 1
            self.state = match[0][0]
            match[0][1](line)
        else: self.states[self.state][1](line)

    def do_nothing(self, line):
        pass
    
    def on_begin_test(self, line):
        assert self.next_name != self.prev_name, \
            "missing or duplicate name for test on line {0}".format(self.lineno)
        self.count += 1
        self.io = open("tests/test{0:03}.txt".format(self.count), 'w')
        self.prev_name = self.next_name

    def on_test_name(self, line):
        self.next_name = line.split(":")[1].strip()
        assert self.next_name not in self.test_names, \
            "duplicate name {0:r} on line {0}".format(self.next_name, self.lineno)
        self.test_names.append(self.next_name)

    def on_test_code(self, line):
        self.io.write(line)

    def on_end_test(self, line):
        self.count += 1
        self.io.close()


if __name__=="__main__":
    map(CuteLittleStateMachine(),
        file("testplan.org"))
