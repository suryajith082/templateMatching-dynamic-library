#pragma once
#ifdef templateMatching_EXPORTS  
#define templateMatchingApi __declspec(dllexport)   
#else  
#define templateMatchingApi __declspec(dllimport)   
#endif  
extern "C" templateMatchingApi int res( char* a, char* b);