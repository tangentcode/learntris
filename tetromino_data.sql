create table if not exists tetromino (
	tet_type text primary key not null,
	tet_color text not null,
	tet_size int not null,
	tet_points text not null);

	insert or replace into tetromino (tet_type, tet_color, tet_size, tet_points) values 
	("I", "c", 4, "[[1,0],[1,1],[1,2],[1,3]]"),
	("J", "b", 3, "[[0,0],[1,0],[1,1],[1,2]]"),
	("T", "m", 3, "[[0,1],[1,0],[1,1],[1,2]]"),
	("L", "o", 3, "[[0,2],[1,0],[1,1],[1,2]]"),
	("S", "g", 3, "[[0,1],[0,2],[1,0],[1,1]]"),
	("Z", "r", 3, "[[0,0],[0,1],[1,1],[1,2]]"),
	("O", "y", 2, "[[0,0],[0,1],[1,0],[1,1]]");
