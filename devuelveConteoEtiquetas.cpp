#include <stdio.h>
#include <string>
#include <map>
#include<bits/stdc++.h>
#include <sys/types.h> 
#include <unistd.h> 

using namespace std;

typedef pair<string, int> cuentaTags;

map<string, int> archivo;

int main (){

	//lectura del archivo por lineas	
	char linea[1024];
	FILE *fichero;

	//variables para conteo de etiquetas
	string lineaS;
	int tamLinea;
	char tag[50]="";
	int tamTag = 0;
	int x = 0;
	int caso = 0;
	
	fichero = fopen("Archivo.ht", "r");
	//lee linea por linea y la reparte a cada hijo
	while(fgets(linea, 1024, (FILE*) fichero)){
		
		lineaS = (string)linea; //cast a string
		transform(lineaS.begin(), lineaS.end(), lineaS.begin(), ::toupper); //convierte a uppercase
		tamLinea = lineaS.length(); //tamano de linea
		if( ! fork() ){ // es hijo
			
			//obtiene cada etiqueta y la almacena en un diccionario
			while(x<tamLinea){

				if(lineaS[x]=='<'){ //encontro primer caracter de la etiqueta HTML
					caso = 0;
				}

				switch(caso){
					
					case 0: //inicia para guardar etiqueta
						tamTag = 0;
						caso = 1;
						break;
					case 1: //avanza en la linea hasta encontrar el fin de la etiqueta HTML
						if(lineaS[x]==' ' || lineaS[x]=='>'){ //encontro el final de la etiqueta
							archivo.insert( cuentaTags( (string)tag , archivo[(string)tag]++ )); //guarda en el diccionario
							//limpia variables
							for(int y=0;y<tamTag;y++){ 
								tag[y] = '\0';
							}
							tamTag = 0;
							caso = 2;
						}else{ //no ha encontrado final de etiqueta
							tag[tamTag] = lineaS[x];
							tamTag++;
						}
						break;
					default:
						break;
				}
				
				x++;
			}
			
		}else{
			break;
		}
	}
	fclose(fichero);

	for(std::map<string,int>::iterator it=archivo.begin(); it!=archivo.end(); ++it){
		std::cout << it->first << " => " << it->second << '\n';		
	}

	

	return 0;

}
