program teste (input, output);
{ lexical level 1 }
	var x,y: integer;
	procedure A(var z: integer; w: integer);
	{ lexical level 2 }
		var t: integer;
		begin
			t := z + w * x * y
		end;
	function factorial(n: integer) : integer;
		begin
			if n > 2 then
				factorial := factorial(n-1) * n
			else
				factorial := 1
		end;
	begin
		y:= x + y
	end.
