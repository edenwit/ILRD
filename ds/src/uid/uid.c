#include <unistd.h> 	/* pid_t */
#include <time.h> 		/* time_t */
#include <limits.h> 	/* MAX_INT */
#include "uid.h"

#define MAX_SIZE_T (~(size_t)0)

/* Approved by eden girl */
ilrd_uid_t UidCreate(void)
{
	static size_t count = 0;
	ilrd_uid_t uid ={0};	
	
	++count;
		
	uid.count = count;
	uid.process_ID = getpid();
	uid.time_stamp = time(NULL);
	
	if (uid.time_stamp == ((time_t)(-1)))
	{
		return GetBadUid();
	}

	return (uid);
	
}
 
 /* Approved by eden girl */
int UidIsSame(const ilrd_uid_t uid1, const ilrd_uid_t uid2)
{
	if ((uid1.count == uid2.count) && ((uid1.process_ID == uid2.process_ID)) && (0 == difftime(uid1.time_stamp, uid2.time_stamp)))
	{
		return (1);
	}
	
	return (0);
}

/* Approved by eden girl */
ilrd_uid_t GetBadUid(void)
{
	ilrd_uid_t bad_uid ={0, INT_MAX, (time_t)-1};
	
	return bad_uid;	
}
 
