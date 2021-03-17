#include<stdio.h>

int main()
{
	char char_type = 0;
	char *char_p_type = 0;
	short int s_int_type = 0;
	int int_type = 0;
	long int l_int_type = 0L;
	float float_type = 0;
	double double_type = 0.0;
	long double l_double_type = 0.0;
	size_t sizet_type = 0;

	printf("char pointer type size		 : %lu\n",sizeof(char *));
	printf("char type size		 : %lu\n",sizeof(char_type));
	printf("short int type size	 : %lu\n",sizeof(s_int_type));
	printf("int type size		 : %lu\n",sizeof(int_type));
	printf("long int type size	 : %lu\n",sizeof(l_int_type));	
	printf("float type size		 : %lu\n",sizeof(float_type));
	printf("double type size	 : %lu\n",sizeof(double_type));
	printf("long double type size: %lu\n",sizeof(l_double_type));
	printf("size_t type size	 : %lu\n",sizeof(sizet_type));	

}
