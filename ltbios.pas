{ basic input/output for learntris.
  (reference implementation in object pascal) }
program ltbios;

procedure print;
  var y, x : integer;
begin
  for y := 22 downto 1 do begin
    for x := 1 to 10 do write('. ');
    writeln;
    flush(output);
  end
end;

var
  cmd  : string;
  done : boolean = false;
begin
  repeat
    write( '> ' ); readln( cmd );
    case cmd[1] of
      'q' : done := true;
      'p' : print;
      else
    end
  until done
end.
