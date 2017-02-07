class Point
	attr_accessor :x, :y

	def initialize(x, y)
		@x = x
		@y = y
	end

	def ==(other)
		other.x == @x and
			other.y == @y
	end

	alias eql? ==
end
