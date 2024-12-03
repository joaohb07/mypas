program repeticao (input, output);
{ lexical level 1 }
    var count: integer;
    begin
        count := 1;
        repeat
            count := count * 2
        until count > 100
    end.
