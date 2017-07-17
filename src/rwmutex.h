/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 seantian
 *
 * Permission is hereby granted, delete of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **/



/*****************************************************
email: txlstars@gamil.com  

refer https://www.ibm.com/support/knowledgecenter/en/ssw_i5_54/apis/users_80.htm

flag +=	-lpthread
******************************************************/

#ifndef _TSP_RW_MUTEX_H_
#define _TSP_RW_MUTEX_H_

#include <pthread.h>
#include <errno.h>
namespace tsp
{
	
	enum RWMutexRetCode
	{
		RWMutexRetCode_SUCC		= 0,//成功
		RWMutexRetCode_BUSY		= -1,//trylock加锁时锁已被占用
		RWMutexRetCode_EINVAL	= -2,//参数无效或错误
		RWMutexRetCode_EPERM	= -3,//当前线程不持有该锁
		RWMutexRetCode_ERR		= -4,//未知错误	
	};

	class RWMutex
	{
	public:
		RWMutex(){}
		RWMutex(const RWMutex&);//禁止copy
		RWMutex operator=(const RWMutex&);//禁止赋值

		inline RWMutexRetCode initRWLock()
		{
			int ret = pthread_rwlock_init(&m_rwlock, NULL);
			if(ret == 0) return RWMutexRetCode_SUCC;
			else if(ret == EINVAL) return RWMutexRetCode_EINVAL;
			return RWMutexRetCode_ERR;
		}
		inline RWMutexRetCode readLock()
		{
			int ret = pthread_rwlock_rdlock(&m_rwlock);
			if(ret == 0) return RWMutexRetCode_SUCC;
			else if(ret == EINVAL) return RWMutexRetCode_EINVAL;
			return RWMutexRetCode_ERR;
		}
		inline RWMutexRetCode readTryLock()
		{
			int ret = pthread_rwlock_tryrdlock(&m_rwlock);
			if(ret == 0) return RWMutexRetCode_SUCC;
			else if(ret == EINVAL) return RWMutexRetCode_EINVAL;
			else if(ret == EBUSY) return RWMutexRetCode_BUSY;
			return RWMutexRetCode_ERR;
		}
		inline RWMutexRetCode writeLock()
		{
			int ret = pthread_rwlock_wrlock(&m_rwlock);
			if(ret == 0) return RWMutexRetCode_SUCC;
			else if(ret == EINVAL) return RWMutexRetCode_EINVAL;
			return RWMutexRetCode_ERR;
		}
		inline RWMutexRetCode writeTryLock()
		{
			int ret = pthread_rwlock_trywrlock(&m_rwlock);
			if(ret == 0) return RWMutexRetCode_SUCC;
			else if(ret == EINVAL) return RWMutexRetCode_EINVAL;
			else if(ret == EBUSY) return RWMutexRetCode_BUSY;
			return RWMutexRetCode_ERR;
		}
		inline RWMutexRetCode unlock()
		{
			int ret = pthread_rwlock_unlock(&m_rwlock);
			if(ret == 0) return RWMutexRetCode_SUCC;
			else if(ret == EINVAL) return RWMutexRetCode_EINVAL;
			else if(ret == EPERM) return RWMutexRetCode_EPERM;
			return RWMutexRetCode_ERR;
		}
		inline RWMutexRetCode destoryLock()
		{
			int ret = pthread_rwlock_destroy(&m_rwlock);
			if(ret == 0) return RWMutexRetCode_SUCC;
			else if(ret == EINVAL) return RWMutexRetCode_EINVAL;
			return RWMutexRetCode_ERR;
		}
		~RWMutex(){}	

	private:
		pthread_rwlock_t m_rwlock;
	};
}
#endif
