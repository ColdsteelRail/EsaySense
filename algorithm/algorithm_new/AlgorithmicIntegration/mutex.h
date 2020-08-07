
#ifndef _MUTEX_H_
#define _MUTEX_H_
#include<mutex>
typedef std::recursive_mutex MutexObject;
#define AUTOLOCK(a)  std::lock_guard<MutexObject> lock(a);
#define AUTOLOCK_BEGIN(a) { std::lock_guard<MutexObject> lock(a);
#define AUTOLOCK_END }





#endif
