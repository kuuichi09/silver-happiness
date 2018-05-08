#include <stdio.h>

int nuc_num(int x){
	int y = 0;
	switch (x){
		case 'a':
		case 'A':
			y = 1;
			break;
		case 't':
		case 'T':
			y = 4;
			break;
		case 'g':
		case 'G':
			y = 2;
			break;
		case 'c':
		case 'C':
			y = 3;
			break;
		default:
			break;
	}
	return(y);
} 

int main(void){

	FILE *fp;
	char *fname = "query.txt";
	FILE *fpr;
	char *fnamer = "result.fasta";

	int nuc1 = 0;
	int nuc2 = 0;
	int nuc3 = 0;
	int NUC1 = 0;
	int NUC2 = 0;
	int NUC3 = 0;
	int NUCSUM = 0;

	char buf_nucpos[32];

	fpos_t filepos = 0;
	int terminal_FLAG = 0;

	fp = fopen(fname, "r");
	if(fp == NULL){
		printf("No query. Rename to \"query.txt\".\n");
		return 0;
	}else{
		printf("Success of opening the query file.\n");
	}

	fpr = fopen(fnamer, "w");
	if(fpr == NULL){
		printf("Cannot make the result file.\n");
		return 0;
	}else{
		printf("Success of makeing the results file.\n");
	}

	printf("Now processing. Please wait.\n");
	fgetpos(fp, &filepos);
	while((nuc1 = fgetc(fp)) != EOF ){
		fgetpos(fp, &filepos);
		if((nuc2 = fgetc(fp)) == EOF){
			break;
		}
		if((nuc3 = fgetc(fp)) == EOF){
			break;
		}

		NUC1 = nuc_num(nuc1);
		NUC2 = nuc_num(nuc2);
		NUC3 = nuc_num(nuc3); 

		if((NUC1 == 1)&&(NUC2 == 4)&&(NUC3 == 2)){
			fputc('>',fpr);
			sprintf(buf_nucpos, "%d\nM",filepos);
			fputs(buf_nucpos, fpr);
			printf("Find ORF Pos at %d.\n", filepos);

			while((nuc1 = fgetc(fp)) != EOF){
				if((nuc2 = fgetc(fp)) == EOF){
					terminal_FLAG = 1;
					break;
				}
				if((nuc3 = fgetc(fp)) == EOF){
					terminal_FLAG = 1;
					break;
				}

				NUC1 = nuc_num(nuc1);
				NUC2 = nuc_num(nuc2);
				NUC3 = nuc_num(nuc3);
				NUCSUM = NUC1 * 100 + NUC2 * 10 + NUC3;
				switch(NUCSUM){
					case 111:	/*AAA*/
					case 112:	/*AAG*/
						fputc('K', fpr);
						break;
					case 113:	/*AAC*/
					case 114:	/*AAT*/
						fputc('N', fpr);
						break;
					case 121:	/*AGA*/
					case 122:	/*AGG*/
						fputc('R', fpr);
						break;
					case 123:	/*AGC*/
					case 124:	/*AGC*/
						fputc('S', fpr);
						break;
					case 131:	/*ACA*/
					case 132:	/*ACG*/
					case 133:	/*ACC*/
					case 134:	/*ACT*/
						fputc('T', fpr);
						break;
					case 141:	/*ATA*/
					case 143:	/*ATC*/
					case 144:	/*ATT*/
						fputc('I',fpr);
						break;
					case 142:	/*ATG*/
						fputc('M',fpr);
						break;
					case 211:	/*GAA*/
					case 212:	/*GAG*/
						fputc('E',fpr);
						break;
					case 213:	/*GAC*/
					case 214:	/*GAT*/
						fputc('D',fpr);
						break;
					case 221:	/*GGA*/
					case 222:	/*GGG*/
					case 223:	/*GGC*/
					case 224:	/*GGT*/
						fputc('G',fpr);
						break;
					case 231: 	/*GCA*/
					case 232:	/*GCG*/
					case 233:	/*GCC*/
					case 234:	/*GCT*/
						fputc('A',fpr);
						break;
					case 241:	/*GTA*/
					case 242:	/*GTG*/
					case 243:	/*GTC*/
					case 244:	/*GTT*/
						fputc('V',fpr);
						break;
					case 311:	/*CAA*/
					case 312:	/*CAG*/
						fputc('Q',fpr);
						break;
					case 313:	/*CAC*/
					case 314:	/*CAT*/
						fputc('H',fpr);
						break;
					case 321:	/*CGA*/
					case 322:	/*CGG*/
					case 323:	/*CGC*/
					case 324:	/*CGT*/
						fputc('R',fpr);
						break;
					case 331:	/*CCA*/
					case 332:	/*CCG*/
					case 333:	/*CCC*/
					case 334:	/*CCT*/
						fputc('P',fpr);
						break;
					case 341:	/*CTA*/
					case 342:	/*CTG*/
					case 343:	/*CTC*/
					case 344:	/*CTT*/
						fputc('L',fpr);
						break;
					case 411:	/*TAA*/
					case 412:	/*TAG*/
						terminal_FLAG = 1;
						break;
					case 413:	/*TAC*/
					case 414:	/*TAT*/
						fputc('Y',fpr);
						break;
					case 421:	/*TGA*/
						terminal_FLAG = 1;
						break;
					case 422:	/*TGG*/
						fputc('W',fpr);
						break;
					case 423:	/*TGC*/
					case 424:	/*TGT*/
						fputc('C',fpr);
						break;
					case 431:	/*TCA*/
					case 432:	/*TCG*/
					case 433:	/*TCC*/
					case 434:	/*TCT*/
						fputc('S',fpr);
						break;
					case 441:	/*TTA*/
					case 442:	/*TTG*/
						fputc('L',fpr);
						break;
					case 443:	/*TTC*/
					case 444:	/*TTT*/
						fputc('F',fpr);
						break;
					default:
						fputc('X', fpr);
						break;
				}
			
				if (terminal_FLAG == 1){
					break;
				}

			}
			if((terminal_FLAG == 1)||(nuc1 == EOF)){
				sprintf(buf_nucpos, "\n\n");
				fputs(buf_nucpos, fpr);
			}
			terminal_FLAG = 0;
		}

		nuc1 = 0;
		nuc2 = 0;
		nuc3 = 0;
		NUC1 = 0;
		NUC2 = 0;
		NUC3 = 0;
		NUCSUM = 0;
		fsetpos(fp, &filepos);
	}

	printf("Processing was succeeded. Closing files.\n");
	fclose(fp);
	fclose(fpr);
	printf("Complete!\n");
	return 0;
}




