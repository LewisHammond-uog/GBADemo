#pragma once

#pragma once

#include <assert.h>

#define CREATEPOOL 0xcdcdcdcdcd
#define FREEPOLL 0x000000000

template <class T, int MAX_SIZE>
class CStaticPool
{
protected:

	struct FreeObject
	{
		FreeObject* p_Next;
	};

	unsigned int m_uiAllocated; //Number of un allocated items
	T m_pool[MAX_SIZE]; //Actuall Object Pool
	FreeObject m_pFreeList; //List of free items

public:

	/// Default Constructor/Destructor
	CStaticPool();
	~CStaticPool();

	//Public Functions
	T* Allocate();
	void Free(T* pObject);
	void Release();
	unsigned int GetNumUsedElements() const;
	unsigned int GetNumFreeElements() const;
	unsigned int GetSizeOfPoolElement() const;
};

template<class T, int MAX_SIZE>
inline CStaticPool<T, MAX_SIZE>::CStaticPool()
{

	m_uiAllocated = 0;
	m_pFreeList = (FreeObject*)(&m_pool);

	FreeObject* tempFree = m_pFreeList;
	memset(&m_pool[0], CREATEPOOL, sizeof(T) * MAX_SIZE);
	for (int i = 1; i < MAX_SIZE; ++i) {
		tempFree->p_Next = (FreeObject*)(&m_pFreeList);
		tempFree = tempFree->p_Next;
	}
}

template<class T, int MAX_SIZE>
inline CStaticPool<T, MAX_SIZE>::~CStaticPool()
{
	//Do Nothing
}


//Allocate Memory to the pool
template<class T, int MAX_SIZE>
inline T* CStaticPool<T, MAX_SIZE>::Allocate()
{
	assert(m_pool);

	if (m_pFreeList) {
		FreeObject* pFreeObject = m_pFreeList; //Get current free obj
		m_pFreeList = m_pFreeList->pNext; //Move free list to next obj
		++m_uiAllocated;
		memset(pFreeObject, ZEROPOOL, sizeof(T)); // Zero the data
		return reinterpret_cast<T*>(pFreeObject); //Return the pool Object
	}

	return NULL; //We've run out of free object
}

///Free Object from Pool
template<class T, int MAX_SIZE>
inline void CStaticPool<T, MAX_SIZE>::Free(T* pObject)
{

	FreeObject* pFreeObject = reinterpret_cast<FreeObject*>(pObject);

	unsigned int uFirstAddress = reinterpret_cast<unsigned int>(&m_pool[0]);
	unsigned int uObjectAddress = reinterpret_cast<unsigned int>(pObject);
	unsigned int uSize = sizeof(T);

	//Test to see if the obj address is valid
	if (!((uObjectAddress - uFirstAddress) % uSize) && pFreeObject < reinterpret_cast<FreeObject*>(&m_pool[MAX_SIZE])) {
		pFreeObject->pNext = m_pFreeList;
		m_pFreeList = pFreeObject;
		--m_uiAllocated;
	}
	else {
		//We are outside the scope of this memory block
	}
}

template<class T, int MAX_SIZE>
inline void CStaticPool<T, MAX_SIZE>::Release()
{
	CStaticPool();
}


template<class T, int MAX_SIZE>
inline unsigned int CStaticPool<T, MAX_SIZE>::GetNumFreeElements() const
{
	return (MAX_SIZE - m_uiAllocated);
}

template<class T, int MAX_SIZE>
inline unsigned int CStaticPool<T, MAX_SIZE>::GetSizeOfPoolElement() const
{
	return sizeof(T);
}

template<class T, int MAX_SIZE>
inline unsigned int CStaticPool<T, MAX_SIZE>::GetNumUsedElements() const
{
	return (m_uiAllocated);
}




