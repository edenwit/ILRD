#include <stddef.h> /* size_t */
#include <stdio.h>
#include <string.h>
#include "vector.h" 

static void TestVector();

int main ()
{
	TestVector();	
	return 0;			
}

static void TestVector()
{
	size_t i;
    size_t capacity = 10;
	
	float floati_float = 0.1;
	int inti_int = 0;
	
	vector_t* vec_test;
    vec_test = VectorCreate(capacity);
	
	printf("\nVector capacity: %ld, size: %ld\n",VectorCapacity(vec_test), VectorSize(vec_test));
	for (i = 0; i < capacity; ++i)
	{
		++floati_float;
		++inti_int;
		
		VectorPushBack(vec_test, &floati_float);	
		VectorPushBack(vec_test, &inti_int);	
		VectorPushBack(vec_test, "me three!");	
		VectorPushBack(vec_test, "103546532"); 	
		VectorPushBack(vec_test, "lol");
    }
	printf("Vector capacity: %ld, size: %ld\n",VectorCapacity(vec_test), VectorSize(vec_test));
	
	for (i = 0; i < capacity; ++i)    
	{
		VectorPopBack(vec_test); 	
	}	
	
	printf("\nVector capacity: %ld, size: %ld\n",VectorCapacity(vec_test), VectorSize(vec_test));
	VectorShrinkToFit(vec_test);
	printf("\nAfter Shrinking to fit Capacity is: %ld\n",VectorCapacity(vec_test));
	VectorReserve(vec_test, 10);
	printf("\nReserving with size of 10: Capacity: %ld\n",VectorCapacity(vec_test));
	VectorSetElem(vec_test, 5, "The very very endy end");
	printf("After SetElem 6 has: %s\n",(char*)VectorGetElem(vec_test,5));
		
	VectorDestroy(vec_test);
	
	return;
}
