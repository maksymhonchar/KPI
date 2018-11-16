#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#include "stack.h"

void DLL_EXPORT addItem(stack_t * a);
void DLL_EXPORT reaction(stack_t * a);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
