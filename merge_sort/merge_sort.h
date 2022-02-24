
// comb sort for linked list

struct S_node 
{
   struct S_node *next;
   unsigned char data[];
};

struct S_node *merge_sort (struct S_node *first, int (* cmp) (const struct S_node *, const struct S_node *));
