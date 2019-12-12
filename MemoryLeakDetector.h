#pragma once

#if defined(_DEBUG)
#include <crtdbg.h>
#endif

#if defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#if defined(_DEBUG)
inline void SetUpMemoryLeakDetector()
{
	// メモリーリーク検出のための設定
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
}
#endif