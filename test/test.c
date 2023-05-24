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
