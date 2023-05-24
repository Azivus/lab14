#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "lib.h"


int main(int argc, char* argv[])
{
	char arg_for_file[PATH_MAX] = {0};
	char arg_for_dir[PATH_MAX] = {0};
	int *number_elements;
	int elements[2];
	
	printf("Вивести структуру файлів та каталогів, як це робить утиліта Linux tree.\n\n");
	
	if(Check_Write_In_Data(argc, argv) != 0)
		return 1;
	
	strcat(arg_for_file,*(argv + 2));
	strcat(arg_for_dir,*(argv + 1));
	
	
	FILE *output_file = fopen(arg_for_file, "a");
	fprintf(output_file,"%s\n|\n", arg_for_dir);
	fclose(output_file);
	
	number_elements = Write_Struct_Dir(arg_for_file, arg_for_dir, arg_for_dir);
	
	elements[0] = number_elements[0];
	elements[1] = number_elements[1];
	
	FILE *out_file = fopen(arg_for_file, "a");
	fprintf(output_file,"\nкілк. дирикторій:%d  кілк. файлів:%d", *(elements), *(elements + 1));
	fclose(out_file);
	

	
	
	return 0;
}

















