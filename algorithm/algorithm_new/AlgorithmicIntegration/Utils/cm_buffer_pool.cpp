#include "cm_buffer_pool.h"

namespace cm {

	CBufferItem::CBufferItem(int size)
	{
		if (size > 0) {
			m_size = size;
			m_buffer = new char[size];
		}
		else {
			m_size = 0;
			m_buffer = NULL;
		}
	}

	CBufferItem::~CBufferItem()
	{
		if (m_buffer != NULL) {
			delete[] m_buffer;
			m_buffer = NULL;
		}
	}

	char* CBufferPool::GetBuffer(int size)
	{
		CAutoLock autoLock(lock_);

		CBufferItem *item = NULL;

		auto iter = queue_accessible_objects_.begin();
		for (; iter != queue_accessible_objects_.end(); iter++) {
			if ((*iter)->m_size >= size) {
				item = *iter;

				queue_accessible_objects_.erase(iter);
				queue_using_objects_.push_back(item);
				return item->m_buffer;
			}
		}

		item = new CBufferItem(size);
		queue_using_objects_.push_back(item);
		return item->m_buffer;
	}


	void CBufferPool::ReleaseBuffer(char *buffer)
	{
		CAutoLock autoLock(lock_);

		auto iter = queue_using_objects_.begin();
		for (; iter != queue_using_objects_.end(); iter++) {
			if ((*iter)->m_buffer == buffer) {
				CBufferItem *item = *iter;

				queue_accessible_objects_.push_back(item);
				queue_using_objects_.erase(iter);
				return;
			}
		}

		assert(false);

		return;
	}
}