#ifndef P_H
#define P_H


typedef struct page * Page;

Page init_page(int n_out, double rank);
double page_getRank(Page p);
void page_addLinkIn(Page p, char *token) ;
void page_addLinkOut(Page p, char *token);
void destroy_page(void *p);


#endif