"""
extract the tests from the outline.
"""

class CuteLittleStateMachine:
    # This state machine is overkill for such a simple little
    # parser, but I was prototyping something.

    def __init__(self):
        self.states = [
            (0, self.on_meta_line),
            (1, self.on_test_line)]
        self.transitions = [
            (0, '#+begin_src', 1, self.on_begin_test),
            (1, '#+end_src',   0, self.on_end_test)]
        self.state = 0
        self.count = 0
        self.io = None

    def __call__(self, line):
        match = [row[2:] for row in self.transitions 
                 if row[0]==self.state and line.startswith(row[1])]
        if match: # match :: [( to_state, method )] of len 1
            self.state = match[0][0]
            match[0][1]()
        else: self.states[self.state][1](line)

    def on_meta_line(self, line):
        pass
    
    def on_begin_test(self):
        self.count += 1
        self.io = open("tests/test{0:03}.py".format(self.count), 'w')

    def on_test_line(self, line):
        self.io.write(line)

    def on_end_test(self):
        self.count += 1
        self.io.close()


if __name__=="__main__":
    map(CuteLittleStateMachine(),
        file("testplan.org"))
