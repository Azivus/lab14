#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "lib.h"


int Check_Write_In_Data(int number_arguments,char *arr_arguments[])
{
	FILE *output_file;
	DIR *input_dir;
	
	if(number_arguments > 1)
	{	
		if(number_arguments != 3)
			printf("Ви ввели хибну кілк. даних");
		else
		{	
			output_file = fopen(*(arr_arguments + 2), "w");
			input_dir = opendir(*(arr_arguments + 1));
		
			if(output_file == NULL || input_dir == NULL )
				printf("Не можливо отримати доступ до файлу або дерикторії");
			else
				return 0;
		}		
	}
	else	
		printf("Ви не ввели данних");
		
	return 1;
}

int* Write_Struct_Dir(char arg_for_file[],char present_dir[],char parents_dir[])
{		
	DIR *input_dir = opendir(present_dir);
	struct dirent *elements;
	int number_elements[] = {0,0};
	int *point_num_elements;
	char element[255];
	
	elements = readdir(input_dir);
	while(elements != NULL)
	{	
		strcat(element, elements->d_name);
		
		if(elements->d_type == 4 && strcmp(elements->d_name, ".") != 0 && strcmp(elements->d_name, "..") != 0)
		{	
			char path[PATH_MAX] = {0};
			int type = elements->d_type;
			
			strcat(path, present_dir);
			strcat(path, "/");
			strcat(path, elements->d_name);
			
			Write_Out_File(element, type, arg_for_file, present_dir, parents_dir);
			
			point_num_elements = Write_Struct_Dir(arg_for_file, path, parents_dir);
			
			*(number_elements) += *(point_num_elements) + 1;
			*(number_elements + 1) += *(point_num_elements + 1);
		}
		if(elements->d_type != 4 && strcmp(elements->d_name, ".") != 0 && strcmp(elements->d_name, "..") != 0)
		{	
			*(number_elements + 1) += 1;
			Write_Out_File(element, 0,arg_for_file, present_dir, parents_dir);
		}	
			
		memset(element, 0, 255);
		elements = readdir(input_dir);
	}
		
	closedir(input_dir);
	
	point_num_elements = number_elements;
	return point_num_elements;
}

int Write_Out_File(char element[],int type,char arg_for_file[],char present_dir[],char parents_dir[])
{	
	int entry_par_path = 0;
	int entry_pre_path = 0;
	int number_tab = 0;
	FILE *output_file = fopen(arg_for_file, "a");
	
	for(int i = 0; parents_dir[i] != '\0';i++)
		if(parents_dir[i] == '/')
			entry_par_path++;	
	
	
	for(int i = 0; present_dir[i] != '\0';i++)
		if(present_dir[i] == '/')
			entry_pre_path++;	
	
	
	if(entry_pre_path >= entry_par_path)
	{
		number_tab = entry_pre_path - entry_par_path;
		
		if(type == 4)
		{	
			for(int i = 0; i < number_tab; i++)
				fprintf(output_file,"|\t");
				
			fprintf(output_file,"|");
			
			if(number_tab == 0)
				number_tab++;
				
			for(int i = 0; i < number_tab + 6; i++)
				fprintf(output_file,"-");
			
			fprintf(output_file,"%s\n", element);	
		}
		else
		{	
			for(int i = 0; i < number_tab; i++)
				fprintf(output_file,"|\t");
				
			fprintf(output_file,"|-%s\n", element);	
		}
	}
	else
		return 1;
		
	fclose(output_file);

	return 0;
}
