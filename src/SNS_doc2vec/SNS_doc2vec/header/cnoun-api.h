#include "cnoun.h"

extern PREFIX HAM_SHORT genNounCompKSC(
	HAM_PUCHAR word,	/* c-noun: KSC5601 code */
	HAM_PUCHAR nlist,	/* list of unit nouns */
	HAM_PSHORT n2,	/* 2nd �ĺ����� index */
	HAM_UCHAR noun_delimiter,	/* noun-split mark like '_' or '\0' */
	HAM_PSHORT cnndic);	/* ham-cnn.dic�� �ְų�(1), �˰������� ����(0) */

extern PREFIX int genNounCompKSC_alnum(
	HAM_PUCHAR word,	/* c-noun: KSC5601 Hangul string */
	HAM_PUCHAR nlist,	/* list of unit nouns */
	char noun_delimiter,	/* noun-split mark like '_' or '\0' */
	int *cnndic,	/* ham-cnn.dic�� �ְų�(1), �˰������� ����(0) */
	int *puncflag);	/* �����ȣ �и��Ǿ�����(1), �ƴ���(0) */

extern PREFIX int cnoun_decomposition(char *word, HAM_CNOUN cnn[]);
