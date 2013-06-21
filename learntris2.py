import sys, os, glob, subprocess

class Test:
	def __init__(self):
		self.desc = ""
		self.input = []
		self.output = []

	def __repr__(self):
		return "<Test: " + self.desc + ">"

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
		onInput = False
		onOutput = False
		n = 0

		for line in fp:
			n += 1
			sline = line.strip()
			if '#' in line:
				line = line[:line.find('#')] # strip comments

			if sline == "":
				continue # skip empty lines
			elif sline == "INPUT":
				onInput = True
			elif sline == "OUTPUT":
				onInput = False
				onOutput = True
			elif not onInput and not onOutput and sline.startswith("TEST: "):
				test.desc = sline[len("TEST: "):]
			elif onInput and sline[0] == '>':
				test.input.extend(parse_line_data(sline[2:]))
			elif onInput:
				raise SyntaxError("Can't parse line %d - unknown line: %s" % (n, line))
			elif onOutput:
				test.output.extend(parse_line_data(sline))
	return test

def spawn(program_name):
	return None

def run_test(program, test):
	print "test:", test
	print "in:"
	print test.input
	print "out:"
	print test.output

def run(program_name):
	for test in glob.glob("tests/*.txt"):
		program = spawn(program_name)
		test_obj = parse_test(test)
		run_test(program, test_obj)

def main():
	program_name = "tetris.exe"
	if len(sys.argv) == 2:
		program_name = sys.argv[1]

	# if not os.path.exists(program_name):
	# 	print "Error: The tetris program ('%s') doesn't exist." % program_name
	# 	sys.exit(1)

	run(program_name)

if __name__ == '__main__':
	main()