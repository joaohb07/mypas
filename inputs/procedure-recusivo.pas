program recursion (input, output);
{ lexical level 1 }
    var x: integer;

    procedure countdown(n: integer);
    { lexical level 2 }
        begin
            if n > 0 then
                begin
                    n := n - 1;
                    countdown(n)
                end
        end;

    begin
        x := 5;
        countdown(x)
    end.
