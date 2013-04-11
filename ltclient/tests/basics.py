"""
Test of basic interaction with the game.
"""
import time, unittest
from ltclient import client

EMPTYROW = ( '. . . . . . . . . .' )
JUNKROWS = [ 't t t . s l l . z j' ,
             '. t o o s s l z z j' ,
             '. . o o . s l z j j' ,
             'i i i i . . i i i i' ]

class BiosTest(unittest.TestCase):

    def setUp(self):
        self.bios = client.connect()
        self.maxDiff = None
        
    def test_q(self):
        """
        q : should quit the system
        """
        self.bios.send('q')
        for i in range(10):
            if self.bios.connected: time.sleep(0.1)
        self.failIf(self.bios.connected,
                    "Disconnect failed. Did you implement the 'q' command?")

    def test_p(self):
        """
        p : should print the current game state
        """
        self.bios.send('p')
        self.assertEquals([EMPTYROW] * 22, self.bios.next())

    def test_g(self):
        """
        g (given) : should read the game state
        """
        given = (18 * [EMPTYROW] + JUNKROWS)
        self.bios.send('g')
        self.bios.send(*given)
        self.bios.send('p')
        self.assertEquals(given, self.bios.next())

if __name__=="__main__":
    unittest.main()
