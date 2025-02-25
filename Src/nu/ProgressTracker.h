						#include <map>
						#include "AutoLock.h"
						#include <bfc/platform/types.h>
						
						class ProgressTracker
						{
						public:
					static const uint64_t null_position;
					ProgressTracker()
					{
				current_position=0;
				current_chunk=0;
				chunks[0]=0;
				chunks[null_position]=null_position;
					};
						
					void Write(uint64_t bytes_written)
					{
				Nullsoft::Utility::AutoLock list_lock(list_guard);
				ChunkList::iterator next, itr = chunks.find(current_chunk);
				current_position += bytes_written;
				if (itr->second < current_position)
			itr->second = current_position;
						
				for (;;)
				{
			next = itr;
			++next;
			if (next != chunks.end() && (next->first <= itr->second))
			{
		itr->second = next->second;
		chunks.erase(next);
			}
			else
		break;
				}
					}
						
					bool Valid(uint64_t requested_position, uint64_t requested_end)
					{
				Nullsoft::Utility::AutoLock list_lock(list_guard);
				for (ChunkList::iterator itr=chunks.begin();itr!=chunks.end();itr++)
				{
			if (requested_position >= itr->first)
			{
		if (requested_position < itr->second)
		{
	if (requested_end <= itr->second)
	{
return true;
	}
	else
	{
return false;
	}
		}
			}
				}
				return false;
					}
						
					bool Seek(uint64_t requested_position, uint64_t requested_end, uint64_t *new_start, uint64_t *new_end)
					{
				Nullsoft::Utility::AutoLock list_lock(list_guard);
				uint64_t last_good_start=0;
				ChunkList::iterator itr;
				for (itr=chunks.begin();itr!=chunks.end();itr++)
				{
			if (requested_position >= itr->first)
			{
		current_chunk = itr->first;
		if (requested_position <= itr->second)
		{
	ChunkList::iterator next = itr;
	++next;
	*new_end = next->first;
						
	*new_start = current_position = itr->second;
						
	if (requested_end <= itr->second)
	{
return true;
	}
	else
	{
return false;
	}
		}
		else
		{
	last_good_start = itr->second;
		}
			}
				}
				if (last_good_start > requested_position)
			*new_start = current_position = last_good_start;
				else
				{
			
			*new_start = current_chunk = current_position = requested_position;
			chunks[current_chunk] = current_chunk;
				}
				*new_end = null_position;
				return false;
					}
						
						#if 0
					void Dump()
					{
		ChunkList::iterator itr;
				for (itr=chunks.begin();itr!=chunks.end();itr++)
				{
			printf("%I64u - %I64u\n", itr->first, itr->second);
				}
						
					}
					#endif
						
					typedef std::map<uint64_t, uint64_t> ChunkList;
					ChunkList chunks;
					uint64_t current_chunk;
					uint64_t current_position;
					Nullsoft::Utility::LockGuard list_guard;
						};
						const uint64_t ProgressTracker::null_position = (uint64_t)-1;