# **Лабораторна робота 14**

# **Панкеєв Владислав Олексійович 922-Б**

## **Основна частина:**

### **Вміст файлу main.c**

```c
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

```
### **Вміст файлу lib.c**
```c
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
```
### **Вміст файлу lib.h**
```c
int Check_Write_In_Data(int number_arguments, char *arr_arguments[]);

int* Write_Struct_Dir(char arg_for_file[],char present_dir[],char parents_dir[]);

int Write_Out_File(char element[],int type, char arg_for_file[],char present_dir[],char parents_dir[]);
```
### **Вміст файлу test.c**
```c
#include "../src/lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <math.h>

START_TEST(test_Check_Write_In_Data_NoArguments)
{	
	int number_arguments = 0;
	char* arr_arguments[1];
	int expected_result = 1;
	int actual_result;
	
	actual_result = Check_Write_In_Data(number_arguments,arr_arguments);
	
	ck_assert_int_eq(expected_result,actual_result);
}
END_TEST

START_TEST(test_Check_Write_In_Data_NoCorentEnghtArg)
{	
	int number_arguments = 2;
	char *arr_arguments[1];
	int expected_result = 1;
	int actual_result;
	
	actual_result = Check_Write_In_Data(number_arguments,arr_arguments);
	
	ck_assert_int_eq(expected_result,actual_result);
	
	number_arguments = 4;
	
	actual_result = Check_Write_In_Data(number_arguments,arr_arguments);
	
	ck_assert_int_eq(expected_result,actual_result);
}
END_TEST

START_TEST(test_Check_Write_In_Data_NoActualArg)
{	
	int number_arguments = 3;
	char *arr_arguments[100];
	
	*(arr_arguments) = "0";
	*(arr_arguments + 1) = "/home/home/home/home";
	*(arr_arguments + 2) = "dist/text.txt";
	
	int expected_result = 1;
	int actual_result;
	
	actual_result = Check_Write_In_Data(number_arguments,arr_arguments);
	
	ck_assert_int_eq(expected_result,actual_result);
	
	*(arr_arguments + 1) = "/home/vlad/Documents/1cours";
	*(arr_arguments + 2) = "dir1/dir2/text.txt";
	
	actual_result = Check_Write_In_Data(number_arguments,arr_arguments);
	
	ck_assert_int_eq(expected_result,actual_result);
}
END_TEST

START_TEST(test_Check_Write_In_Data_TrueData)
{	
	int number_arguments = 3;
	char *arr_arguments[100];
	
	*(arr_arguments) = "0";
	*(arr_arguments + 1) = "/home/vlad/Documents/1cours";
	*(arr_arguments + 2) = "dist/text.txt";
	
	int expected_result = 0;
	int actual_result;
	
	actual_result = Check_Write_In_Data(number_arguments,arr_arguments);
	
	ck_assert_int_eq(expected_result,actual_result);
	
}
END_TEST

START_TEST(test_Write_Struct_Dir_DirFiles)
{	
	char file[] = "dist/test_DirFiles.txt";
	char path_to_dir[] = "test/test(DirFiles)";
	int expected_number_elements = 5;
	int actual_number_elements;
	
	actual_number_elements = Write_Struct_Dir(file,path_to_dir);
	
	ck_assert_int_eq(expected_number_elements,actual_number_elements);
}
END_TEST

START_TEST(test_Write_Struct_Dir_DirInDir)
{	
	char file[] = "dist/test_DirInDir.txt";
	char path_to_dir[] = "test/test(DirInDir)";
	int expected_number_elements = 30;
	int actual_number_elements;
	
	actual_number_elements = Write_Struct_Dir(file,path_to_dir);
	
	ck_assert_int_eq(expected_number_elements,actual_number_elements);
}
END_TEST

Suite *lab_test_suite(void)
{
	Suite *s;
	TCase *Check_Write_In_Data;
	TCase *Write_Struct_Dir;

	s = suite_create("lab14");

	Check_Write_In_Data = tcase_create("Check_Write_In_Data");
	Write_Struct_Dir = tcase_create("Write_Struct_Dir");
	
	tcase_add_test(Check_Write_In_Data, test_Check_Write_In_Data_NoArguments);
	tcase_add_test(Check_Write_In_Data, test_Check_Write_In_Data_NoCorentEnghtArg);
	tcase_add_test(Check_Write_In_Data, test_Check_Write_In_Data_NoActualArg);
	tcase_add_test(Check_Write_In_Data, test_Check_Write_In_Data_TrueData);
	
	suite_add_tcase(s, Check_Write_In_Data);
	
	tcase_add_test(Write_Struct_Dir, test_Write_Struct_Dir_DirFiles);
	tcase_add_test(Write_Struct_Dir, test_Write_Struct_Dir_DirInDir);
	
	suite_add_tcase(s, Write_Struct_Dir);
	
	return s;
}

int main(void)
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = lab_test_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
```
### **Структура проекту лабораторної роботи:**
```   
lab14
├── Doxyfile
├── Makefile
├── README.md
├── test
│   └── test.c
└── src
    ├── lib.c
    ├── lib.h
    └──	main.c
```
### **Скріншоти**
![Program](https://github.com/Azivus/lab14/blob/main/Снимок%20экрана%20(3904).png)
![Program](https://github.com/Azivus/lab14/blob/main/Снимок%20экрана%20(3908).png)
