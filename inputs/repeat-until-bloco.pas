program repeticao (input, output);
{ lexical level 1 }
    var count: long;
    begin
        count := 1;
        repeat
        begin
            count := count * 2
        end;
        until count > 100
    end.