#!/usr/bin/env ruby
class Tetromino
	require "sqlite3"
	require_relative "point"
	attr_accessor :type, :color, :size, :points

	DATABASE_NAME = "tetromino.db"
	TABLE_NAME = "tetromino"
	@@db = SQLite3::Database.open(DATABASE_NAME)
	@@types = @@db.execute("select tet_type from " + TABLE_NAME).flatten

	def initialize(type)
		@type = type
		@color = db_query("tet_color")
		@size = db_query("tet_size")
		# db_query returns a string and we want the actual array
		@points = eval(db_query("tet_points"))
	end

	def db_query(attr)
		# SELECT attr from TABLE_NAME where tet_type = @type
		# Return is a doubly nested array, which is why we call first twice
		@@db.execute("select " + attr + " from " + TABLE_NAME + " where tet_type = ?", @type).first.first
	end

	def self.db
		@@db
	end

	def self.types
		@@types
	end

	def to_s
		ary = Array.new(@size) { Array.new(@size, '.')}
		s = ""

		@points.each do |x,y|
			ary[x][y] = @color
		end

		ary.each do |row|
			row.each_with_index do |c, index|
				if index != 0
					s += ' '
				end
				s += c
			end
			s += "\n"
		end

		s
	end

	if __FILE__ == $0
		t = Tetromino.new("I")
		puts t.to_s
	end
end
