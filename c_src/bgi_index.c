#include "erl_nif.h"
#include "beam/index.h"
#include "beam/atom.h"
#include "beam/export.h"
#include "beam/module.h"

extern uint32_t the_active_code_index;

// Prototypes
static ERL_NIF_TERM bgi_index_atom_1(ErlNifEnv* env, int argc,
                                     const ERL_NIF_TERM argv[]);
static ERL_NIF_TERM bgi_index_atom_table_size_0(ErlNifEnv* env, int argc,
                                                const ERL_NIF_TERM argv[]);
static ERL_NIF_TERM bgi_index_export_1(ErlNifEnv* env, int argc,
                                       const ERL_NIF_TERM argv[]);
static ERL_NIF_TERM bgi_index_export_table_size_0(ErlNifEnv* env, int argc,
                                                  const ERL_NIF_TERM argv[]);
static ERL_NIF_TERM bgi_index_module_1(ErlNifEnv* env, int argc,
                                       const ERL_NIF_TERM argv[]);
static ERL_NIF_TERM bgi_index_module_table_size_0(ErlNifEnv* env, int argc,
                                                  const ERL_NIF_TERM argv[]);

static ErlNifFunc nif_funcs[] =
{
    {"atom", 1, bgi_index_atom_1},
    {"atom_table_size", 0, bgi_index_atom_table_size_0},
    {"export", 1, bgi_index_export_1},
    {"export_table_size", 0, bgi_index_export_table_size_0},
    {"module", 1, bgi_index_module_1},
    {"module_table_size", 0, bgi_index_module_table_size_0}
};

static ERL_NIF_TERM bgi_index_atom_1(ErlNifEnv* env, int argc,
                                     const ERL_NIF_TERM argv[])
{
    int atom;
    if(!enif_get_int(env, argv[0], &atom) || atom >= erts_atom_table.entries) {
        return enif_make_badarg(env);
    }

    Atom* atom_entry = (Atom*)erts_index_lookup(&erts_atom_table, atom);
    if(atom_entry == NULL) {
        return enif_make_badarg(env);
    }

    return enif_make_atom_len(env, atom_entry->name, atom_entry->len);
}

static ERL_NIF_TERM bgi_index_atom_table_size_0(ErlNifEnv* env, int argc,
                                                const ERL_NIF_TERM argv[])
{
    return enif_make_int(env, erts_atom_table.entries);
}

static ERL_NIF_TERM bgi_index_export_1(ErlNifEnv* env, int argc,
                                       const ERL_NIF_TERM argv[])
{
    int size = export_list_size(the_active_code_index);
    int export;

    if(!enif_get_int(env, argv[0], &export) || export >= size) {
        return enif_make_badarg(env);
    }

    Export* e = export_list(export, (unsigned)the_active_code_index);
    if(e == NULL) {
        return enif_make_badarg(env);
    }

    ERL_NIF_TERM module = enif_make_int(env, (int)e->code[0]);
    ERL_NIF_TERM function = enif_make_int(env, (int)e->code[1]);
    ERL_NIF_TERM arity = enif_make_int(env, (int)e->code[2]);
    return enif_make_tuple3(env, module, function, arity);
}

static ERL_NIF_TERM bgi_index_export_table_size_0(ErlNifEnv* env, int argc,
                                                  const ERL_NIF_TERM argv[])
{
    return enif_make_int(env, export_list_size(the_active_code_index));
}

static ERL_NIF_TERM bgi_index_module_1(ErlNifEnv* env, int argc,
                                       const ERL_NIF_TERM argv[])
{
    int size = module_code_size(the_active_code_index);
    int module;
    if(!enif_get_int(env, argv[0], &module) || module >= size) {
        return enif_make_badarg(env);
    }

    Module *m = module_code(module, the_active_code_index);
    if(m == NULL) {
        return enif_make_badarg(env);
    }

    return enif_make_int(env, m->module); 
}

static ERL_NIF_TERM bgi_index_module_table_size_0(ErlNifEnv* env, int argc,
                                                  const ERL_NIF_TERM argv[])
{
    return enif_make_int(env, module_code_size(the_active_code_index));
}

static int on_load(ErlNifEnv* env, void** priv_data, ERL_NIF_TERM load_info)
{
    return 0;
}

ERL_NIF_INIT(bgi_index, nif_funcs, &on_load, NULL, NULL, NULL);
