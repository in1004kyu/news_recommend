/*
	File Name: cnoun.h
	Description: output structure for compound noun decomposition.
	Written by: Kang, Seung-Shik		04/11/1997
*/

/*                                                         */
/*     C-noun decomposition result structure               */
/*                                                         */
#define MAXCAND	50	/* ���ո�� ���� �ĺ��� �����ϴ� �ִ� ���� */
#define MAXCOMP	16	/* ���ո�縦 �����ϴ� ���������� �ִ� ���� */

typedef struct ncomp {
    HAM_UCHAR ncmp; /* number of noun components in c-noun */
    HAM_UCHAR flag; /* 8-bit 0/1 for (un)registered compo. */
    HAM_UCHAR nsyl[MAXCOMP];/* num. of syllables for each compo.*/
    HAM_SHORT score;
} HAM_CNOUNSTR, *HAM_PCNOUNSTR;

/*---------------------------------------------------------*/
#define MAXnnn	15	/* see MAXCOMP --> ���ո�縦 �����ϴ� ���������� �ִ� ���� */

typedef struct hamcnoun {
    char nnn[MAXnnn+1];		/* ���ո�� ��� ���� (ex; 644) -- ����Ʈ ���� */
    char dic[MAXnnn+1];		/* ���� ����� ���� ���� -- S/s/U/D/P/k (�켱���� �������)
					S: �ҿ�� ������ ��ϵ� �ҿ��
					s: �ҿ�� ������ ��ϵ� Ư�����ξ�
					U: ����� ������ ��ϵ� ���� ���
					D: ��м� �������� ���ص� ���ո���� ���� ���
					P: ������ ��ϵ� ���� ���
					K: ������ ���ϵ��� ���� �̵�Ͼ� */
	int score;	/* best �м���� ������ �� ���Ǵ� ���� */
} HAM_CNOUN, *HAM_PCNOUN;
/*-------------------- end of cnoun.h ---------------------*/
