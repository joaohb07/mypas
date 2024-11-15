###################################################
# Compiladores - Noturno - 2024
# Professor Eraldo Pereira Marinho
# 
# Mypas
# 
# Grupo:
# Cristian Santos de Castro
# João Henrique Botelho
# João Pedro Brum Terra
###################################################
CFLAGS = -I. -g

relocatable = mypas.o lexer.o parser.o keywords.o

mypas: $(relocatable)
	$(CC) -o mypas $(relocatable)
clean: 
	$(RM) *.o
mostlyclean:
	$(RM) *~ mypas

