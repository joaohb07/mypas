program relacionalAninhado (input, output);
{ lexical level 1 }
    var x, y: integer;

    procedure CompareValues(a, b: integer);
    { lexical level 2 }
        var isEqual, isGreater: boolean;

        function CheckEqual(c, d: integer): boolean;
        { lexical level 3 }
            begin
                CheckEqual := c = d
            end;

        function CheckGreaterOrEqual(c, d: integer): boolean;
        { lexical level 3 }
            begin
                CheckGreaterOrEqual := c >= d
            end;

        begin
            isEqual := CheckEqual(a, b);
            isGreater := CheckGreaterOrEqual(a, b);

            if isEqual then
                x := 1
            else if isGreater then
                y := 2
            else
                x := -1
        end;

    begin
        x := 5;
        y := 10;
        CompareValues(x, y)
    end.
