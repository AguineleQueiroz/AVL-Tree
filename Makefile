# ALGORITMOS E ESTRUTURAS III - TP1: ESTRUTURAS DE DADOS

# Código desenvolvido na disciplina de AEDs III
#Implementação de uma árvore Binária Balanceada - AVL

#Arvore arvoreAVL
arvoreAVL: arvoreAVL.o
	g++ -o arvoreAVL arvoreAVL.o
	./arvoreAVL
	
arvoreAVL.o: arvoreAVL.cpp
	g++ -c arvoreAVL.cpp

limpararvoreAVL: 
	rm -rf *.o *~ arvoreAVL




	
