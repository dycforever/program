#include "radix_tree.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    struct radix_tree_root* root = radix_tree_init();
    int a = 1;
    assert(radix_tree_insert(root, 1, &a) == 0);
    int b = 12345;
    assert(radix_tree_insert(root, 12345, &b) == 0);

    printf("%d\n", *((int*)radix_tree_lookup(root, 1)) );
    printf("%d\n", *((int*)radix_tree_lookup(root, 12345)) );
    return 0;
}
