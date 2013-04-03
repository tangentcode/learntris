"""
Basic interaction with the game.
"""
import time, unittest
from ltclient import client

class BiosTest(unittest.TestCase):
    def setUp(self):
        self.bios = client.connect()
        
    def test_q(self):
        self.bios.send('q')
        for i in range(10):
            if self.bios.connected: time.sleep(0.1)
        self.failIf(self.bios.connected,
                    "Disconnect failed. Did you implement the 'q' command?")

if __name__=="__main__":
    unittest.main()
