#include "../global.h"

/* 
 * recover the status of lexical analysing from backups 
 */
void recover ()
{
	backUpNum--;
	fin = backups[backUpNum].backupFin;
	sym = backups[backUpNum].backupSym;
	ch = backups[backUpNum].backupCh;
	posCh = backups[backUpNum].backupPosCh;
	chNum = backups[backUpNum].backupChNum;
	doubleNum = backups[backUpNum].backupDoubleNum;
	intNum = backups[backUpNum].backupIntNum;
	codeNum = backups[backUpNum].backupIterCode;
	strcpy (id, backups[backUpNum].backupId);

	for (int i = 0; i < MAX_NUM_LINE; i++)
	{
		lineCache[i] = backups[backUpNum].backupLineCache[i];
	}
}