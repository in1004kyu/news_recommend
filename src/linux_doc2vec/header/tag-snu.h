/*
	File Name: tag-snu.h
	Description: Hangul POS tags defined for S.N.U. K-J M.T. system.
		It is only used for token-based output result.
	Written by: Kang, Seung-Shik	04/11/1997
*/
/* N(ü��): NPUM�� ����, N/P/U/M --> 'ü��'�� ���� ���� �±� */
#define HTAG_NOUN	'N'
#define HTAG_PNOUN	'P'
#define HTAG_XNOUN	'U'
#define HTAG_NUMER	'M'

#define HTAG_ASC	'A'

/* V(���): VJ�� ����, V/J --> '���'�� ���� ���� �±� */
#define HTAG_VERB	'V'
#define HTAG_XVERB	'W'
#define HTAG_ADJ	'J'
#define HTAG_XADJ	'K'	/* NOT USED YET */

#define HTAG_ADV	'B'
#define HTAG_DET	'D'
#define HTAG_EXCL	'L'

#define HTAG_JOSA	'j'
#define HTAG_CORP	'c'
#define HTAG_EOMI	'e'
#define HTAG_POMI	'f'

#define HTAG_NSFX	's'
#define HTAG_VSFX	't'

#define HTAG_PUNC	'q'
#define HTAG_SYMB	'Q'
/*------------------- end of tag-snu.h --------------------*/
/*	���� �±׸� �Ʒ��� ���� ��������: 2001.07.27 ���½�
	'x' --> 'W' 
	'C' --> 'q'
*/
