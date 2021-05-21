/*
	Linguagens e Ambientes de Programação - Projeto de 2020/2021

	Imageomatic module body

largura maxima = 100 colunas
tab = 4 espaços
0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789

	Este ficheiro constitui apenas um ponto de partida para o
	seu trabalho. Todo este ficheiro pode e deve ser alterado
	à vontade, a começar por este comentário.


 IDENTIFICAÇÃO DOS AUTORES -
	Aluno 1: numero, nome
	Aluno 2: numero, nome

Comentarios:

?????????????????????????
?????????????????????????
?????????????????????????
?????????????????????????
?????????????????????????
?????????????????????????

*/

#include "Imageomatic.h"
#include <stdio.h>
#include <stdbool.h>


/*** TYPE Int2 ***/

/* More Int2 functions, in case you need them */




/*** TYPE Pixel ***/

/* More Pixel functions, in case you need them */




/*** TYPE Image ***/

void initialization(void)
{
	// This function is automatically called when the interpreter starts.
	// If you need to perform some initialization, this is the place
	// to write the initialization code.
}

Int2 imageCopy(Image img, Int2 n, Image res)
{
	Int2 i;
	for(i.y = 0; i.y < n.y; i.y++)
	for(i.x = 0; i.x < n.x; i.x++) {
		res[i.x][i.y] = img[i.x][i.y];
	}
	return n;
}
char *getHexa(char linha[256]){
	char *palavra = malloc(6*sizeof(char));
	int i=0;
	while(i<6 ){
		palavra[i]=linha[i];
		i= i+1;
	}
	return palavra;
}
char *getLiteral(char linha[256], int size){
	char *palavra = malloc(sizeof(char)*size);
	int i=0;
	int i2=7;
	while(i<=size){
		palavra[i]=linha[i2];
		i= i+1;
		i2++;
	}
	return palavra;
}

int convertHexaToDecimal(String hex){
    long long decimal, place;
    int i = 0, val, len;

    decimal = 0;

    /* Find the length of total number of hex digit */
    len = strlen(hex);
    len--;

    /*
     * Iterate over each hex digit
     */
    for(i=0; hex[i]!='\0'; i++)
    {
 
        /* Find the decimal representation of hex[i] */
        if(hex[i]>='0' && hex[i]<='9')
        {
            val = hex[i] - 48;
        }
        else if(hex[i]>='a' && hex[i]<='f')
        {
            val = hex[i] - 97 + 10;
        }
        else if(hex[i]>='A' && hex[i]<='F')
        {
            val = hex[i] - 65 + 10;
        }

        decimal += val * pow(16, len);
        len--;
    }
	return decimal;
}
char *getInHexa(String h, int numberPosition){
	char *result = malloc(sizeof(char)*2);
	int n=0;
	for(int i=numberPosition; i<(numberPosition+2); i++){
		result[n++]=h[i];
	}
	return result;
}
char *getRedInHexa(String h){
	return getInHexa(h, 0);
}
char *getGreenInHexa(char *h){
	return getInHexa(h, 2);
}
char *getBlueInHexa(char *h){
	return getInHexa(h, 4);
}

void createImage(Int2 n,String hexa, Image res){
	Int2 i;
	Pixel newP;
	newP.red = convertHexaToDecimal(getRedInHexa(hexa));
	newP.green =convertHexaToDecimal(getGreenInHexa(hexa));
	newP.blue = convertHexaToDecimal(getBlueInHexa(hexa));
	for(i.y=0;i.y<n.y; i.y++){
		for(i.x=0;i.x<n.x; i.x++){
			res[i.x][i.y] = newP;
		}
	}
}

void concatenar(char *original, char *add) {
    while (*original)
        original++;

    while (*add) {
        *original = *add;
        add++;
        original++;
    }
    *original = '\0';
}

Int2 imagePaint(String cor, Int2 n, Image res)
{
	FILE *cores;
	int found=0;
	char linha[256];
	cores = fopen(colorsFileName, "r");
	Byte red, green, blue;
	//String ca = "2fff09";
	Int2 i;
	String hexa;
	String literal;
	Pixel newP;
			//Criar ficheiro
	String dir = "./img/";
	strcat(dir,cor);
	strcat(dir,".png");
	
	const char s[2] = " ";
	while(fgets(linha, 256, cores)!=NULL && found==0){
		
		char *linha_aux = strtok(linha, s);
		int i2=0;
		// separa a linha em duas partes, Hexa e literal
		while( linha_aux != NULL ) {
			if(i2==0){
				strcpy(hexa,linha_aux);
				i2=1;
			}else{
				strcpy(literal,linha_aux);
			}
			linha_aux = strtok(NULL, " ");
  		}
		// a parte literal vem sempre com um caracter a mais, entao eliminanos a ultima posicao ;)
		literal[strlen(literal)-1]='\0';

		// compara se a cor e igual a parte literal ou hexa 
		if(strcmp(hexa, cor)==0 || strcmp(literal, cor)==0){
			
			//convert as partes hexa decimal para inteiro
			newP.red = convertHexaToDecimal(getRedInHexa(hexa));
			newP.green =convertHexaToDecimal(getGreenInHexa(hexa));
			newP.blue = convertHexaToDecimal(getBlueInHexa(hexa));
			// preeenche a Imagem Result com a cor
			for(i.y=0;i.y<n.y; i.y++){
				for(i.x=0;i.x<n.x; i.x++){
					res[i.x][i.y] = newP;
				}
			}
			found = 1;
			imageStore(dir, res, n);
			
			return n;
		}
	}
	//Caso a Cor nao for encontrada no ficheiro de cores, cria a imagem 000
		newP.red = 0;
		newP.green = 0;
		newP.blue = 0;
		for(i.y=0;i.y<n.y; i.y++){
			for(i.x=0;i.x<n.x; i.x++){
				res[i.x][i.y] = newP;
			}
		}
		imageStore(dir, res, n);

		return n;
		
}




Int2 imageNegative(Image img, Int2 n, Image res)
{
	Int2 i;
	for(i.y=0;i.y<n.y; i.y++){
		for(i.x=0;i.x<n.x; i.x++){
			Pixel newI = img[i.x][i.y];
			newI.red = 255 - newI.red;
			newI.green =255- newI.green;
			newI.blue = 255- newI.blue;
			res[i.x][i.y] = newI;
		}
	}
	return n;
}

Int2 imageDroplet(Int2 n, Image res)
{
	Int2 i;
	Int2 centro = int2Half(n);
	for(i.y=0;i.y<n.y; i.y++){
		for(i.x=0;i.x<n.x; i.x++){
			Pixel newI ;
			double dist = int2Distance(centro, i);
			Byte cinza = 0.7*MAX_COLOR+(0.3*sin(dist/20.0)*MAX_COLOR);
			newI.red = cinza;
			newI.green = cinza;
			newI.blue = cinza;
			res[i.x][i.y] = newI;
		}
	}
	String dir = "./img/";
	strcat(dir,"droplet");
	strcat(dir,".png");
	imageStore(dir, res, n);

	return n;
}

Int2 imageMask(Image img1, Int2 n1, Image img2, Int2 n2, Image res) // pre: int2Equals(n1, n2)
{
	Int2 i;
	for(i.y=0;i.y<n1.y; i.y++){
		for(i.x=0;i.x<n1.x; i.x++){
			Pixel newI1 = img1[i.x][i.y];
			Pixel newI2 = img2[i.x][i.y];
			newI1.red = newI1.red*(newI2.red/(double)MAX_COLOR);
			newI1.green = newI1.green*(newI2.green/(double)MAX_COLOR);
			newI1.blue = newI1.blue*(newI2.blue/(double)MAX_COLOR);
			res[i.x][i.y] = newI1;
		}
	}

	return n1;
}

Int2 imageGrayscale(Image img, Int2 n, Image res)
{
	Int2 i;
	for(i.y=0;i.y<n.y; i.y++){
		for(i.x=0;i.x<n.x; i.x++){
			Pixel newI = img[i.x][i.y];
			Byte cinza = (newI.red + newI.green + newI.blue)/3;
			newI.red = cinza;
			newI.green = cinza;
			newI.blue = cinza;
			res[i.x][i.y] = newI;
		}
	}
	return n;
}

Int2 imageRotation90(Image img, Int2 n, Image res)
{

	Int2 i;
	for(i.y=0;i.y<n.y; i.y++){
		for(i.x=0;i.x<n.x; i.x++){
			res[i.y][i.x] = img[i.x][n.y-i.y-1];
		}
	}
	i.x=n.x;
	i.y=n.y;
	n.x=i.y;
	n.y=i.y;
	return n;
}


int convertColorToNewLevel(Byte color,int *n,int size){
	int c = color;
	int i=0;
	int newColor;
	int found =0;
	while (i<size && found==0)
	{
		/* code */
		if(c<n[i]){
			found =1;
			newColor = n[i-1];
		}else if(c == n[1]){
			found =1;
			newColor = c;
		}else if(c>n[size-1]){
			found =1;
			newColor = n[size-1];
		}
		i++;
	}

	return newColor;
}

Int2 imagePosterize(Image img, Int2 n, int factor, Image res)
{
	Int2 i;
	int i2=1;
	int size_vector = pow(2,factor);
	int total = 256/(size_vector);
	int vectorValoresPossiveis[size_vector];
	vectorValoresPossiveis[0]=0;
	while (i2<(size_vector))
	{
		vectorValoresPossiveis[i2] = vectorValoresPossiveis[i2-1] + total;
		i2++;
	}
	
	
	for(i.y=0;i.y<n.y; i.y++){
		for(i.x=0;i.x<n.x; i.x++){
			Pixel newI = img[i.x][i.y];
			
			newI.red = convertColorToNewLevel(newI.red, vectorValoresPossiveis,size_vector);
			newI.green = convertColorToNewLevel(newI.green, vectorValoresPossiveis,size_vector);
			newI.blue = convertColorToNewLevel(newI.blue, vectorValoresPossiveis,size_vector);
			
			res[i.x][i.y] = newI;
		}
	}
	return n;
}

int averageColor(Byte color, int sum, int count) {
	int avColor;
	
	avColor = sum/count;
	return avColor;
}


Int2 imageBlur(Image img, Int2 n, int nivel, Image res)
{
	Int2 i;
	int size = 2*nivel +1;
	int rn=0;
	int gn=0;
	int bn=0;
	for(i.y=0;i.y<n.y; i.y++){
		for(i.x=0;i.x<n.x; i.x++){
			// Inicialização das variaveis para a subMatix
			Int2 iSub = i;
			Image subMatrix;
			Pixel p;
			Pixel pResult;

			//Preencher a sub Matriz

			int sumResult=0;
			// percorrer a subMatrix 
			int c = i.x-nivel;
			int c1 = 0;
			
			for(iSub.y=(i.y-nivel); iSub.y<=size; iSub.y++){
				if(iSub.y>=0 && iSub.y<n.y-1){
					for(iSub.x=(i.x-nivel);iSub.x<size; iSub.x++){
						if (iSub.x>=0 && iSub.x<n.x){
							/* code */
							p = img[iSub.x][iSub.y];
							if(sumResult==0){
								rn = p.red;
								gn = p.green;
								bn = p.blue;
							}else{
								rn = p.red+rn;
								gn = p.green+gn;
								bn = p.blue+bn;
							}
							sumResult++;
							
							//printf("pixel: %d %d %d ) %d %d %d %i\n",p.red,p.green,p.blue,rn,gn,bn,sumResult);

						}
						
					}
				}
			}
			printf("%d %d %d %i\n",rn,gn,bn,sumResult);

			
			/*double r = (rn)/sumResult;
			double g = (gn)/sumResult;
			double b = (bn)/sumResult;

			pResult.red =r;
			pResult.green =g;
			pResult.blue =b;
			res[i.x][i.y] = pResult;*/
			
			
			//fim do fetch da SubMatrix

		}
	}

	return n;
}

Int2 imageHalf(Image img, Int2 n, Image res){
	Int2 i;
	Int2 i2;
	Int2 nFinal = n;
	nFinal.x =n.x/2;
	nFinal.y =n.y/2;
	i2.y=0;
	i2.x=0;
	for(i.y=0;i.y<n.y; i.y=i.y+2){
		for(i.x=0;i.x<n.x; i.x=i.x+2){
				Pixel newI = img[i.x][i.y];
				res[i2.x][i2.y] = img[i.x][i.y];
				i2.x++;
		}
		i2.x=0;
		i2.y++;
	}
	return nFinal;
}

Int2 imageFunctionPlotting(DoubleFun fun, int scale, Int2 n, Image res)
{
	return int2Error;
}

Int2 imageOrderedDithering(Image img, Int2 n, Image res)
{
	#define INDEX_SIDE  8
	Byte indexMatrix[INDEX_SIDE][INDEX_SIDE] = {
					{ 0, 32,  8, 40,  2, 34, 10, 42}, 
					{48, 16, 56, 24, 50, 18, 58, 26},
					{12, 44,  4, 36, 14, 46,  6, 28},
					{60, 28, 52, 20, 62, 30, 54, 22},
					{ 3, 35, 11, 43,  1, 33,  9, 41},
					{51, 19, 59, 27, 49, 17, 57, 25},
					{15, 47,  7, 39, 13, 45,  5, 37},
					{63, 31, 55, 23, 61, 29, 53, 21}
			};
	return int2Error;
}

Int2 imageSteganography(Image img, Int2 n, String s, Image res)
{
	return int2Error;
}


void imageTests(void)
{
	static Image img, img2, res;
	Int2 n;

	// Q
	n = imageLoad("img/frutos.png", img);
	n = imageGrayscale(img, n, res);
	imageStore("img/cinzento.png", res, n);

	// N
	n = imageLoad("img/frutos.png", img);
	n = imageNegative(img, n, res);
	imageStore("img/negativo.png", res, n);	

	// H
	n = imageLoad("img/frutos.png", img);
	n = imageHalf(img, n, res);
	imageStore("img/metade.png", res, n);

	// P
	n = int2(512, 512);
	n = imagePaint("green", n, res);
	imageStore("img/pintar.png", res, n);

	// R
	n = imageLoad("img/frutos.png", img);
	n = imageRotation90(img, n, res);
	imageStore("img/rotacao_90.png", res, n);

	// O
	n = imageLoad("img/frutos.png", img);
	n = imagePosterize(img, n, 3, res);
	imageStore("img/poster.png", res, n);

	// G
	n = int2(512, 512);
	n = imageDroplet(n, res);
	imageStore("img/goticula.png", res, n);

	// D
	n = imageLoad("img/frutos.png", img);
	n = imageBlur(img, n, 5, res);
	imageStore("img/desfocado.png", res, n);

	// M
	n = imageLoad("img/frutos.png", img);
	n = imageDroplet(n, img2);
	n = imageMask(img, n, img2, n, res);
	imageStore("img/mascarar.png", res, n);

	// F
	n = int2(512, 512);
	n = imageFunctionPlotting(sin, 50, n, res);
	imageStore("img/funcao.png", res, n);

	// T
	n = imageLoad("img/frutos.png", img);
	n = imageOrderedDithering(img, n, res);
	imageStore("img/matizacao.png", res, n);

	// E
	n = imageLoad("img/frutos.png", img);
	n = imageSteganography(img, n, "atacamos ao amanhecer", res);
	imageStore("img/esteganografia.png", res, n);
}

