#include <unistd.h> 	/* pid_t */
#include <time.h> 		/* time_t */

/*
typedef struct unique_id
{
	size_t count;
	pid_t process_ID:
	time_t time_stamp;
} ilrd_uid_t;
*/

ilrd_uid_t UidCreate(void)
{
	
	ilrd_uid_t uid ={0};
	
	uid.process_ID = getpid();
	
}
 
int UidIsSame(const ilrd_uid_t uid1, const ilrd_uid_t uid2)
{

}

ilrd_uid_t GetBadUid(void)
{

}
 
