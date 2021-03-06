#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include "sys_call_table.h"

#pragma mark - APIs -
void init_sys_call_array();

char* get_sys_call_name(long sys_call_number){
    if(strcmp(sys_call_names[0], "read") < 0){
        init_sys_call_array();
    }
    return sys_call_names[sys_call_number];
}

void init_sys_call_array(){

strcpy(sys_call_names[0], "read");
strcpy(sys_call_names[1], "write");
strcpy(sys_call_names[2], "open");
strcpy(sys_call_names[3], "close");
strcpy(sys_call_names[4], "stat");
strcpy(sys_call_names[5], "fstat");
strcpy(sys_call_names[6], "lstat");
strcpy(sys_call_names[7], "poll");
strcpy(sys_call_names[8], "lseek");
strcpy(sys_call_names[9], "mmap");
strcpy(sys_call_names[10], "mprotect");
strcpy(sys_call_names[11], "munmap");
strcpy(sys_call_names[12], "brk");
strcpy(sys_call_names[13], "rt_sigaction");
strcpy(sys_call_names[14], "rt_sigprocmask");
strcpy(sys_call_names[15], "rt_sigreturn");
strcpy(sys_call_names[16], "ioctl");
strcpy(sys_call_names[17], "pread64");
strcpy(sys_call_names[18], "pwrite64");
strcpy(sys_call_names[19], "readv");
strcpy(sys_call_names[20], "writev");
strcpy(sys_call_names[21], "access");
strcpy(sys_call_names[22], "pipe");
strcpy(sys_call_names[23], "select");
strcpy(sys_call_names[24], "sched_yield");
strcpy(sys_call_names[25], "mremap");
strcpy(sys_call_names[26], "msync");
strcpy(sys_call_names[27], "mincore");
strcpy(sys_call_names[28], "madvise");
strcpy(sys_call_names[29], "shmget");
strcpy(sys_call_names[30], "shmat");
strcpy(sys_call_names[31], "shmctl");
strcpy(sys_call_names[32], "dup");
strcpy(sys_call_names[33], "dup2");
strcpy(sys_call_names[34], "pause");
strcpy(sys_call_names[35], "nanosleep");
strcpy(sys_call_names[36], "getitimer");
strcpy(sys_call_names[37], "alarm");
strcpy(sys_call_names[38], "setitimer");
strcpy(sys_call_names[39], "getpid");
strcpy(sys_call_names[40], "sendfile");
strcpy(sys_call_names[41], "socket");
strcpy(sys_call_names[42], "connect");
strcpy(sys_call_names[43], "accept");
strcpy(sys_call_names[44], "sendto");
strcpy(sys_call_names[45], "recvfrom");
strcpy(sys_call_names[46], "sendmsg");
strcpy(sys_call_names[47], "recvmsg");
strcpy(sys_call_names[48], "shutdown");
strcpy(sys_call_names[49], "bind");
strcpy(sys_call_names[50], "listen");
strcpy(sys_call_names[51], "getsockname");
strcpy(sys_call_names[52], "getpeername");
strcpy(sys_call_names[53], "socketpair");
strcpy(sys_call_names[54], "setsockopt");
strcpy(sys_call_names[55], "getsockopt");
strcpy(sys_call_names[56], "clone");
strcpy(sys_call_names[57], "fork");
strcpy(sys_call_names[58], "vfork");
strcpy(sys_call_names[59], "execve");
strcpy(sys_call_names[60], "exit");
strcpy(sys_call_names[61], "wait4");
strcpy(sys_call_names[62], "kill");
strcpy(sys_call_names[63], "uname");
strcpy(sys_call_names[64], "semget");
strcpy(sys_call_names[65], "semop");
strcpy(sys_call_names[66], "semctl");
strcpy(sys_call_names[67], "shmdt");
strcpy(sys_call_names[68], "msgget");
strcpy(sys_call_names[69], "msgsnd");
strcpy(sys_call_names[70], "msgrcv");
strcpy(sys_call_names[71], "msgctl");
strcpy(sys_call_names[72], "fcntl");
strcpy(sys_call_names[73], "flock");
strcpy(sys_call_names[74], "fsync");
strcpy(sys_call_names[75], "fdatasync");
strcpy(sys_call_names[76], "truncate");
strcpy(sys_call_names[77], "ftruncate");
strcpy(sys_call_names[78], "getdents");
strcpy(sys_call_names[79], "getcwd");
strcpy(sys_call_names[80], "chdir");
strcpy(sys_call_names[81], "fchdir");
strcpy(sys_call_names[82], "rename");
strcpy(sys_call_names[83], "mkdir");
strcpy(sys_call_names[84], "rmdir");
strcpy(sys_call_names[85], "creat");
strcpy(sys_call_names[86], "link");
strcpy(sys_call_names[87], "unlink");
strcpy(sys_call_names[88], "symlink");
strcpy(sys_call_names[89], "readlink");
strcpy(sys_call_names[90], "chmod");
strcpy(sys_call_names[91], "fchmod");
strcpy(sys_call_names[92], "chown");
strcpy(sys_call_names[93], "fchown");
strcpy(sys_call_names[94], "lchown");
strcpy(sys_call_names[95], "umask");
strcpy(sys_call_names[96], "gettimeofday");
strcpy(sys_call_names[97], "getrlimit");
strcpy(sys_call_names[98], "getrusage");
strcpy(sys_call_names[99], "sysinfo");
strcpy(sys_call_names[100], "times");
strcpy(sys_call_names[101], "ptrace");
strcpy(sys_call_names[102], "getuid");
strcpy(sys_call_names[103], "syslog");
strcpy(sys_call_names[104], "getgid");
strcpy(sys_call_names[105], "setuid");
strcpy(sys_call_names[106], "setgid");
strcpy(sys_call_names[107], "geteuid");
strcpy(sys_call_names[108], "getegid");
strcpy(sys_call_names[109], "setpgid");
strcpy(sys_call_names[110], "getppid");
strcpy(sys_call_names[111], "getpgrp");
strcpy(sys_call_names[112], "setsid");
strcpy(sys_call_names[113], "setreuid");
strcpy(sys_call_names[114], "setregid");
strcpy(sys_call_names[115], "getgroups");
strcpy(sys_call_names[116], "setgroups");
strcpy(sys_call_names[117], "setresuid");
strcpy(sys_call_names[118], "getresuid");
strcpy(sys_call_names[119], "setresgid");
strcpy(sys_call_names[120], "getresgid");
strcpy(sys_call_names[121], "getpgid");
strcpy(sys_call_names[122], "setfsuid");
strcpy(sys_call_names[123], "setfsgid");
strcpy(sys_call_names[124], "getsid");
strcpy(sys_call_names[125], "capget");
strcpy(sys_call_names[126], "capset");
strcpy(sys_call_names[127], "rt_sigpending");
strcpy(sys_call_names[128], "rt_sigtimedwait");
strcpy(sys_call_names[129], "rt_sigqueueinfo");
strcpy(sys_call_names[130], "rt_sigsuspend");
strcpy(sys_call_names[131], "sigaltstack");
strcpy(sys_call_names[132], "utime");
strcpy(sys_call_names[133], "mknod");
strcpy(sys_call_names[134], "uselib");
strcpy(sys_call_names[135], "personality");
strcpy(sys_call_names[136], "ustat");
strcpy(sys_call_names[137], "statfs");
strcpy(sys_call_names[138], "fstatfs");
strcpy(sys_call_names[139], "sysfs");
strcpy(sys_call_names[140], "getpriority");
strcpy(sys_call_names[141], "setpriority");
strcpy(sys_call_names[142], "sched_setparam");
strcpy(sys_call_names[143], "sched_getparam");
strcpy(sys_call_names[144], "sched_setscheduler");
strcpy(sys_call_names[145], "sched_getscheduler");
strcpy(sys_call_names[146], "sched_get_priority_max");
strcpy(sys_call_names[147], "sched_get_priority_min");
strcpy(sys_call_names[148], "sched_rr_get_interval");
strcpy(sys_call_names[149], "mlock");
strcpy(sys_call_names[150], "munlock");
strcpy(sys_call_names[151], "mlockall");
strcpy(sys_call_names[152], "munlockall");
strcpy(sys_call_names[153], "vhangup");
strcpy(sys_call_names[154], "modify_ldt");
strcpy(sys_call_names[155], "pivot_root");
strcpy(sys_call_names[156], "_sysctl");
strcpy(sys_call_names[157], "prctl");
strcpy(sys_call_names[158], "arch_prctl");
strcpy(sys_call_names[159], "adjtimex");
strcpy(sys_call_names[160], "setrlimit");
strcpy(sys_call_names[161], "chroot");
strcpy(sys_call_names[162], "sync");
strcpy(sys_call_names[163], "acct");
strcpy(sys_call_names[164], "settimeofday");
strcpy(sys_call_names[165], "mount");
strcpy(sys_call_names[166], "umount2");
strcpy(sys_call_names[167], "swapon");
strcpy(sys_call_names[168], "swapoff");
strcpy(sys_call_names[169], "reboot");
strcpy(sys_call_names[170], "sethostname");
strcpy(sys_call_names[171], "setdomainname");
strcpy(sys_call_names[172], "iopl");
strcpy(sys_call_names[173], "ioperm");
strcpy(sys_call_names[174], "create_module");
strcpy(sys_call_names[175], "init_module");
strcpy(sys_call_names[176], "delete_module");
strcpy(sys_call_names[177], "get_kernel_syms");
strcpy(sys_call_names[178], "query_module");
strcpy(sys_call_names[179], "quotactl");
strcpy(sys_call_names[180], "nfsservctl");
strcpy(sys_call_names[181], "getpmsg");
strcpy(sys_call_names[182], "putpmsg");
strcpy(sys_call_names[183], "afs_syscall");
strcpy(sys_call_names[184], "tuxcall");
strcpy(sys_call_names[185], "security");
strcpy(sys_call_names[186], "gettid");
strcpy(sys_call_names[187], "readahead");
strcpy(sys_call_names[188], "setxattr");
strcpy(sys_call_names[189], "lsetxattr");
strcpy(sys_call_names[190], "fsetxattr");
strcpy(sys_call_names[191], "getxattr");
strcpy(sys_call_names[192], "lgetxattr");
strcpy(sys_call_names[193], "fgetxattr");
strcpy(sys_call_names[194], "listxattr");
strcpy(sys_call_names[195], "llistxattr");
strcpy(sys_call_names[196], "flistxattr");
strcpy(sys_call_names[197], "removexattr");
strcpy(sys_call_names[198], "lremovexattr");
strcpy(sys_call_names[199], "fremovexattr");
strcpy(sys_call_names[200], "tkill");
strcpy(sys_call_names[201], "time");
strcpy(sys_call_names[202], "futex");
strcpy(sys_call_names[203], "sched_setaffinity");
strcpy(sys_call_names[204], "sched_getaffinity");
strcpy(sys_call_names[205], "set_thread_area");
strcpy(sys_call_names[206], "io_setup");
strcpy(sys_call_names[207], "io_destroy");
strcpy(sys_call_names[208], "io_getevents");
strcpy(sys_call_names[209], "io_submit");
strcpy(sys_call_names[210], "io_cancel");
strcpy(sys_call_names[211], "get_thread_area");
strcpy(sys_call_names[212], "lookup_dcookie");
strcpy(sys_call_names[213], "epoll_create");
strcpy(sys_call_names[214], "epoll_ctl_old");
strcpy(sys_call_names[215], "epoll_wait_old");
strcpy(sys_call_names[216], "remap_file_pages");
strcpy(sys_call_names[217], "getdents64");
strcpy(sys_call_names[218], "set_tid_address");
strcpy(sys_call_names[219], "restart_syscall");
strcpy(sys_call_names[220], "semtimedop");
strcpy(sys_call_names[221], "fadvise64");
strcpy(sys_call_names[222], "timer_create");
strcpy(sys_call_names[223], "timer_settime");
strcpy(sys_call_names[224], "timer_gettime");
strcpy(sys_call_names[225], "timer_getoverrun");
strcpy(sys_call_names[226], "timer_delete");
strcpy(sys_call_names[227], "clock_settime");
strcpy(sys_call_names[228], "clock_gettime");
strcpy(sys_call_names[229], "clock_getres");
strcpy(sys_call_names[230], "clock_nanosleep");
strcpy(sys_call_names[231], "exit_group");
strcpy(sys_call_names[232], "epoll_wait");
strcpy(sys_call_names[233], "epoll_ctl");
strcpy(sys_call_names[234], "tgkill");
strcpy(sys_call_names[235], "utimes");
strcpy(sys_call_names[236], "vserver");
strcpy(sys_call_names[237], "mbind");
strcpy(sys_call_names[238], "set_mempolicy");
strcpy(sys_call_names[239], "get_mempolicy");
strcpy(sys_call_names[240], "mq_open");
strcpy(sys_call_names[241], "mq_unlink");
strcpy(sys_call_names[242], "mq_timedsend");
strcpy(sys_call_names[243], "mq_timedreceive");
strcpy(sys_call_names[244], "mq_notify");
strcpy(sys_call_names[245], "mq_getsetattr");
strcpy(sys_call_names[246], "kexec_load");
strcpy(sys_call_names[247], "waitid");
strcpy(sys_call_names[248], "add_key");
strcpy(sys_call_names[249], "request_key");
strcpy(sys_call_names[250], "keyctl");
strcpy(sys_call_names[251], "ioprio_set");
strcpy(sys_call_names[252], "ioprio_get");
strcpy(sys_call_names[253], "inotify_init");
strcpy(sys_call_names[254], "inotify_add_watch");
strcpy(sys_call_names[255], "inotify_rm_watch");
strcpy(sys_call_names[256], "migrate_pages");
strcpy(sys_call_names[257], "openat");
strcpy(sys_call_names[258], "mkdirat");
strcpy(sys_call_names[259], "mknodat");
strcpy(sys_call_names[260], "fchownat");
strcpy(sys_call_names[261], "futimesat");
strcpy(sys_call_names[262], "newfstatat");
strcpy(sys_call_names[263], "unlinkat");
strcpy(sys_call_names[264], "renameat");
strcpy(sys_call_names[265], "linkat");
strcpy(sys_call_names[266], "symlinkat");
strcpy(sys_call_names[267], "readlinkat");
strcpy(sys_call_names[268], "fchmodat");
strcpy(sys_call_names[269], "faccessat");
strcpy(sys_call_names[270], "pselect6");
strcpy(sys_call_names[271], "ppoll");
strcpy(sys_call_names[272], "unshare");
strcpy(sys_call_names[273], "set_robust_list");
strcpy(sys_call_names[274], "get_robust_list");
strcpy(sys_call_names[275], "splice");
strcpy(sys_call_names[276], "tee");
strcpy(sys_call_names[277], "sync_file_range");
strcpy(sys_call_names[278], "vmsplice");
strcpy(sys_call_names[279], "move_pages");
strcpy(sys_call_names[280], "utimensat");
strcpy(sys_call_names[281], "epoll_pwait");
strcpy(sys_call_names[282], "signalfd");
strcpy(sys_call_names[283], "timerfd_create");
strcpy(sys_call_names[284], "eventfd");
strcpy(sys_call_names[285], "fallocate");
strcpy(sys_call_names[286], "timerfd_settime");
strcpy(sys_call_names[287], "timerfd_gettime");
strcpy(sys_call_names[288], "accept4");
strcpy(sys_call_names[289], "signalfd4");
strcpy(sys_call_names[290], "eventfd2");
strcpy(sys_call_names[291], "epoll_create1");
strcpy(sys_call_names[292], "dup3");
strcpy(sys_call_names[293], "pipe2");
strcpy(sys_call_names[294], "inotify_init1");
strcpy(sys_call_names[295], "preadv");
strcpy(sys_call_names[296], "pwritev");
strcpy(sys_call_names[297], "rt_tgsigqueueinfo");
strcpy(sys_call_names[298], "perf_event_open");
strcpy(sys_call_names[299], "recvmmsg");
strcpy(sys_call_names[300], "fanotify_init");
strcpy(sys_call_names[301], "fanotify_mark");
strcpy(sys_call_names[302], "prlimit64");
strcpy(sys_call_names[303], "name_to_handle_at");
strcpy(sys_call_names[304], "open_by_handle_at");
strcpy(sys_call_names[305], "clock_adjtime");
strcpy(sys_call_names[306], "syncfs");
strcpy(sys_call_names[307], "sendmmsg");
strcpy(sys_call_names[308], "setns");
strcpy(sys_call_names[309], "getcpu");
strcpy(sys_call_names[310], "process_vm_readv");
strcpy(sys_call_names[311], "process_vm_writev");
strcpy(sys_call_names[312], "kcmp");
strcpy(sys_call_names[313], "finit_module");
}
