#include "../global.h"

/* 
 * recover the status of lexical analysing from backups 
 */
void recover ()
{
	iterBackUp--;
	fin = backups[iterBackUp].backupFin;
	sym = backups[iterBackUp].backupSym;
	ch = backups[iterBackUp].backupCh;
	posCh = backups[iterBackUp].backupPosCh;
	chNum = backups[iterBackUp].backupChNum;
	doubleNum = backups[iterBackUp].backupDoubleNum;
	intNum = backups[iterBackUp].backupIntNum;
	iterCode = backups[iterBackUp].backupIterCode;
	strcpy (id, backups[iterBackUp].backupId);

	for (int i = 0; i < MAX_SIZE_LINE; i++)
	{
		lineCache[i] = backups[iterBackUp].backupLineCache[i];
	}
}