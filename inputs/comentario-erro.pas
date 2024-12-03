program teste (input, output);
{ lexical level 1 }
	var x,y: real;
	procedure A(var z: real; w: integer);
	{ lexical level 2 }
		var t: integer;
		begin
			t := z + w * x * y
		end;
	
	{ comentario mal 
	
	begin
		y:= x + y
	end.
