program nestedFunctionsInProc (input, output);
{ lexical level 1 }
    var total: real;

    procedure Compute(a: real);
    { lexical level 2 }
        var factor: real;

        function Square(x: real): real;
        { lexical level 3 }
            begin
                Square := x * x
            end;

        function Cube(x: real): real;
        { lexical level 3 }
            begin
                Cube := x * Square(x)
            end;

        begin
            factor := 2.0;
            total := Cube(a) * factor
        end;

    begin
        total := 0.0;
        Compute(3.0)
    end.
