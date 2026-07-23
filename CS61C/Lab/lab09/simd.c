#include <time.h>
#include <stdio.h>
#include <x86intrin.h>
#include "simd.h"

long long int sum(int vals[NUM_ELEMS]) {
	clock_t start = clock();

	long long int sum = 0;
	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		for(unsigned int i = 0; i < NUM_ELEMS; i++) {
			if(vals[i] >= 128) {
				sum += vals[i];
			}
		}
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return sum;
}

long long int sum_unrolled(int vals[NUM_ELEMS]) {
	clock_t start = clock();
	long long int sum = 0;

	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		for(unsigned int i = 0; i < NUM_ELEMS / 4 * 4; i += 4) {
			if(vals[i] >= 128) sum += vals[i];
			if(vals[i + 1] >= 128) sum += vals[i + 1];
			if(vals[i + 2] >= 128) sum += vals[i + 2];
			if(vals[i + 3] >= 128) sum += vals[i + 3];
		}

		//This is what we call the TAIL CASE
		//For when NUM_ELEMS isn't a multiple of 4
		//NONTRIVIAL FACT: NUM_ELEMS / 4 * 4 is the largest multiple of 4 less than NUM_ELEMS
		for(unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++) {
			if (vals[i] >= 128) {
				sum += vals[i];
			}
		}
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return sum;
}

long long int sum_simd(int vals[NUM_ELEMS]) {
	clock_t start = clock();
	__m128i _127 = _mm_set1_epi32(127);		// This is a vector with 127s in it... Why might you need this?
	long long int result = 0;				   // This is where you should put your final result!
	/* DO NOT DO NOT DO NOT DO NOT WRITE ANYTHING ABOVE THIS LINE. */
	
	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		/* YOUR CODE GOES HERE */
		for (unsigned int i = 0; i < NUM_ELEMS / 4 * 4; i += 4) {
			__m128i vec = _mm_load_si128((__m128i *) &vals[i]);
			__m128i mask = _mm_cmpgt_epi32(vec, _127);
			__m128i sum = _mm_and_si128(vec, mask);
			result += _mm_extract_epi32(sum, 0) + _mm_extract_epi32(sum, 1) + _mm_extract_epi32(sum, 2) + _mm_extract_epi32(sum, 3);
		}
		/* You'll need a tail case. */
		for (unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++) {
			if (vals[i] >= 128) {
				result += vals[i];
			}
		}

	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return result;
}

long long int sum_simd_unrolled(int vals[NUM_ELEMS]) {
	clock_t start = clock();
	__m128i _127 = _mm_set1_epi32(127);
	long long int result = 0;
	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		/* COPY AND PASTE YOUR sum_simd() HERE */
		/* MODIFY IT BY UNROLLING IT */
		for (unsigned int i = 0; i < NUM_ELEMS / 16 * 16; i += 16) {
			__m128i vec1 = _mm_load_si128((__m128i *) &vals[i]);
			__m128i vec2 = _mm_load_si128((__m128i *) &vals[i + 4]);
			__m128i vec3 = _mm_load_si128((__m128i *) &vals[i + 8]);
			__m128i vec4 = _mm_load_si128((__m128i *) &vals[i + 12]);
			__m128i mask1 = _mm_cmpgt_epi32(vec1, _127);
			__m128i mask2 = _mm_cmpgt_epi32(vec2, _127);
			__m128i mask3 = _mm_cmpgt_epi32(vec3, _127);
			__m128i mask4 = _mm_cmpgt_epi32(vec4, _127);
			__m128i sum1 = _mm_and_si128(vec1, mask1);
			__m128i sum2 = _mm_and_si128(vec2, mask2);
			__m128i sum3 = _mm_and_si128(vec3, mask3);
			__m128i sum4 = _mm_and_si128(vec4, mask4);
			sum1 = _mm_add_epi32(sum1, sum2);
			sum3 = _mm_add_epi32(sum3, sum4);
			sum1 = _mm_add_epi32(sum1, sum3);
			result += _mm_extract_epi32(sum1, 0) + _mm_extract_epi32(sum1, 1) + _mm_extract_epi32(sum1, 2) + _mm_extract_epi32(sum1, 3);
		}

		/* You'll need 1 or maybe 2 tail cases here. */
		for (unsigned int i = NUM_ELEMS / 16 * 16; i < NUM_ELEMS; i++) {
			if (vals[i] >= 128) {
				result += vals[i];
			}
		}

	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return result;
}