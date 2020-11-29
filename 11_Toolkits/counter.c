#include <glib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE 81


int compare_ints(gpointer a, gpointer b, gpointer hash) {
    gpointer va = g_hash_table_lookup(hash, (char *) a);
    gpointer vb = g_hash_table_lookup(hash, (char *) b);
    return GPOINTER_TO_INT(va) - GPOINTER_TO_INT(vb);
}


int main(void) {

    GHashTable* hash = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);

    while (!feof(stdin)) {
        char buf[MAX_LINE] = {0};
        fgets(buf, MAX_LINE, stdin);

        gchar ** words = g_strsplit_set(buf, " \t\n", -1);
        for (char ** key = words; *key; key++) {
            
            g_strstrip(*key);
            if (strlen(*key) == 0) {
                continue;
            }
            
            gpointer n = g_hash_table_lookup(hash, *key);

            if (n == NULL) {
                g_hash_table_insert(hash, g_strdup(*key), GINT_TO_POINTER(1));
            } else {
                int m = GPOINTER_TO_INT(n) + 1;
                g_hash_table_insert(hash, g_strdup(*key), GINT_TO_POINTER(m));
            }
        }

        g_strfreev(words);
    }

    GList* lst = g_hash_table_get_keys(hash);

    GList* new_lst = g_list_sort_with_data(lst, (GCompareDataFunc) compare_ints, hash);
    for (GList* it = new_lst; it; it = it->next) {
        char * key = (char *) it->data;
        gpointer v = g_hash_table_lookup(hash, key);
        printf("%10d\t%s\n", GPOINTER_TO_INT(v), key);
    }

    g_hash_table_destroy(hash);
    g_list_free(new_lst);

    return 0;
}
