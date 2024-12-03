program condicional (input, output);
{ lexical level 1 }
    var num: integer;
    begin
        num := 7;
        if num > 2  then
            begin
                { Number is even }
                num := num + 1
            end
        else
            begin
                { Number is odd }
                num := num * 2
            end
    end.
