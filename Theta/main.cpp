#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <locale.h>
#include <iterator>
#include <fstream>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv) {
	bool exit = false;
	setlocale(LC_ALL, "portuguese-brazilian");
	char entrada[200];
	char entrada2[200];
	int x = 0;
	int i, j;
	FILE * arq;
	
	while(!exit){
		cout << "#";
		cin >> entrada;
		istringstream iss(entrada);
		
		do{
        	string subs;
        	iss >> subs;
        	if(subs != "createhd" && subs != ""){
        		string nome;
        		nome = subs;
        		string cmdSystem ="fsutil file createnew " + nome +".txt 33762";
        		cout << nome + " criado com sucesso" << endl;
        		system(cmdSystem.c_str());
        		arq = fopen("HD1.txt", "w");
				        for(i=0; i < 1024; i++){

							fprintf(arq, "0");
							
							for(j = 0;j < 33;j++){

       							if(i < 20 && j < 1){
									fprintf(arq, "0");
								}
								else if(i >= 20 && j<1){
                                    fprintf(arq, "1");
								}
								else if(j == 32){
									fprintf(arq, "\n");
								}else{
									fprintf(arq, "");
								}
							}
					}
				fclose(arq);
        		x = 1;
        		
        		while(x != 2){
                    long lSize;
        			cout<< "#" + nome + ">";
        			cin >> entrada2;
        			istringstream iss2(entrada2);
				    do
				    {
				        string subs2;
				        iss2 >> subs2;
				        if(subs2 != "create" && subs2 != ""){
				        	string nomeArq;
				        	nomeArq = subs2;
				        	string cmdSystem2 = "copy con " + nome + ".txt";
				        	//system(cmdSystem2.c_str());
				        	cout<<endl;
				        	
				        	arq = fopen("HD1.txt", "r");
				        	fseek (arq , 0 , SEEK_END);
				            lSize = ftell (pFile);
  							rewind (pFile);
				        	
				        	cout << "arquivo "+ nomeArq + " criado" << endl;
				        	x = 2;
						}
				    } while (iss2);
        			
        			fclose(arq);
				}
			}
			
    	} while (iss && x != 1);
    	
		
		if(entrada == "exit"){
			exit = true;
		}
		
	}
	
	return 0;
	system("pause");
}
