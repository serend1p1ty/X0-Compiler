#include "../global.h"

/* 
 * backup the status of lexical analysing 
 */
void backup ()
{
	backups[iterBackUp].backupFin = fin;
	backups[iterBackUp].backupSym = sym;
	backups[iterBackUp].backupCh = ch;
	backups[iterBackUp].backupPosCh = posCh;
	backups[iterBackUp].backupChNum = chNum;
	backups[iterBackUp].backupDoubleNum = doubleNum;
	backups[iterBackUp].backupIntNum = intNum;
	backups[iterBackUp].backupIterCode = iterCode;
	strcpy (backups[iterBackUp].backupId, id);

	for (int i = 0; i < MAX_SIZE_LINE; i++)
	{
		backups[iterBackUp].backupLineCache[i] = lineCache[i];
	}
	
	iterBackUp++;
}