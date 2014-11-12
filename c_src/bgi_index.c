#include "erl_nif.h"
#include "beam/index.h"
#include "beam/atom.h"

extern IndexTable erts_atom_table;

// Prototypes
static ERL_NIF_TERM bgi_index_atom_1(ErlNifEnv* env, int argc,
                                     const ERL_NIF_TERM argv[]);
static ERL_NIF_TERM bgi_index_atom_table_size_0(ErlNifEnv* env, int argc,
                                                const ERL_NIF_TERM argv[]);

static ErlNifFunc nif_funcs[] =
{
    {"atom", 1, bgi_index_atom_1},
    {"atom_table_size", 0, bgi_index_atom_table_size_0}
};

static ERL_NIF_TERM bgi_index_atom_1(ErlNifEnv* env, int argc,
                                     const ERL_NIF_TERM argv[])
{
    int atom;
    if(!enif_get_int(env, argv[0], &atom)) {
        return enif_make_badarg(env);
    }

    if(atom >= erts_atom_table.entries) {
       return enif_make_badarg(env);
    } 

    Atom* atom_entry = (Atom*)erts_index_lookup(&erts_atom_table, atom);
    return enif_make_atom_len(env, atom_entry->name, atom_entry->len);
}

static ERL_NIF_TERM bgi_index_atom_table_size_0(ErlNifEnv* env, int argc,
                                                const ERL_NIF_TERM argv[])
{
    return enif_make_int(env, erts_atom_table.entries);
}

static int on_load(ErlNifEnv* env, void** priv_data, ERL_NIF_TERM load_info)
{
    return 0;
}

ERL_NIF_INIT(bgi_index, nif_funcs, &on_load, NULL, NULL, NULL);
