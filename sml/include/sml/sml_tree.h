#ifndef _SML_TREE_H
#define	_SML_TREE_H

#include "sml_shared.h"
#include "sml_octet_string.h"
#include "sml_value.h"
#include "sml_time.h"

#ifdef __cplusplus
extern "C" {
#endif


#define SML_PROC_PAR_VALUE_TAG_VALUE 0x01
#define SML_PROC_PAR_VALUE_TAG_PERIOD_ENTRY 0x02
#define SML_PROC_PAR_VALUE_TAG_TUPEL_ENTRY 0x03
#define SML_PROC_PAR_VALUE_TAG_TIME 0x04


// TODO
typedef struct {
    u8 tag;
    union {
        sml_value *value;
        // sml_period_entry
        // sml_tupel_entry
        sml_time *time;
    } data;
} sml_proc_par_value;

typedef struct {
    octet_string **path_entries;
    int path_entries_len;
} sml_tree_path;

typedef struct s_tree{
    octet_string *parameter_name; 
    sml_proc_par_value *parameter_value; // optional
    struct s_tree **child_list; // optional
    int child_list_len; 
} sml_tree;

// SML_TREE_PATH
sml_tree_path *sml_tree_path_init();
void sml_tree_path_add_path_entry(sml_tree_path *tree_path, octet_string *entry);
void sml_tree_path_write(sml_tree_path *tree_path, sml_buffer *buf);
void sml_tree_path_free(sml_tree_path *tree_path);

// SML_TREE
sml_tree *sml_tree_init(octet_string *parameter_name);
void sml_tree_write(sml_tree *tree, sml_buffer *buf);
sml_tree *sml_tree_parse(sml_buffer *buf);
void sml_tree_free(sml_tree *tree);

// SML_PROC_PAR_VALUE
sml_proc_par_value *sml_proc_par_value_init(u8 tag, void *data);
void sml_proc_par_value_write(sml_proc_par_value *value, sml_buffer *buf);
void sml_proc_par_value_free(sml_proc_par_value *value);

#ifdef __cplusplus
}
#endif

#endif
