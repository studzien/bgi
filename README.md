# BEAM guts inspector

## Index tables

### Atom table
```erlang
1> bgi_index:atoms().
[{0,false},
 {1,true},
 {2,'_'},
 {3,nonode@nohost},
 {4,'$end_of_table'},
 {5,''},
 {6,'fun'},
 {7,infinity},
 {8,timeout},
 {9,normal},
 {10,call},
 {11,return},
 {12,throw},
 {13,error},
 {14,exit},
 {15,undefined},
 {16,nocatch},
 {17,undefined_function},
 {18,undefined_lambda},
 {19,'DOWN'},
 {20,'UP'},
 {21,'EXIT'},
 {22,aborted},
 {23,abs_path},
 {24,absoluteURI},
 {25,ac},
 {26,active},
 {27,...},
 {...}|...]
```


### Export table
```erlang
2> bgi_index:exports().
[{erlang,alloc_info,1},
 {erlang,alloc_sizes,1},
 {erlang,gather_sched_wall_time_result,1},
 {erlang,gather_gc_info_result,1},
 {erlang,abs,1},
 {erlang,adler32,1},
 {erlang,adler32,2},
 {erlang,adler32_combine,3},
 {erlang,apply,3},
 {erlang,atom_to_list,1},
 {erlang,binary_to_list,1},
 {erlang,binary_to_list,3},
 {erlang,binary_to_term,1},
 {erlang,crc32,1},
 {erlang,crc32,2},
 {erlang,crc32_combine,3},
 {erlang,date,0},
 {erlang,delete_module,1},
 {erlang,display,1},
 {erlang,display_string,1},
 {erlang,display_nl,0},
 {erlang,element,2},
 {erlang,erase,0},
 {erlang,erase,1},
 {erlang,exit,1},
 {erlang,exit,2},
 {erlang,external_size,...},
 {erlang,...},
 {...}|...]
```

### Module table
```erlang
3> bgi_index:modules().
[otp_ring0,init,prim_eval,prim_inet,prim_file,zlib,prim_zip,
 erl_prim_loader,erlang,erts_internal,error_handler,heart,
 error_logger,gen_event,gen,proc_lib,application_controller,
 lists,gen_server,application,sys,application_master,kernel,
 supervisor,rpc,gb_trees,global,inet_db,inet_config|...]
```
