#include <stdio.h>
#include <stdlib.h>

typedef struct list_t {
    uintptr_t val;
    struct list_t *next;
} list_t;

typedef struct ttrie_t {
    char c;
    list_t *list;
    struct ttrie_t *lo,*eq,*hi;
} ttrie_t;

ttrie_t *alloc_ttrie(char c) {
    ttrie_t* t = (ttrie_t*)malloc(sizeof(ttrie_t));
    t->c = c;
    t->list = NULL;
    t->lo = t->eq = t->hi = NULL;
    return t;
}

list_t *alloc_list(uintptr_t val) {
    list_t* l = (list_t*)malloc(sizeof(list_t));
    l->val = val;
    l->next = NULL;
    return l;
}

int is_empty_ttrie(ttrie_t *t) {
    return (t->list == NULL) && (t->lo == NULL) && (t->eq == NULL) && (t->hi == NULL);
}

list_t *insert_list(list_t *p, uintptr_t val) {
    list_t* l= alloc_list(val);
    l->next = p;
    return l;
}

list_t *delete_list(list_t *p) {
    list_t *l = p->next;
    free(p);
    return l;
}

list_t *search_ttrie(ttrie_t *p, char *s) {
    if (!p) return 0;
    if (*s < p->c) return search_ttrie(p->hi, s);
    else if (*s > p->c) return search_ttrie(p->lo, s);

    if (*s==0) return p->list;
    return search_ttrie(p->eq,++s);
}

ttrie_t *rotate_lo_ttrie(ttrie_t *p) {
    ttrie_t *lo = p->lo;
    p->lo = lo->hi;
    lo->hi = p;
    return lo;
}

ttrie_t *rotate_hi_ttrie(ttrie_t *p) {
    ttrie_t *hi = p->hi;
    p->hi = hi->lo;
    hi->lo = p;
    return hi;
}

ttrie_t *insert_ttrie(ttrie_t *p, char *s, uintptr_t val) {
    if (!p) p = alloc_ttrie(*s);
    if (*s < p->c) p->lo = insert_ttrie(p->lo, s, val);
    else if (*s > p->c) p->hi = insert_ttrie(p->hi, s, val);
    else if (*s) p->eq = insert_ttrie(p->eq, s+1, val);
    else p->list = insert_list(p->list,val);
    return p;
}

ttrie_t *delete_ttrie(ttrie_t *p, char *s) {
    if (!p) return p;
    if (*s < p->c) p->lo = delete_ttrie(p->lo, s);
    else if (*s > p->c) p->hi = delete_ttrie(p->hi, s);
    else if (*s) p->eq = delete_ttrie(p->eq, s+1);
    else p->list = delete_list(p->list);
    if(is_empty_ttrie(p)) {
        free(p);
        p = NULL;
    }
    return p;
}

void traverse_list(list_t *l)
{
    if(l) {
        printf("%jd,",l->val);
        traverse_list(l->next);
    }
}

void traverse_ttrie(ttrie_t *p, char *buf, int i)
{
    if (!p) return;
    traverse_ttrie(p->lo,buf,i);
    if (p->c) {
        buf[i]=p->c;
        traverse_ttrie(p->eq,buf,i+1);
    }
    else {
        buf[i]=p->c;
        printf("%s:",buf);
        traverse_list(p->list);
        printf("\n");
    }
    traverse_ttrie(p->hi,buf,i);
}

int main(int argc, char *arg[]) {
    ttrie_t *root = NULL;
    char buf[10];
    root = insert_ttrie(root,"test",10);
    root = insert_ttrie(root,"tesa",20);
    root = insert_ttrie(root,"goto",30);
    root = insert_ttrie(root,"goto",70);
    root = insert_ttrie(root,"tes",40);
    root = delete_ttrie(root,"test");
    traverse_ttrie(root,buf,0);
    return search_ttrie(root,"afag");
}
