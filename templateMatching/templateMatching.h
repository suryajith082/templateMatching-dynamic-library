#pragma once
#ifdef templateMatching_EXPORTS  
#define templateMatchingApi __declspec(dllexport)   
#else  
#define templateMatchingApi __declspec(dllimport)   
#endif  
extern "C" templateMatchingApi void res( char* a, char* b, int* x, int* y);