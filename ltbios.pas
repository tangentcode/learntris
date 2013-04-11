{ basic input/output for learntris.
  (reference implementation in object pascal) }
program ltbios;

const
  xmax =  9;
  ymax = 21;
var
  grid : array[ 0..xmax, 0..ymax ] of char;
  y, x : integer;

procedure init;
begin
  for y := ymax downto 0 do
    for x := 0 to xmax do grid[ x, y ] := '.';
end;

procedure print;
begin
  for y := ymax downto 0 do begin
    for x := 0 to xmax do write( grid[ x, y ], ' ' );
    writeln;
  end
end;

procedure given;
  var space : char;
begin
  for y := ymax downto 0 do begin
    for x := 0 to xmax - 1 do begin
      read( grid[ x, y ] );
      read( space );
    end;
    read( grid[ xmax, y ] );
    readln;
  end;
end;

var
  cmd  : string;
  done : boolean = false;
begin
  init;
  repeat
    write( '> ' ); readln( cmd );
    case cmd[1] of
      'q' : done := true;
      'p' : print;
      'g' : given;
      else
    end
  until done
end.
