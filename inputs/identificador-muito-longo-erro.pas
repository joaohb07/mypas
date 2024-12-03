program teste (input, output);
{ lexical level 1 }
	var x,y: real;
	procedure A234567890123456789A01234567890123(var z: real; w: integer);
	{ lexical level 2 }
		var t: integer;
		begin
			t := z + w * x * y
		end;
	function factorial(n: integer) : integer;
	{ lexical level 2 }
		begin
			if n > 2 then
				{ return factorial(n-1) * n }
				factorial := factorial(n-1) * n
			else
				{ return 1 }
				factorial := 1
		end;
	begin
		y:= x + y
	end.
