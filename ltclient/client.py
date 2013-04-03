"""
client for ltbios, the basic input/output system for learntris.

The ltbios program is something /you/ write so that the tests
can talk to your code.
"""
import os, sys
try:
    try: import pexpect as expect
    except ImportError: import winpexpect as expect
except ImportError:
    print "Unable to load pexpect."
    print "Please run pip install pexpect."
    sys.exit(-1)

#-----------------------------------------------------

class BIOS(object):
    def __init__(self, path):
        self.game = None
        self.connect(path)

    def connect(self, path):
        try: self.game = expect.spawn(path)
        except Exeption as e:
            # sadly, the pexpect errors aren't very helpful :/
            raise IOError("unable to spawn '{0}': {1}"
                          .format(path, e.message))
    def send(self, *lines):
        """send lines to the repl."""
        map(self.game.sendline, lines)

    def read(self):
        """Send a string to the repl."""
        self.game.expect('> ')
        return self.game.before

PATH = './ltbios'
try:
    if os.path.exists(PATH):
        bios = BIOS(PATH)
    else: raise IOError('{0} not found'.format(PATH))
except Exception as e:
    print "------------------------------------"
    print "*ERROR* Unable to connect to ltbios."
    print "Please make sure the file './ltbios'"
    print "exists and is an exectuable program."
    print "------------------------------------"
    print repr(e)
    print "------------------------------------"
    sys.exit(-1)
