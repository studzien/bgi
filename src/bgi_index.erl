-module(bgi_index).

%% NIFs
-export([atom/1]).

%% Erlang functions
-export([atoms/0,
         exports/0,
         modules/0]).

-on_load(init/0).

-compile(export_all).

-define(nif_stub, nif_stub_error(?LINE)).
nif_stub_error(Line) ->
    erlang:nif_error({nif_not_loaded,module,?MODULE,line,Line}).

-ifdef(TEST).
-include_lib("eunit/include/eunit.hrl").
-endif.

init() ->
    PrivDir = case code:priv_dir(?MODULE) of
                  {error, bad_name} ->
                      EbinDir = filename:dirname(code:which(?MODULE)),
                      AppPath = filename:dirname(EbinDir),
                      filename:join(AppPath, "priv");
                  Path ->
                      Path
              end,
    erlang:load_nif(filename:join(PrivDir, ?MODULE), 0).

%%%===================================================================
%%% Exported Erlang functions
%%%===================================================================
atoms() ->
    MaxIndex = atom_table_size() - 1,
    [{Index, atom(Index)} || Index <- lists:seq(0, MaxIndex)]. 

exports() ->
    MaxIndex = export_table_size() - 1,
    [readable_export(Index) || Index <- lists:seq(0, MaxIndex)]. 

modules() ->
    MaxIndex = module_table_size() - 1,
    [atom(module(Module)) || Module <- lists:seq(0, MaxIndex)].

%%%===================================================================
%%% Exported NIFs
%%%===================================================================
atom(_Index) ->
    ?nif_stub.

export(_Index) ->
    ?nif_stub.

module(_Index) ->
    ?nif_stub.

%%%===================================================================
%%% Internal Erlang functions
%%%===================================================================
readable_export(Index) ->
    {TaggedM, TaggedF, Arity} = export(Index),
    {untag_atom(TaggedM), untag_atom(TaggedF), Arity}.

untag_atom(Atom) ->
    atom(Atom bsr 6).

%%%===================================================================
%%% Internal NIFs
%%%===================================================================
atom_table_size() ->
    ?nif_stub.

export_table_size() ->
    ?nif_stub.

module_table_size() ->
    ?nif_stub.
