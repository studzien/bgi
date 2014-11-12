-module(bgi_index).

%% NIFs
-export([atom/1]).

%% Erlang functions
-export([atoms/0]).

-on_load(init/0).

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

%%%===================================================================
%%% Exported NIFs
%%%===================================================================
atom(_Index) ->
    ?nif_stub.

%%%===================================================================
%%% Internal Erlang functions
%%%===================================================================

%%%===================================================================
%%% Internal NIFs
%%%===================================================================
atom_table_size() ->
    ?nif_stub.
