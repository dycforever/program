
struct radix_tree_root {
	unsigned int		height;
	struct radix_tree_node	*rnode;
};

#define RADIX_TREE_INDIRECT_PTR	1
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

static inline void *radix_tree_ptr_to_indirect(void *ptr)
{
	return (void *)((unsigned long)ptr | RADIX_TREE_INDIRECT_PTR);
}

static inline void *radix_tree_indirect_to_ptr(void *ptr)
{
	return (void *)((unsigned long)ptr & ~RADIX_TREE_INDIRECT_PTR);
}

static inline int radix_tree_is_indirect_ptr(void *ptr)
{
//	return (int)((unsigned long)ptr & RADIX_TREE_INDIRECT_PTR);
    return 1;
}

#define rcu_assign_pointer(p, v)	({ \
						(p) = (v); \
					})

#define rcu_dereference(p)     ({ \
				typeof(p) _________p1 = (p); \
				(_________p1); \
				})



int radix_tree_insert(struct radix_tree_root *root,
			unsigned long index, void *item);

void **radix_tree_lookup_slot(struct radix_tree_root *root, unsigned long index);

void *radix_tree_lookup(struct radix_tree_root *root, unsigned long index);

void *radix_tree_tag_set(struct radix_tree_root *root,
			unsigned long index, unsigned int tag);

void *radix_tree_tag_clear(struct radix_tree_root *root,
			unsigned long index, unsigned int tag);

int radix_tree_tag_get(struct radix_tree_root *root,
			unsigned long index, unsigned int tag);

unsigned long radix_tree_next_hole(struct radix_tree_root *root,
				unsigned long index, unsigned long max_scan);

unsigned int
radix_tree_gang_lookup(struct radix_tree_root *root, void **results,
			unsigned long first_index, unsigned int max_items);

unsigned int
radix_tree_gang_lookup_tag(struct radix_tree_root *root, void **results,
		unsigned long first_index, unsigned int max_items,
		unsigned int tag);

void *radix_tree_delete(struct radix_tree_root *root, unsigned long index);

int radix_tree_tagged(struct radix_tree_root *root, unsigned int tag);

struct radix_tree_root* radix_tree_init(void);
