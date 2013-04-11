"""
Test of basic interaction with the game.
"""
import time, unittest
from ltclient import client

class BiosTest(unittest.TestCase):

    def setUp(self):
        self.bios = client.connect()
        
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
        self.assertEquals(['. . . . . . . . . .'] * 22, self.bios.next())


if __name__=="__main__":
    unittest.main()
