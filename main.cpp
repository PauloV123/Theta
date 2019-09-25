//Paulo Victor Ranieri Setúbal 22117021-0

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <iterator>
#include <fstream>
#include <stdio.h>

using namespace std;
int bytes;

void preenche(char HD[1024][32]){ //Preenche a matriz HD
	int i,j;
	for(i=0; i < 1024; i++){
		for(j = 0;j < 33;j++){

			if(i <= 20 && j == 1){
				HD[i][j] = '0';
 				
			}
			else if(i > 20 && j==1){
                HD[i][j] = '1';
                
			}
			else if(j == 0){
				HD[i][j] = '0';
			}else{
				HD[i][j] = ' ';
			}
		}
	}
}

int insereNoHD(string nome, char HD[1024][32]){ //Insere no HD.txt
	string NomeArq = nome +".txt";
	string comando = "fsutil file createnew " + nome + ".txt 33762";
	system(comando.c_str());
	FILE* arq = fopen(NomeArq.c_str(), "w");
	if(arq == NULL){
		printf("ERRO");
		return 1;
	}
	
	//escrevendo com base na matriz HD
	for(int i = 0; i< 1024; i++){
		fprintf(arq, "%c", HD[i][0]);//0
		for(int j =0; j<32;j++){
			if(i<20 && j < 1){
				fprintf(arq, "%c", HD[i][j+1]);//0
			}else if(i>=20 && j<1){
				fprintf(arq, "%c", HD[i][j+1]);//1
			}else if(j == 31){
				fprintf(arq, "\n");//pula linha
			}else{
				fprintf(arq, "%c", HD[i][j+1]);//vazio
			}
		}
	}
	fclose(arq);
	return 0;
}

void create(string nomeArquivo,string nomeHD,char HD[1024][32]){
	char entrada[200];
	cin >> entrada;
	int taFree = -1; //procura a linha livre
	int bloco = 0; 
	int p = 0;
	for(int i = 0; i < 1024 && taFree == -1 ;i++){
		for(int j = 0; j<32; j++){
			if(HD[i][0] == '0' && HD[i][1] =='1'){
				taFree = i;
				bloco = i;
			}
		}
	}
	
	if(taFree!= -1){ //encontrou uma linha livre
		int coluna = 8; //conteudo inicia na linha 8
		while(entrada[p] != 0){ //enquanto o conteudo não zerar
			HD[taFree][0] = '1';
			if(coluna < 30){
				HD[taFree][coluna] = entrada[p];
				coluna++;
				p++;
			}else{
				HD[taFree][coluna] = entrada[p];
				p++; // continuação na proxima linha
				char temporario[4];
				//lógica pra passar o número pra um char
				if(taFree < 99){
					temporario[0] = '0';
					temporario[1] = '0';
					temporario[2] = ((taFree/10)) +'0';
					temporario[3] = ((taFree+1)%10)+'0';
				}else if(taFree < 999){
					temporario[0] = '0';
					temporario[1] = ((taFree%100)/10) + '0';
					temporario[2] = ((taFree)/10) + '0';
					temporario[3] = (taFree+1)%10 + '0';
				}else{
					temporario[0] = ((taFree%1000)/100) + '0';
					temporario[1] = ((taFree%100)/10) + '0';
					temporario[2] = ((taFree)/10) + '0';
					temporario[3] = (taFree+1)%10 + '0';
				}
				
				//escreve aonde ta sendo imprimido isso
				for(int i = 4; i<8;i++){
					HD[taFree][i] = temporario[i-4];
				}
				
				taFree++;
				HD[taFree][0] = '1';
				coluna = 8;
			}

		}
		for(int i = 4; i<8;i++){
			HD[taFree][i] = '0';
		}


		
	}else{
		//se der erro
		cout << "Erro: Sem espaco para arquivos\n";
	}
	
	//Coloca o nome do Arquivo
	taFree = -1;
	char temporario[200];
	strcpy(temporario,nomeArquivo.c_str());
	p = 0;
	for(int i =0;i<1024 && taFree == -1;i++){
		for(int j = 0; j<32; j++){
			if(HD[i][0]=='0' && HD[i][1]=='0'){
				taFree = i;
			}
		}
	}

	if(taFree!=-1){
		char temP[4];
		//lógica pra passar o número pra um char
		if(bloco < 99){
			temP[0] = '0';
			temP[1] = '0';
			temP[2] = ((bloco/10)) +'0';
			temP[3] = ((bloco)%10)+'0';
		}else if(bloco < 999){
			temP[0] = '0';
			temP[1] = ((bloco%100)/10) + '0';
			temP[2] = ((bloco)/10) + '0';
			temP[3] = (bloco)%10 + '0';
		}else{
			temP[0] = ((bloco%1000)/100) + '0';
			temP[1] = ((bloco%100)/10) + '0';
			temP[2] = ((bloco)/10) + '0';
			temP[3] = (bloco)%10 + '0';
		}
		//escreve no arquivo
		for(int i = 8; i < 12;i++){
			HD[taFree][i] = temP[i-8];
		}
		
		//Quantidade de Byts
		int tam = 0;
		for(int i = 0; entrada[i] != 0; i++){
			tam++;
		}
		
		bytes = tam;
		//lógica pra passar o número pra um char
		if(tam < 99){
			temP[0] = '0';
			temP[1] = '0';
			temP[2] = (tam/10) +'0';
			temP[3] = (tam%10)+'0';
		}else if(tam < 999){
			temP[0] = '0';
			temP[1] = ((tam%100)/10) + '0';
			temP[2] = ((tam)/10) + '0';
			temP[3] = (sizeof(entrada))%10 + '0';
		}else{
			temP[0] = ((tam%1000)/100) + '0';
			temP[1] = ((tam%100)/10)+ '0';
			temP[2] = (tam/10) + '0';
			temP[3] = (tam%10) + '0';
		}
		//escreve no arquivo
		for(int i = 12; i < 16; i++){
			HD[taFree][i] = temP[i-12];
		}


		for(int i = 0;i < 32;i++){
			if(i == 0){
				HD[taFree][i] = '1';
			}else if(i == 2){
				HD[taFree][i]='0';
			}else if(i >= 16 && i <= 31 && temporario[p]!=0){
				HD[taFree][i] = temporario[p];
				p++;
			}else if(i >= 4 && i <= 7){
				HD[taFree][i] = '0';
			}
		}
	}
	
	insereNoHD(nomeHD,HD);
}

int main(int argc, char** argv) {
	
	bool exit = false; //variavel que ve se a entrada é "exit"
	char HD[1024][32];
	string entrada; //entrada que pega o comando
	string entrada2; //entrada do nome
	string nomeHD; //nome do HD
	preenche(HD);
	
	while(true){
		if(!exit){
			cout << "#";
		}else{
			cout <<"#"<< nomeHD << ">";
		}
		
		cin >> entrada;
		
		//pra sair do código
		if(entrada == "exit"){
			break;
		}
		
		cin >> entrada2;
		
		//primeira parte
		if(entrada == "createhd"){
			
			insereNoHD(entrada2, HD);
			nomeHD = entrada2;
			exit = true;
			cout << "Arquivo " << entrada2 << ".txt criado com sucesso" << endl;
		
		
		//segunda parte
		}else if(entrada == "create"){
			
			create(entrada2,nomeHD,HD);
			cout << "Arquivo criado com " << bytes << " sucesso" << endl;
			
		}else{
			continue;
		}
	}
	return 0;
	system("pause");
}
