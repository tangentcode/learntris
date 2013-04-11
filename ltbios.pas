{ basic input/output for learntris.
  (reference implementation in object pascal) }
program ltbios;

var
  cmd  : string;
  done : boolean = false;
begin
  repeat
    write( '> ' ); readln( cmd );
    case cmd[1] of
      'q' : done := true;
      else
    end
  until done
end.
