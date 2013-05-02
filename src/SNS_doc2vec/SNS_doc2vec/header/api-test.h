/* USED ONLY FOR 'ADJUST_WORD_SPACING' OF INPUT SENTENCE */
extern PREFIX int load_bigram_data(char *filename);
extern PREFIX int load_bigram_dpath(char *dicpath, char *fname);

extern PREFIX int adjust_word_spacing(unsigned char sent[], int flag);
extern PREFIX int adjust_word_spacing_nsyl(
	unsigned char *sent,	/* ���� */
	unsigned char *sent2,	/* �ڵ� ���� �� ��� ���� */
	int maxsiz,				/* sent2[]�� ũ�� */
	int nsyl);	/* nsyl �̻��� �����鸸 ���� ����, nsyl < 0 �̸� ���� blank ���� */

extern PREFIX void free_bigram_data(void);

extern PREFIX unsigned char *HANJA2KSC(unsigned char *ksc, unsigned char *ksm);

extern PREFIX int convert_e2k(unsigned char *estring, unsigned char *kstring);
extern PREFIX int convert_k2e(unsigned char *kstring, unsigned char *estring);
