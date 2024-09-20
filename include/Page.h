#ifndef P_H
#define P_H


typedef struct page * Page;

Page init_page(int n_out, char * name, long double rank) ;
void page_rank(Page p, TST pages, int n);
int page_compare_by_rank(const void *a, const void *b);
long double page_getRank(Page p);
long double page_getLastRank(Page p);
char * page_getName(Page p);
char * page_getLinkIn(Page p, int i) ;
char * page_getLinkOut(Page p, int i) ;
int page_getNOut(Page p);
int page_getNIn(Page p) ;
void page_addLinkIn(Page p, char *token) ;
void page_addLinkOut(Page p, char *token);

void destroy_page(void *p);


#endif