"""
client for ltbios, the basic input/output system for learntris.

The ltbios program is something /you/ write so that the tests
can talk to your code.
"""
import os, sys, time
try:
    try: import pexpect as expect
    except ImportError: import winpexpect as expect
except ImportError:
    print "Unable to load pexpect."
    print "Please run 'pip install pexpect'."
    sys.exit(-1)

#-----------------------------------------------------

class BIOS(object):
    def __init__(self, path):
        self.game = None
        self.connect(path)
        self.game.expect('> ')

    def connect(self, path):
        """
        :: Either IO() Error
        """
        try: self.game = expect.spawn(path)
        except Exception as e:
            # sadly, the pexpect errors aren't very helpful :/
            raise IOError("unable to spawn '{0}': {1}"
                          .format(path, e.message))

    def send(self, *lines):
        """
        :: *lines -> IO()
        Send lines to the REPL.
        """
        for line in lines:
            self.game.sendline(line)
            self.game.expect(line)

    def next(self):
        """
        :: [String]
        read a series of lines from the repl.
        """
        self.game.expect('> ', timeout=10)
        lines = self.game.before.split("\r\n")
        lines = [line.strip() for line in lines]
        return [line for line in lines if line] # remove blanks

    @property
    def connected(self):
        """
        :: Bool
        True when properly connected to the game.
        """
        return self.game and self.game.isalive()

PATH = './ltbios'
def connect():
    """
    :: Either BIOS Error
    """
    try:
        if os.path.exists(PATH):
            return BIOS(PATH)
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

# for convenience:
bios = connect()
def send(*lines): bios.send(*lines)
def next(): return bios.next()

if __name__=="__main__":
    if bios.connected:
        print "Successfully connected. Disconnecting."
        bios.send('q')
        # wait up to 5 seconds for disconnect:
        for i in range(10):
            if bios.connected: time.sleep(0.1)
        if bios.connected:
            print "Disconnect failed. Did you implement the 'q' command?"
        else: print "Done!"
