/*
	File Name: ham-api.h
	Description: HAM API functions
	Written by: Kang, Seung-Shik	11/06/2002
	Modified at 03/24/2003
*/
/*-------------------------------------------------------------
	Compile option : ���̺귯�� �Լ��� ������Ÿ�� ����
	(Linux/UNIX������ �Ʒ� #define WINDOWS�� �����ϼ���)
-------------------------------------------------------------*/
#define UNIX_CPP

#ifdef WINDOWS_DLL			/* DLL export */
#define PREFIX	_declspec(dllimport)
#elif defined(WINDOWS_DLL_CPP)	/* ���� VC++�� C++ �������̽� */
#define PREFIX	"C" _declspec(dllimport)
#elif defined(UNIX_CPP)	/* ���� VC++�� C++ �������̽� */
#define PREFIX	"C"
#else						/* Linux/Unix �� ���н� �迭 */
#define PREFIX
#endif

extern PREFIX int open_HAM_index(
	HAM_RUNMODE *mode,	/* running mode of HAM */
	char *options,	/* option string */
	char *inifile);	/* file name: 'ham2000.ini' */
extern PREFIX int open_HAM_index_dicpath(
	HAM_RUNMODE *mode,	/* running mode of HAM */
	char *options,	/* option string */
	char *inifile,	/* file name: 'ham2000.ini' */
	char *dpath,	/* ���� ���丮 ����: ��) "/usr/sskang/HAM/hdic/" */
	char *dic_usr,	/* ham-usr.dic */
	char *dic_cnn,	/* ham-cnn.dic */
	char *dic_stop);	/* stopword.dic */
extern PREFIX void close_HAM_index(HAM_RUNMODE *);
extern PREFIX int get_stems(		/* ���� or ���� ���� �������̽� */
	HAM_PUCHAR sent,	/* KSC5601 input sentence */
	HAM_PUCHAR keys[],	/* ptr. array of keywords */
	HAM_PRUNMODE mode);	/* running mode of HAM */
extern PREFIX int get_stems_TS(	/* ���� or ���� ���� & multi-thread */
	HAM_PUCHAR sent,	/* KSC5601 input sentence */
	HAM_PUCHAR keys[],	/* ptr. array of keywords */
	HAM_PUCHAR keylist,	/* keyword saving area */
	HAM_PMORES hamout,	/* morph. analysis result */
	HAM_PRUNMODE mode);	/* running mode of HAM */
extern PREFIX int get_terms_text(	/* ���� ���� �������̽� */
	unsigned char *text,	/* KSC5601 input text */
	HAM_TERMLIST term[],	/* array of extracted terms */
	HAM_TERMMEMORY *tm,		/* memories for term extraction */
	HAM_RUNMODE *mode,		/* running mode of HAM */
	int maxTerms,			/* ����� ����: ����� ���ڷ� ����� �ִ� ���� ���� */
	int sortflag,			/* 0: ����������(��� �ߺ�), 1: sort & unify(�ߺ� ����) */
	int widflag);			/* 0: ���� ����(1, 2, 3, ...), 1: �������(101, 102, 201, 202, ...) */
extern PREFIX int get_terms_file(	/* ���� ���� �������̽� -- ���� �Է� */
	char *fname,	/* input: text-file name */
	HAM_TERMLIST term[],	/* array of extracted terms */
	HAM_TERMMEMORY *tm,		/* memories for term extraction */
	HAM_RUNMODE *mode,		/* running mode of HAM */
	int maxTerms,			/* ����� ����: ����� ���ڷ� ����� �ִ� ���� ���� */
	int sortflag,			/* 0: ����������(��� �ߺ�), 1: sort & unify(�ߺ� ����) */
	int widflag);			/* 0: ���� ����(1, 2, 3, ...), 1: �������(101, 102, 201, 202, ...) */
extern PREFIX int get_terms_sent(	/* term-extraction from a sentence */
	unsigned char *sent,	/* KSC5601 input text */
	HAM_TERMLIST term[],	/* array of extracted terms */
	HAM_TERMMEMORY *tm,		/* memories for term extraction */
	HAM_RUNMODE *mode,		/* running mode of HAM */
	int weightflag);		/* term weighting ���� ����: 0(TF), 1(term weighting) */
extern PREFIX int set_options_from_file(char *, HAM_RUNMODE *);
/*--------------------------------- end of ham-api.h ---------------------------------*/
