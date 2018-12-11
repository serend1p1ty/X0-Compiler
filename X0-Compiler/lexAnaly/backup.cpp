#include "../global.h"

/* 
 * backup the status of lexical analysing 
 */
void backup ()
{
	backups[backUpNum].backupFin = fin;
	backups[backUpNum].backupSym = sym;
	backups[backUpNum].backupCh = ch;
	backups[backUpNum].backupPosCh = posCh;
	backups[backUpNum].backupChNum = chNum;
	backups[backUpNum].backupDoubleNum = doubleNum;
	backups[backUpNum].backupIntNum = intNum;
	backups[backUpNum].backupIterCode = codeNum;
	strcpy (backups[backUpNum].backupId, id);

	for (int i = 0; i < MAX_NUM_LINE; i++)
	{
		backups[backUpNum].backupLineCache[i] = lineCache[i];
	}
	
	backUpNum++;
}