- [ ] : ~~Inverted expand path (for tilde prompt)~~
- [x] : Manage clear_history function location
- [ ] : $ comportment for special characters
- [x] : Expand $?
- [ ] : Segfault handle
- [x] : Manage return values
- [x] : Manage error loggin
- [x] : Implementation Env -i
- [!] : Shell level
- [?] : Leaks
- [ ] : Norminette
- [ ] : ~~Stat function~~
- [x] : Test with symbolic link
- [x] : Get path of symlink
- [x] : Message erreur export et unset
- [x] : export peut prendre plusieur args


LOG :
minishell /mnt/nfs/homes/mriaud/42/c3/minishell > $$
minishell: $: command not found
==9835==
==9835== HEAP SUMMARY:
==9835==     in use at exit: 204,749 bytes in 216 blocks
==9835==   total heap usage: 1,511 allocs, 1,295 frees, 276,143 bytes allocated
==9835==
==9835== LEAK SUMMARY:
==9835==    definitely lost: 0 bytes in 0 blocks
==9835==    indirectly lost: 0 bytes in 0 blocks
==9835==      possibly lost: 0 bytes in 0 blocks
==9835==    still reachable: 0 bytes in 0 blocks
==9835==         suppressed: 204,749 bytes in 216 blocks
==9835==
==9835== For lists of detected and suppressed errors, rerun with: -s
==9835== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
minishell /mnt/nfs/homes/mriaud/42/c3/minishell > echo ?$
?
minishell /mnt/nfs/homes/mriaud/42/c3/minishell > $$
minishell: $: command not found
==9936==
==9936== HEAP SUMMARY:
==9936==     in use at exit: 204,774 bytes in 218 blocks
==9936==   total heap usage: 1,825 allocs, 1,607 frees, 295,155 bytes allocated
==9936==
minishell /mnt/nfs/homes/mriaud/42/c3/minishell > export 1a=5
minishell /mnt/nfs/homes/mriaud/42/c3/minishell > export _1a=5
minishell /mnt/nfs/homes/mriaud/42/c3/minishell > ls
dep  ignoreleak  inc  Makefile  minishell  obj  README.md  src  test
minishell /mnt/nfs/homes/mriaud/42/c3/minishell > touch perm && chmod 000 perm
minishell /mnt/nfs/homes/mriaud/42/c3/minishell > echo lol > perm
minishell /mnt/nfs/homes/mriaud/42/c3/minishell > s
minishell: s: command not found
==11637==
==11637== HEAP SUMMARY:
==11637==     in use at exit: 204,881 bytes in 218 blocks
==11637==   total heap usage: 5,677 allocs, 5,459 frees, 636,308 bytes allocated
==11637==
==11637== 81 bytes in 2 blocks are definitely lost in loss record 17 of 60
==11637==    at 0x483DFAF: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==11637==    by 0x49C30A7: getcwd (getcwd.c:84)
==11637==    by 0x10EBC9: swap_pwd (cd.c:33)
==11637==    by 0x10ED03: cmd_cd (cd.c:69)
==11637==    by 0x10CBD8: run_cmd (run_process.c:61)
==11637==    by 0x10CDF7: run_process (run_process.c:114)
==11637==    by 0x10975F: main (main.c:81)
==11637==
==11637== LEAK SUMMARY:
==11637==    definitely lost: 81 bytes in 2 blocks
==11637==    indirectly lost: 0 bytes in 0 blocks
==11637==      possibly lost: 0 bytes in 0 blocks
==11637==    still reachable: 0 bytes in 0 blocks
==11637==         suppressed: 204,800 bytes in 216 blocks
==11637==
==11637== For lists of detected and suppressed errors, rerun with: -s
==11637== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
minishell /mnt/nfs/homes/mriaud/42/c3/minishell >

A TEST ET FIX:
minishell /mnt/nfs/homes/mriaud/42/c3/minishell > unset PATH
minishell /mnt/nfs/homes/mriaud/42/c3/minishell > ls


minishell /mnt/nfs/homes/mriaud/42/c3/minishell > cat << $USER > out
> lol
> $PWD
> $USER
> mriaud
==15195==
==15195== HEAP SUMMARY:
==15195==     in use at exit: 204,669 bytes in 216 blocks
==15195==   total heap usage: 3,258 allocs, 3,042 frees, 376,420 bytes allocated
==15195==
==15195== LEAK SUMMARY:
==15195==    definitely lost: 0 bytes in 0 blocks
==15195==    indirectly lost: 0 bytes in 0 blocks
==15195==      possibly lost: 0 bytes in 0 blocks
==15195==    still reachable: 0 bytes in 0 blocks
==15195==         suppressed: 204,669 bytes in 216 blocks
==15195==
==15195== For lists of detected and suppressed errors, rerun with: -s
==15195== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==15267== Invalid read of size 4
==15267==    at 0x10C24D: get_exec_path (paths.c:30)
==15267==    by 0x10CB15: run_cmd (run_process.c:51)
==15267==    by 0x10CC84: execute (run_process.c:77)
==15267==    by 0x10CDDF: run_process (run_process.c:112)
==15267==    by 0x10975F: main (main.c:81)
==15267==  Address 0x4b5d9e8 is 8 bytes inside a block of size 32 free'd
==15267==    at 0x483CA3F: free (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==15267==    by 0x109E06: free_allocs (t_alloc.c:52)
==15267==    by 0x109B1A: xfree_group (memory.c:107)
==15267==    by 0x10C344: refresh_paths (paths.c:49)
==15267==    by 0x1096D1: main (main.c:68)
==15267==  Block was alloc'd at
==15267==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==15267==    by 0x109D7C: new_alloc (t_alloc.c:32)
==15267==    by 0x109817: xmalloc (memory.c:32)
==15267==    by 0x10D831: split_lst_normal (split_lst.c:28)
==15267==    by 0x10C384: refresh_paths (paths.c:52)
==15267==    by 0x1096D1: main (main.c:68)
==15267==
==15267== Invalid read of size 4
==15267==    at 0x10DC56: merge (merge.c:17)
==15267==    by 0x10C295: get_exec_path (paths.c:32)
==15267==    by 0x10CB15: run_cmd (run_process.c:51)
==15267==    by 0x10CC84: execute (run_process.c:77)
==15267==    by 0x10CDDF: run_process (run_process.c:112)
==15267==    by 0x10975F: main (main.c:81)
==15267==  Address 0x4b5d9e8 is 8 bytes inside a block of size 32 free'd
==15267==    at 0x483CA3F: free (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==15267==    by 0x109E06: free_allocs (t_alloc.c:52)
==15267==    by 0x109B1A: xfree_group (memory.c:107)
==15267==    by 0x10C344: refresh_paths (paths.c:49)
==15267==    by 0x1096D1: main (main.c:68)
==15267==  Block was alloc'd at
==15267==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==15267==    by 0x109D7C: new_alloc (t_alloc.c:32)
==15267==    by 0x109817: xmalloc (memory.c:32)
==15267==    by 0x10D831: split_lst_normal (split_lst.c:28)
==15267==    by 0x10C384: refresh_paths (paths.c:52)
==15267==    by 0x1096D1: main (main.c:68)
==15267==
==15267== Invalid read of size 8
==15267==    at 0x10DC89: merge (merge.c:22)
==15267==    by 0x10C295: get_exec_path (paths.c:32)
==15267==    by 0x10CB15: run_cmd (run_process.c:51)
==15267==    by 0x10CC84: execute (run_process.c:77)
==15267==    by 0x10CDDF: run_process (run_process.c:112)
==15267==    by 0x10975F: main (main.c:81)
==15267==  Address 0x4b5d9e0 is 0 bytes inside a block of size 32 free'd
==15267==    at 0x483CA3F: free (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==15267==    by 0x109E06: free_allocs (t_alloc.c:52)
==15267==    by 0x109B1A: xfree_group (memory.c:107)
==15267==    by 0x10C344: refresh_paths (paths.c:49)
==15267==    by 0x1096D1: main (main.c:68)
==15267==  Block was alloc'd at
==15267==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==15267==    by 0x109D7C: new_alloc (t_alloc.c:32)
==15267==    by 0x109817: xmalloc (memory.c:32)
==15267==    by 0x10D831: split_lst_normal (split_lst.c:28)
==15267==    by 0x10C384: refresh_paths (paths.c:52)
==15267==    by 0x1096D1: main (main.c:68)
==15267==
==15267== Invalid read of size 4
==15267==    at 0x10DCF4: merge (merge.c:25)
==15267==    by 0x10C295: get_exec_path (paths.c:32)
==15267==    by 0x10CB15: run_cmd (run_process.c:51)
==15267==    by 0x10CC84: execute (run_process.c:77)
==15267==    by 0x10CDDF: run_process (run_process.c:112)
==15267==    by 0x10975F: main (main.c:81)
==15267==  Address 0x4b5d9e8 is 8 bytes inside a block of size 32 free'd
==15267==    at 0x483CA3F: free (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==15267==    by 0x109E06: free_allocs (t_alloc.c:52)
==15267==    by 0x109B1A: xfree_group (memory.c:107)
==15267==    by 0x10C344: refresh_paths (paths.c:49)
==15267==    by 0x1096D1: main (main.c:68)
==15267==  Block was alloc'd at
==15267==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==15267==    by 0x109D7C: new_alloc (t_alloc.c:32)
==15267==    by 0x109817: xmalloc (memory.c:32)
==15267==    by 0x10D831: split_lst_normal (split_lst.c:28)
==15267==    by 0x10C384: refresh_paths (paths.c:52)
==15267==    by 0x1096D1: main (main.c:68)
==15267==
==15267== Invalid read of size 8
==15267==    at 0x10DCC4: merge (merge.c:26)
==15267==    by 0x10C295: get_exec_path (paths.c:32)
==15267==    by 0x10CB15: run_cmd (run_process.c:51)
==15267==    by 0x10CC84: execute (run_process.c:77)
==15267==    by 0x10CDDF: run_process (run_process.c:112)
==15267==    by 0x10975F: main (main.c:81)
==15267==  Address 0x4b5d9e0 is 0 bytes inside a block of size 32 free'd
==15267==    at 0x483CA3F: free (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==15267==    by 0x109E06: free_allocs (t_alloc.c:52)
==15267==    by 0x109B1A: xfree_group (memory.c:107)
==15267==    by 0x10C344: refresh_paths (paths.c:49)
==15267==    by 0x1096D1: main (main.c:68)
==15267==  Block was alloc'd at
==15267==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==15267==    by 0x109D7C: new_alloc (t_alloc.c:32)
==15267==    by 0x109817: xmalloc (memory.c:32)
==15267==    by 0x10D831: split_lst_normal (split_lst.c:28)
==15267==    by 0x10C384: refresh_paths (paths.c:52)
==15267==    by 0x1096D1: main (main.c:68)
==15267==
==15267== Invalid read of size 1
==15267==    at 0x10DCEB: merge (merge.c:26)
==15267==    by 0x10C295: get_exec_path (paths.c:32)
==15267==    by 0x10CB15: run_cmd (run_process.c:51)
==15267==    by 0x10CC84: execute (run_process.c:77)
==15267==    by 0x10CDDF: run_process (run_process.c:112)
==15267==    by 0x10975F: main (main.c:81)
==15267==  Address 0x4b5daa0 is 0 bytes inside a block of size 26 free'd
==15267==    at 0x483CA3F: free (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==15267==    by 0x109E06: free_allocs (t_alloc.c:52)
==15267==    by 0x109B1A: xfree_group (memory.c:107)
==15267==    by 0x10C344: refresh_paths (paths.c:49)
==15267==    by 0x1096D1: main (main.c:68)
==15267==  Block was alloc'd at
==15267==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==15267==    by 0x109D7C: new_alloc (t_alloc.c:32)
==15267==    by 0x109817: xmalloc (memory.c:32)
==15267==    by 0x10D853: split_lst_normal (split_lst.c:29)
==15267==    by 0x10C384: refresh_paths (paths.c:52)
==15267==    by 0x1096D1: main (main.c:68)
==15267==
==15267== Invalid read of size 8
==15267==    at 0x10C2EE: get_exec_path (paths.c:40)
==15267==    by 0x10CB15: run_cmd (run_process.c:51)
==15267==    by 0x10CC84: execute (run_process.c:77)
==15267==    by 0x10CDDF: run_process (run_process.c:112)
==15267==    by 0x10975F: main (main.c:81)
==15267==  Address 0x4b5d9f0 is 16 bytes inside a block of size 32 free'd
==15267==    at 0x483CA3F: free (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==15267==    by 0x109E06: free_allocs (t_alloc.c:52)
==15267==    by 0x109B1A: xfree_group (memory.c:107)
==15267==    by 0x10C344: refresh_paths (paths.c:49)
==15267==    by 0x1096D1: main (main.c:68)
==15267==  Block was alloc'd at
==15267==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==15267==    by 0x109D7C: new_alloc (t_alloc.c:32)
==15267==    by 0x109817: xmalloc (memory.c:32)
==15267==    by 0x10D831: split_lst_normal (split_lst.c:28)
==15267==    by 0x10C384: refresh_paths (paths.c:52)
==15267==    by 0x1096D1: main (main.c:68)
==15267==
