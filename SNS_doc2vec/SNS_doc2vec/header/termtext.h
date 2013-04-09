/*=====================================================================
	�� ���� �� ���� ��ü�� ���� ���ξ� ����
		- unify�� ���� TF ���
=====================================================================*/
/* ���ĸ��(�λ缺 ���)�� �ִ��: modinoun.dic */
#define MAX_MODINOUN	1000

/* �оߺ� ���� �ִ� ��� ��: domain.dic */
#define MAX_DOMAINNOUN	50000

/* ���� or �������� ���ξ� ���⿡ �ʿ��� �ִ� ���� */
#define MAX_TERMS_SENT		 100	/* �� ���忡�� ����Ǵ� �ִ� ��� ���� */
#define MAX_TERM_BYTES_SENT	2000	/* term string ���忡 �ʿ��� �ִ� ����Ʈ �� */

#define MAX_TERMS_DOC		 2000	/* �� ���� ���Ͽ��� ����Ǵ� �ִ� ��� ���� */
#define MAX_TERM_BYTES_DOC	1000000	/* term string ���忡 �ʿ��� �ִ� ����Ʈ �� */

#define MAX_LOCS_PER_TERM	20/*1024*/	/* ������ term�� ���� ��ġ �ִ� ���� */

/* �� ���� or ������ ���� term extraction ��� ���� ���� */
typedef struct TermList {
	long offset;				/* term string ���� ��ġ */
	unsigned char pos;			/* term type */
	unsigned char tf;			/* term frequency: max. 255 */
	unsigned short score;		/* term weight */
	unsigned short loc[MAX_LOCS_PER_TERM];	/* term ���� ��ġ �ִ� ���� */
} HAM_TERMLIST, *HAM_PTERMLIST;

/* �� ������ ���� term extraction�� �ʿ��� memory */
typedef struct TermMemory {
	long memTermIndex;	/* 'memTermString[]'�� free �κ� index */
	unsigned char memTermString[MAX_TERM_BYTES_DOC];	/* ���� ��� ������� */

	/* �� ���徿 �м��ϴµ� �ʿ��� memory */
	unsigned char *terms[MAX_TERMS_SENT];			/* ���忡�� ����� ��� ���� */
	unsigned char termMem[MAX_TERM_BYTES_SENT];		/* �� ���� ��� ������� */
	HAM_MORES hamOut;		/* �� ���忡 ���� ���¼� �м� ��� ������� */
} HAM_TERMMEMORY, *HAM_PTERMMEMORY;
