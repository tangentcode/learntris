The Learntris Challenge
=======================

Learntris is a set of automated tests that will guide you through implementing your own version of
[Tetris](https://en.wikipedia.org/wiki/Tetris), that famous Soviet falling blocks game.

The game is a fairly small project suitable for beginners
who understand the basic concepts of programming, or for
veteran developers looking to pick up a new language.

Along the way, it will expose you to some common software
engineering tools, practices, and buzzwords that might not be familiar
to you:

 * Version control with [git](https://en.wikipedia.org/wiki/Git_(software))
 * [Test-Driven/Behavior-Driven Development](https://en.wikipedia.org/wiki/Test-driven_development)
 * Process automation
 * Implementing an interface/specification
 * [Inter-Process Communication (IPC)](https://en.wikipedia.org/wiki/Inter-process_communication)
 * Creating a simple [domain-specific language](https://en.wikipedia.org/wiki/Domain-specific_language)

**Note:** This is not a tutorial, in that it will not tell you *how* to do things, just guide you on *what* to do -- the implementation is up to you. Are you up for the challenge?

While the tests are about implementing a video game, the real purpose 
of this exercise is to force you to "fend for yourself" on
a project, without relying on tutorial-style guidance.

Instead, the tests present a series of problems that you
will need to solve in order to implement the game.

*It is entirely up to you how to write the code.* Design it however you wish -- there are no wrong answers.

While the tests themselves are written in Python, you are free to implement your game in any language you like.
Python will run the tests on your program regardless of what language it is in.

## Getting Started

The first step is to git clone or fork this repository and run `testris.py`.
You will need a recent version of [Python](https://www.python.org/), preferably Python 3.2 or later, but Python 2.x works fine as well.
(Remember: Python is *only* for the test runner. You can use any language you want to
write your implementation.)

The output of `testris.py` will tell you what needs to be done at every
step along the way. Just keep running it, and do what it guides you to do.
Please read **[Understanding the Test Results](https://github.com/LearnProgramming/learntris/wiki/Understanding-the-Test-results)** briefly before getting started! The wiki here also has a couple pages on [Getting Set Up](https://github.com/LearnProgramming/learntris/wiki/Getting-Set-Up).

**Important**: The tests expect you to receive commands as input over [*standard input*](http://www.linfo.org/standard_input.html) (commonly called *stdin*), e.g. via `input()` in Python, `scanf/getline/getchar/etc` in C, and so on. This is *not* the same thing as command-line arguments that you pass via the terminal: it's what you're using when you type in input to a running program.

If you get stuck, please come join us in [our IRC chatroom](https://webchat.freenode.net/?channels=learnprogramming) (links to a Web chat) at `#learnprogramming` on `irc.freenode.net`, and we'll try to help you sort it out.

Good luck, and most importantly: have fun!
