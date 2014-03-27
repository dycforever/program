#include "common.h"
namespace dyc {

DYC_GLOBAL dyc_global;

const char* errno2str(int errno_p) {
    switch(errno_p) {
        case (EPERM): return "EPERM";
        case (ENOENT): return "ENOENT";
        case (ESRCH): return "ESRCH";
        case (EINTR): return "EINTR";
        case (EIO): return "EIO";
        case (ENXIO): return "ENXIO";
        case (E2BIG): return "E2BIG";
        case (ENOEXEC): return "ENOEXEC";
        case (EBADF): return "EBADF";
        case (ECHILD): return "ECHILD";
        // EAGAIN equals to EWOULDBLOCK
        case (EAGAIN): return "EAGAIN";
        case (ENOMEM): return "ENOMEM";
        case (EACCES): return "EACCES";
        case (EFAULT): return "EFAULT";
        case (ENOTBLK): return "ENOTBLK";
        case (EBUSY): return "EBUSY";
        case (EEXIST): return "EEXIST";
        case (EXDEV): return "EXDEV";
        case (ENODEV): return "ENODEV";
        case (ENOTDIR): return "ENOTDIR";
        case (EISDIR): return "EISDIR";
        case (EINVAL): return "EINVAL";
        case (ENFILE): return "ENFILE";
        case (EMFILE): return "EMFILE";
        case (ENOTTY): return "ENOTTY";
        case (ETXTBSY): return "ETXTBSY";
        case (EFBIG): return "EFBIG";
        case (ENOSPC): return "ENOSPC";
        case (ESPIPE): return "ESPIPE";
        case (EROFS): return "EROFS";
        case (EMLINK): return "EMLINK";
        case (EPIPE): return "EPIPE";
        case (EDOM): return "EDOM";
        case (ERANGE): return "ERANGE";
        // EDEADLK equals to EDEADLOCK
        case (EDEADLK): return "EDEADLK";
        case (ENAMETOOLONG): return "ENAMETOOLONG";
        case (ENOLCK): return "ENOLCK";
        case (ENOSYS): return "ENOSYS";
        case (ENOTEMPTY): return "ENOTEMPTY";
        case (ELOOP): return "ELOOP";
        case (ENOMSG): return "ENOMSG";
        case (EIDRM): return "EIDRM";
        case (ECHRNG): return "ECHRNG";
        case (EL2NSYNC): return "EL2NSYNC";
        case (EL3HLT): return "EL3HLT";
        case (EL3RST): return "EL3RST";
        case (ELNRNG): return "ELNRNG";
        case (EUNATCH): return "EUNATCH";
        case (ENOCSI): return "ENOCSI";
        case (EL2HLT): return "EL2HLT";
        case (EBADE): return "EBADE";
        case (EBADR): return "EBADR";
        case (EXFULL): return "EXFULL";
        case (ENOANO): return "ENOANO";
        case (EBADRQC): return "EBADRQC";
        case (EBADSLT): return "EBADSLT";
        case (EBFONT): return "EBFONT";
        case (ENOSTR): return "ENOSTR";
        case (ENODATA): return "ENODATA";
        case (ETIME): return "ETIME";
        case (ENOSR): return "ENOSR";
        case (ENONET): return "ENONET";
        case (ENOPKG): return "ENOPKG";
        case (EREMOTE): return "EREMOTE";
        case (ENOLINK): return "ENOLINK";
        case (EADV): return "EADV";
        case (ESRMNT): return "ESRMNT";
        case (ECOMM): return "ECOMM";
        case (EPROTO): return "EPROTO";
        case (EMULTIHOP): return "EMULTIHOP";
        case (EDOTDOT): return "EDOTDOT";
        case (EBADMSG): return "EBADMSG";
        case (EOVERFLOW): return "EOVERFLOW";
        case (ENOTUNIQ): return "ENOTUNIQ";
        case (EBADFD): return "EBADFD";
        case (EREMCHG): return "EREMCHG";
        case (ELIBACC): return "ELIBACC";
        case (ELIBBAD): return "ELIBBAD";
        case (ELIBSCN): return "ELIBSCN";
        case (ELIBMAX): return "ELIBMAX";
        case (ELIBEXEC): return "ELIBEXEC";
        case (EILSEQ): return "EILSEQ";
        case (ERESTART): return "ERESTART";
        case (ESTRPIPE): return "ESTRPIPE";
        case (EUSERS): return "EUSERS";
        case (ENOTSOCK): return "ENOTSOCK";
        case (EDESTADDRREQ): return "EDESTADDRREQ";
        case (EMSGSIZE): return "EMSGSIZE";
        case (EPROTOTYPE): return "EPROTOTYPE";
        case (ENOPROTOOPT): return "ENOPROTOOPT";
        case (EPROTONOSUPPORT): return "EPROTONOSUPPORT";
        case (ESOCKTNOSUPPORT): return "ESOCKTNOSUPPORT";
        case (EOPNOTSUPP): return "EOPNOTSUPP";
        case (EPFNOSUPPORT): return "EPFNOSUPPORT";
        case (EAFNOSUPPORT): return "EAFNOSUPPORT";
        case (EADDRINUSE): return "EADDRINUSE";
        case (EADDRNOTAVAIL): return "EADDRNOTAVAIL";
        case (ENETDOWN): return "ENETDOWN";
        case (ENETUNREACH): return "ENETUNREACH";
        case (ENETRESET): return "ENETRESET";
        case (ECONNABORTED): return "ECONNABORTED";
        case (ECONNRESET): return "ECONNRESET";
        case (ENOBUFS): return "ENOBUFS";
        case (EISCONN): return "EISCONN";
        case (ENOTCONN): return "ENOTCONN";
        case (ESHUTDOWN): return "ESHUTDOWN";
        case (ETOOMANYREFS): return "ETOOMANYREFS";
        case (ETIMEDOUT): return "ETIMEDOUT";
        case (ECONNREFUSED): return "ECONNREFUSED";
        case (EHOSTDOWN): return "EHOSTDOWN";
        case (EHOSTUNREACH): return "EHOSTUNREACH";
        case (EALREADY): return "EALREADY";
        case (EINPROGRESS): return "EINPROGRESS";
        case (ESTALE): return "ESTALE";
        case (EUCLEAN): return "EUCLEAN";
        case (ENOTNAM): return "ENOTNAM";
        case (ENAVAIL): return "ENAVAIL";
        case (EISNAM): return "EISNAM";
        case (EREMOTEIO): return "EREMOTEIO";
        case (EDQUOT): return "EDQUOT";
        case (ENOMEDIUM): return "ENOMEDIUM";
        case (EMEDIUMTYPE): return "EMEDIUMTYPE";
        case (ECANCELED): return "ECANCELED";
        case (ENOKEY): return "ENOKEY";
        case (EKEYEXPIRED): return "EKEYEXPIRED";
        case (EKEYREVOKED): return "EKEYREVOKED";
        case (EKEYREJECTED): return "EKEYREJECTED";
        case (EOWNERDEAD): return "EOWNERDEAD";
        case (ENOTRECOVERABLE): return "ENOTRECOVERABLE";
        default: return "unknow errno";
    };
}

const char* syscall2str(long syscallnum) {
#ifdef __x86_64__
    switch(syscallnum) {
        case(SYS__sysctl): return "SYS__sysctl";
        case(SYS_access): return "SYS_access";
        case(SYS_acct): return "SYS_acct";
        case(SYS_add_key): return "SYS_add_key";
        case(SYS_adjtimex): return "SYS_adjtimex";
        case(SYS_afs_syscall): return "SYS_afs_syscall";
        case(SYS_alarm): return "SYS_alarm";
        case(SYS_brk): return "SYS_brk";
        case(SYS_capget): return "SYS_capget";
        case(SYS_capset): return "SYS_capset";
        case(SYS_chdir): return "SYS_chdir";
        case(SYS_chmod): return "SYS_chmod";
        case(SYS_chown): return "SYS_chown";
        case(SYS_chroot): return "SYS_chroot";
        case(SYS_clock_adjtime): return "SYS_clock_adjtime";
        case(SYS_clock_getres): return "SYS_clock_getres";
        case(SYS_clock_gettime): return "SYS_clock_gettime";
        case(SYS_clock_nanosleep): return "SYS_clock_nanosleep";
        case(SYS_clock_settime): return "SYS_clock_settime";
        case(SYS_clone): return "SYS_clone";
        case(SYS_close): return "SYS_close";
        case(SYS_creat): return "SYS_creat";
        case(SYS_create_module): return "SYS_create_module";
        case(SYS_delete_module): return "SYS_delete_module";
        case(SYS_dup): return "SYS_dup";
        case(SYS_dup2): return "SYS_dup2";
        case(SYS_dup3): return "SYS_dup3";
        case(SYS_epoll_create): return "SYS_epoll_create";
        case(SYS_epoll_create1): return "SYS_epoll_create1";
        case(SYS_epoll_ctl): return "SYS_epoll_ctl";
        case(SYS_epoll_pwait): return "SYS_epoll_pwait";
        case(SYS_epoll_wait): return "SYS_epoll_wait";
        case(SYS_eventfd): return "SYS_eventfd";
        case(SYS_eventfd2): return "SYS_eventfd2";
        case(SYS_execve): return "SYS_execve";
        case(SYS_exit): return "SYS_exit";
        case(SYS_exit_group): return "SYS_exit_group";
        case(SYS_faccessat): return "SYS_faccessat";
        case(SYS_fadvise64): return "SYS_fadvise64";
        case(SYS_fallocate): return "SYS_fallocate";
        case(SYS_fanotify_init): return "SYS_fanotify_init";
        case(SYS_fanotify_mark): return "SYS_fanotify_mark";
        case(SYS_fchdir): return "SYS_fchdir";
        case(SYS_fchmod): return "SYS_fchmod";
        case(SYS_fchmodat): return "SYS_fchmodat";
        case(SYS_fchown): return "SYS_fchown";
        case(SYS_fchownat): return "SYS_fchownat";
        case(SYS_fcntl): return "SYS_fcntl";
        case(SYS_fdatasync): return "SYS_fdatasync";
        case(SYS_fgetxattr): return "SYS_fgetxattr";
        case(SYS_flistxattr): return "SYS_flistxattr";
        case(SYS_flock): return "SYS_flock";
        case(SYS_fork): return "SYS_fork";
        case(SYS_fremovexattr): return "SYS_fremovexattr";
        case(SYS_fsetxattr): return "SYS_fsetxattr";
        case(SYS_fstat): return "SYS_fstat";
        case(SYS_fstatfs): return "SYS_fstatfs";
        case(SYS_fsync): return "SYS_fsync";
        case(SYS_ftruncate): return "SYS_ftruncate";
        case(SYS_futex): return "SYS_futex";
        case(SYS_futimesat): return "SYS_futimesat";
        case(SYS_get_kernel_syms): return "SYS_get_kernel_syms";
        case(SYS_get_mempolicy): return "SYS_get_mempolicy";
        case(SYS_get_robust_list): return "SYS_get_robust_list";
        case(SYS_get_thread_area): return "SYS_get_thread_area";
        case(SYS_getcpu): return "SYS_getcpu";
        case(SYS_getcwd): return "SYS_getcwd";
        case(SYS_getdents): return "SYS_getdents";
        case(SYS_getdents64): return "SYS_getdents64";
        case(SYS_getegid): return "SYS_getegid";
        case(SYS_geteuid): return "SYS_geteuid";
        case(SYS_getgid): return "SYS_getgid";
        case(SYS_getgroups): return "SYS_getgroups";
        case(SYS_getitimer): return "SYS_getitimer";
        case(SYS_getpgid): return "SYS_getpgid";
        case(SYS_getpgrp): return "SYS_getpgrp";
        case(SYS_getpid): return "SYS_getpid";
        case(SYS_getpmsg): return "SYS_getpmsg";
        case(SYS_getppid): return "SYS_getppid";
        case(SYS_getpriority): return "SYS_getpriority";
        case(SYS_getresgid): return "SYS_getresgid";
        case(SYS_getresuid): return "SYS_getresuid";
        case(SYS_getrlimit): return "SYS_getrlimit";
        case(SYS_getrusage): return "SYS_getrusage";
        case(SYS_getsid): return "SYS_getsid";
        case(SYS_gettid): return "SYS_gettid";
        case(SYS_gettimeofday): return "SYS_gettimeofday";
        case(SYS_getuid): return "SYS_getuid";
        case(SYS_getxattr): return "SYS_getxattr";
        case(SYS_init_module): return "SYS_init_module";
        case(SYS_inotify_add_watch): return "SYS_inotify_add_watch";
        case(SYS_inotify_init): return "SYS_inotify_init";
        case(SYS_inotify_init1): return "SYS_inotify_init1";
        case(SYS_inotify_rm_watch): return "SYS_inotify_rm_watch";
        case(SYS_io_cancel): return "SYS_io_cancel";
        case(SYS_io_destroy): return "SYS_io_destroy";
        case(SYS_io_getevents): return "SYS_io_getevents";
        case(SYS_io_setup): return "SYS_io_setup";
        case(SYS_io_submit): return "SYS_io_submit";
        case(SYS_ioctl): return "SYS_ioctl";
        case(SYS_ioperm): return "SYS_ioperm";
        case(SYS_iopl): return "SYS_iopl";
        case(SYS_ioprio_get): return "SYS_ioprio_get";
        case(SYS_ioprio_set): return "SYS_ioprio_set";
        case(SYS_kexec_load): return "SYS_kexec_load";
        case(SYS_keyctl): return "SYS_keyctl";
        case(SYS_kill): return "SYS_kill";
        case(SYS_lchown): return "SYS_lchown";
        case(SYS_lgetxattr): return "SYS_lgetxattr";
        case(SYS_link): return "SYS_link";
        case(SYS_linkat): return "SYS_linkat";
        case(SYS_listxattr): return "SYS_listxattr";
        case(SYS_llistxattr): return "SYS_llistxattr";
        case(SYS_lookup_dcookie): return "SYS_lookup_dcookie";
        case(SYS_lremovexattr): return "SYS_lremovexattr";
        case(SYS_lseek): return "SYS_lseek";
        case(SYS_lsetxattr): return "SYS_lsetxattr";
        case(SYS_lstat): return "SYS_lstat";
        case(SYS_madvise): return "SYS_madvise";
        case(SYS_mbind): return "SYS_mbind";
        case(SYS_migrate_pages): return "SYS_migrate_pages";
        case(SYS_mincore): return "SYS_mincore";
        case(SYS_mkdir): return "SYS_mkdir";
        case(SYS_mkdirat): return "SYS_mkdirat";
        case(SYS_mknod): return "SYS_mknod";
        case(SYS_mknodat): return "SYS_mknodat";
        case(SYS_mlock): return "SYS_mlock";
        case(SYS_mlockall): return "SYS_mlockall";
        case(SYS_mmap): return "SYS_mmap";
        case(SYS_modify_ldt): return "SYS_modify_ldt";
        case(SYS_mount): return "SYS_mount";
        case(SYS_move_pages): return "SYS_move_pages";
        case(SYS_mprotect): return "SYS_mprotect";
        case(SYS_mq_getsetattr): return "SYS_mq_getsetattr";
        case(SYS_mq_notify): return "SYS_mq_notify";
        case(SYS_mq_open): return "SYS_mq_open";
        case(SYS_mq_timedreceive): return "SYS_mq_timedreceive";
        case(SYS_mq_timedsend): return "SYS_mq_timedsend";
        case(SYS_mq_unlink): return "SYS_mq_unlink";
        case(SYS_mremap): return "SYS_mremap";
        case(SYS_msync): return "SYS_msync";
        case(SYS_munlock): return "SYS_munlock";
        case(SYS_munlockall): return "SYS_munlockall";
        case(SYS_munmap): return "SYS_munmap";
        case(SYS_name_to_handle_at): return "SYS_name_to_handle_at";
        case(SYS_nanosleep): return "SYS_nanosleep";
        case(SYS_nfsservctl): return "SYS_nfsservctl";
        case(SYS_open): return "SYS_open";
        case(SYS_open_by_handle_at): return "SYS_open_by_handle_at";
        case(SYS_openat): return "SYS_openat";
        case(SYS_pause): return "SYS_pause";
        case(SYS_perf_event_open): return "SYS_perf_event_open";
        case(SYS_personality): return "SYS_personality";
        case(SYS_pipe): return "SYS_pipe";
        case(SYS_pipe2): return "SYS_pipe2";
        case(SYS_pivot_root): return "SYS_pivot_root";
        case(SYS_poll): return "SYS_poll";
        case(SYS_ppoll): return "SYS_ppoll";
        case(SYS_prctl): return "SYS_prctl";
        case(SYS_pread64): return "SYS_pread64";
        case(SYS_preadv): return "SYS_preadv";
        case(SYS_prlimit64): return "SYS_prlimit64";
        case(SYS_process_vm_readv): return "SYS_process_vm_readv";
        case(SYS_process_vm_writev): return "SYS_process_vm_writev";
        case(SYS_pselect6): return "SYS_pselect6";
        case(SYS_ptrace): return "SYS_ptrace";
        case(SYS_putpmsg): return "SYS_putpmsg";
        case(SYS_pwrite64): return "SYS_pwrite64";
        case(SYS_pwritev): return "SYS_pwritev";
        case(SYS_query_module): return "SYS_query_module";
        case(SYS_quotactl): return "SYS_quotactl";
        case(SYS_read): return "SYS_read";
        case(SYS_readahead): return "SYS_readahead";
        case(SYS_readlink): return "SYS_readlink";
        case(SYS_readlinkat): return "SYS_readlinkat";
        case(SYS_readv): return "SYS_readv";
        case(SYS_reboot): return "SYS_reboot";
        case(SYS_recvmmsg): return "SYS_recvmmsg";
        case(SYS_remap_file_pages): return "SYS_remap_file_pages";
        case(SYS_removexattr): return "SYS_removexattr";
        case(SYS_rename): return "SYS_rename";
        case(SYS_renameat): return "SYS_renameat";
        case(SYS_request_key): return "SYS_request_key";
        case(SYS_restart_syscall): return "SYS_restart_syscall";
        case(SYS_rmdir): return "SYS_rmdir";
        case(SYS_rt_sigaction): return "SYS_rt_sigaction";
        case(SYS_rt_sigpending): return "SYS_rt_sigpending";
        case(SYS_rt_sigprocmask): return "SYS_rt_sigprocmask";
        case(SYS_rt_sigqueueinfo): return "SYS_rt_sigqueueinfo";
        case(SYS_rt_sigreturn): return "SYS_rt_sigreturn";
        case(SYS_rt_sigsuspend): return "SYS_rt_sigsuspend";
        case(SYS_rt_sigtimedwait): return "SYS_rt_sigtimedwait";
        case(SYS_rt_tgsigqueueinfo): return "SYS_rt_tgsigqueueinfo";
        case(SYS_sched_get_priority_max): return "SYS_sched_get_priority_max";
        case(SYS_sched_get_priority_min): return "SYS_sched_get_priority_min";
        case(SYS_sched_getaffinity): return "SYS_sched_getaffinity";
        case(SYS_sched_getparam): return "SYS_sched_getparam";
        case(SYS_sched_getscheduler): return "SYS_sched_getscheduler";
        case(SYS_sched_rr_get_interval): return "SYS_sched_rr_get_interval";
        case(SYS_sched_setaffinity): return "SYS_sched_setaffinity";
        case(SYS_sched_setparam): return "SYS_sched_setparam";
        case(SYS_sched_setscheduler): return "SYS_sched_setscheduler";
        case(SYS_sched_yield): return "SYS_sched_yield";
        case(SYS_select): return "SYS_select";
        case(SYS_sendfile): return "SYS_sendfile";
        case(SYS_sendmmsg): return "SYS_sendmmsg";
        case(SYS_set_mempolicy): return "SYS_set_mempolicy";
        case(SYS_set_robust_list): return "SYS_set_robust_list";
        case(SYS_set_thread_area): return "SYS_set_thread_area";
        case(SYS_set_tid_address): return "SYS_set_tid_address";
        case(SYS_setdomainname): return "SYS_setdomainname";
        case(SYS_setfsgid): return "SYS_setfsgid";
        case(SYS_setfsuid): return "SYS_setfsuid";
        case(SYS_setgid): return "SYS_setgid";
        case(SYS_setgroups): return "SYS_setgroups";
        case(SYS_sethostname): return "SYS_sethostname";
        case(SYS_setitimer): return "SYS_setitimer";
        case(SYS_setns): return "SYS_setns";
        case(SYS_setpgid): return "SYS_setpgid";
        case(SYS_setpriority): return "SYS_setpriority";
        case(SYS_setregid): return "SYS_setregid";
        case(SYS_setresgid): return "SYS_setresgid";
        case(SYS_setresuid): return "SYS_setresuid";
        case(SYS_setreuid): return "SYS_setreuid";
        case(SYS_setrlimit): return "SYS_setrlimit";
        case(SYS_setsid): return "SYS_setsid";
        case(SYS_settimeofday): return "SYS_settimeofday";
        case(SYS_setuid): return "SYS_setuid";
        case(SYS_setxattr): return "SYS_setxattr";
        case(SYS_sigaltstack): return "SYS_sigaltstack";
        case(SYS_signalfd): return "SYS_signalfd";
        case(SYS_signalfd4): return "SYS_signalfd4";
        case(SYS_splice): return "SYS_splice";
        case(SYS_stat): return "SYS_stat";
        case(SYS_statfs): return "SYS_statfs";
        case(SYS_swapoff): return "SYS_swapoff";
        case(SYS_swapon): return "SYS_swapon";
        case(SYS_symlink): return "SYS_symlink";
        case(SYS_symlinkat): return "SYS_symlinkat";
        case(SYS_sync): return "SYS_sync";
        case(SYS_sync_file_range): return "SYS_sync_file_range";
        case(SYS_syncfs): return "SYS_syncfs";
        case(SYS_sysfs): return "SYS_sysfs";
        case(SYS_sysinfo): return "SYS_sysinfo";
        case(SYS_syslog): return "SYS_syslog";
        case(SYS_tee): return "SYS_tee";
        case(SYS_tgkill): return "SYS_tgkill";
        case(SYS_time): return "SYS_time";
        case(SYS_timer_create): return "SYS_timer_create";
        case(SYS_timer_delete): return "SYS_timer_delete";
        case(SYS_timer_getoverrun): return "SYS_timer_getoverrun";
        case(SYS_timer_gettime): return "SYS_timer_gettime";
        case(SYS_timer_settime): return "SYS_timer_settime";
        case(SYS_timerfd_create): return "SYS_timerfd_create";
        case(SYS_timerfd_gettime): return "SYS_timerfd_gettime";
        case(SYS_timerfd_settime): return "SYS_timerfd_settime";
        case(SYS_times): return "SYS_times";
        case(SYS_tkill): return "SYS_tkill";
        case(SYS_truncate): return "SYS_truncate";
        case(SYS_umask): return "SYS_umask";
        case(SYS_umount2): return "SYS_umount2";
        case(SYS_uname): return "SYS_uname";
        case(SYS_unlink): return "SYS_unlink";
        case(SYS_unlinkat): return "SYS_unlinkat";
        case(SYS_unshare): return "SYS_unshare";
        case(SYS_uselib): return "SYS_uselib";
        case(SYS_ustat): return "SYS_ustat";
        case(SYS_utime): return "SYS_utime";
        case(SYS_utimensat): return "SYS_utimensat";
        case(SYS_utimes): return "SYS_utimes";
        case(SYS_vfork): return "SYS_vfork";
        case(SYS_vhangup): return "SYS_vhangup";
        case(SYS_vmsplice): return "SYS_vmsplice";
        case(SYS_vserver): return "SYS_vserver";
        case(SYS_wait4): return "SYS_wait4";
        case(SYS_waitid): return "SYS_waitid";
        case(SYS_write): return "SYS_write";
        case(SYS_writev): return "SYS_writev";
    }

#else

    switch(syscallnum) {
        case(SYS__sysctl): return "SYS__sysctl";
        case(SYS_accept): return "SYS_accept";
        case(SYS_accept4): return "SYS_accept4";
        case(SYS_access): return "SYS_access";
        case(SYS_acct): return "SYS_acct";
        case(SYS_add_key): return "SYS_add_key";
        case(SYS_adjtimex): return "SYS_adjtimex";
        case(SYS_afs_syscall): return "SYS_afs_syscall";
        case(SYS_alarm): return "SYS_alarm";
        case(SYS_arch_prctl): return "SYS_arch_prctl";
        case(SYS_bind): return "SYS_bind";
        case(SYS_brk): return "SYS_brk";
        case(SYS_capget): return "SYS_capget";
        case(SYS_capset): return "SYS_capset";
        case(SYS_chdir): return "SYS_chdir";
        case(SYS_chmod): return "SYS_chmod";
        case(SYS_chown): return "SYS_chown";
        case(SYS_chroot): return "SYS_chroot";
        case(SYS_clock_adjtime): return "SYS_clock_adjtime";
        case(SYS_clock_getres): return "SYS_clock_getres";
        case(SYS_clock_gettime): return "SYS_clock_gettime";
        case(SYS_clock_nanosleep): return "SYS_clock_nanosleep";
        case(SYS_clock_settime): return "SYS_clock_settime";
        case(SYS_clone): return "SYS_clone";
        case(SYS_close): return "SYS_close";
        case(SYS_connect): return "SYS_connect";
        case(SYS_creat): return "SYS_creat";
        case(SYS_create_module): return "SYS_create_module";
        case(SYS_delete_module): return "SYS_delete_module";
        case(SYS_dup): return "SYS_dup";
        case(SYS_dup2): return "SYS_dup2";
        case(SYS_dup3): return "SYS_dup3";
        case(SYS_epoll_create): return "SYS_epoll_create";
        case(SYS_epoll_create1): return "SYS_epoll_create1";
        case(SYS_epoll_ctl): return "SYS_epoll_ctl";
        case(SYS_epoll_ctl_old): return "SYS_epoll_ctl_old";
        case(SYS_epoll_pwait): return "SYS_epoll_pwait";
        case(SYS_epoll_wait): return "SYS_epoll_wait";
        case(SYS_epoll_wait_old): return "SYS_epoll_wait_old";
        case(SYS_eventfd): return "SYS_eventfd";
        case(SYS_eventfd2): return "SYS_eventfd2";
        case(SYS_execve): return "SYS_execve";
        case(SYS_exit): return "SYS_exit";
        case(SYS_exit_group): return "SYS_exit_group";
        case(SYS_faccessat): return "SYS_faccessat";
        case(SYS_fadvise64): return "SYS_fadvise64";
        case(SYS_fallocate): return "SYS_fallocate";
        case(SYS_fanotify_init): return "SYS_fanotify_init";
        case(SYS_fanotify_mark): return "SYS_fanotify_mark";
        case(SYS_fchdir): return "SYS_fchdir";
        case(SYS_fchmod): return "SYS_fchmod";
        case(SYS_fchmodat): return "SYS_fchmodat";
        case(SYS_fchown): return "SYS_fchown";
        case(SYS_fchownat): return "SYS_fchownat";
        case(SYS_fcntl): return "SYS_fcntl";
        case(SYS_fdatasync): return "SYS_fdatasync";
        case(SYS_fgetxattr): return "SYS_fgetxattr";
        case(SYS_flistxattr): return "SYS_flistxattr";
        case(SYS_flock): return "SYS_flock";
        case(SYS_fork): return "SYS_fork";
        case(SYS_fremovexattr): return "SYS_fremovexattr";
        case(SYS_fsetxattr): return "SYS_fsetxattr";
        case(SYS_fstat): return "SYS_fstat";
        case(SYS_fstatfs): return "SYS_fstatfs";
        case(SYS_fsync): return "SYS_fsync";
        case(SYS_ftruncate): return "SYS_ftruncate";
        case(SYS_futex): return "SYS_futex";
        case(SYS_futimesat): return "SYS_futimesat";
        case(SYS_get_kernel_syms): return "SYS_get_kernel_syms";
        case(SYS_get_mempolicy): return "SYS_get_mempolicy";
        case(SYS_get_robust_list): return "SYS_get_robust_list";
        case(SYS_get_thread_area): return "SYS_get_thread_area";
        case(SYS_getcpu): return "SYS_getcpu";
        case(SYS_getcwd): return "SYS_getcwd";
        case(SYS_getdents): return "SYS_getdents";
        case(SYS_getdents64): return "SYS_getdents64";
        case(SYS_getegid): return "SYS_getegid";
        case(SYS_geteuid): return "SYS_geteuid";
        case(SYS_getgid): return "SYS_getgid";
        case(SYS_getgroups): return "SYS_getgroups";
        case(SYS_getitimer): return "SYS_getitimer";
        case(SYS_getpeername): return "SYS_getpeername";
        case(SYS_getpgid): return "SYS_getpgid";
        case(SYS_getpgrp): return "SYS_getpgrp";
        case(SYS_getpid): return "SYS_getpid";
        case(SYS_getpmsg): return "SYS_getpmsg";
        case(SYS_getppid): return "SYS_getppid";
        case(SYS_getpriority): return "SYS_getpriority";
        case(SYS_getresgid): return "SYS_getresgid";
        case(SYS_getresuid): return "SYS_getresuid";
        case(SYS_getrlimit): return "SYS_getrlimit";
        case(SYS_getrusage): return "SYS_getrusage";
        case(SYS_getsid): return "SYS_getsid";
        case(SYS_getsockname): return "SYS_getsockname";
        case(SYS_getsockopt): return "SYS_getsockopt";
        case(SYS_gettid): return "SYS_gettid";
        case(SYS_gettimeofday): return "SYS_gettimeofday";
        case(SYS_getuid): return "SYS_getuid";
        case(SYS_getxattr): return "SYS_getxattr";
        case(SYS_init_module): return "SYS_init_module";
        case(SYS_inotify_add_watch): return "SYS_inotify_add_watch";
        case(SYS_inotify_init): return "SYS_inotify_init";
        case(SYS_inotify_init1): return "SYS_inotify_init1";
        case(SYS_inotify_rm_watch): return "SYS_inotify_rm_watch";
        case(SYS_io_cancel): return "SYS_io_cancel";
        case(SYS_io_destroy): return "SYS_io_destroy";
        case(SYS_io_getevents): return "SYS_io_getevents";
        case(SYS_io_setup): return "SYS_io_setup";
        case(SYS_io_submit): return "SYS_io_submit";
        case(SYS_ioctl): return "SYS_ioctl";
        case(SYS_ioperm): return "SYS_ioperm";
        case(SYS_iopl): return "SYS_iopl";
        case(SYS_ioprio_get): return "SYS_ioprio_get";
        case(SYS_ioprio_set): return "SYS_ioprio_set";
        case(SYS_kexec_load): return "SYS_kexec_load";
        case(SYS_keyctl): return "SYS_keyctl";
        case(SYS_kill): return "SYS_kill";
        case(SYS_lchown): return "SYS_lchown";
        case(SYS_lgetxattr): return "SYS_lgetxattr";
        case(SYS_link): return "SYS_link";
        case(SYS_linkat): return "SYS_linkat";
        case(SYS_listen): return "SYS_listen";
        case(SYS_listxattr): return "SYS_listxattr";
        case(SYS_llistxattr): return "SYS_llistxattr";
        case(SYS_lookup_dcookie): return "SYS_lookup_dcookie";
        case(SYS_lremovexattr): return "SYS_lremovexattr";
        case(SYS_lseek): return "SYS_lseek";
        case(SYS_lsetxattr): return "SYS_lsetxattr";
        case(SYS_lstat): return "SYS_lstat";
        case(SYS_madvise): return "SYS_madvise";
        case(SYS_mbind): return "SYS_mbind";
        case(SYS_migrate_pages): return "SYS_migrate_pages";
        case(SYS_mincore): return "SYS_mincore";
        case(SYS_mkdir): return "SYS_mkdir";
        case(SYS_mkdirat): return "SYS_mkdirat";
        case(SYS_mknod): return "SYS_mknod";
        case(SYS_mknodat): return "SYS_mknodat";
        case(SYS_mlock): return "SYS_mlock";
        case(SYS_mlockall): return "SYS_mlockall";
        case(SYS_mmap): return "SYS_mmap";
        case(SYS_modify_ldt): return "SYS_modify_ldt";
        case(SYS_mount): return "SYS_mount";
        case(SYS_move_pages): return "SYS_move_pages";
        case(SYS_mprotect): return "SYS_mprotect";
        case(SYS_mq_getsetattr): return "SYS_mq_getsetattr";
        case(SYS_mq_notify): return "SYS_mq_notify";
        case(SYS_mq_open): return "SYS_mq_open";
        case(SYS_mq_timedreceive): return "SYS_mq_timedreceive";
        case(SYS_mq_timedsend): return "SYS_mq_timedsend";
        case(SYS_mq_unlink): return "SYS_mq_unlink";
        case(SYS_mremap): return "SYS_mremap";
        case(SYS_msgctl): return "SYS_msgctl";
        case(SYS_msgget): return "SYS_msgget";
        case(SYS_msgrcv): return "SYS_msgrcv";
        case(SYS_msgsnd): return "SYS_msgsnd";
        case(SYS_msync): return "SYS_msync";
        case(SYS_munlock): return "SYS_munlock";
        case(SYS_munlockall): return "SYS_munlockall";
        case(SYS_munmap): return "SYS_munmap";
        case(SYS_name_to_handle_at): return "SYS_name_to_handle_at";
        case(SYS_nanosleep): return "SYS_nanosleep";
        case(SYS_newfstatat): return "SYS_newfstatat";
        case(SYS_nfsservctl): return "SYS_nfsservctl";
        case(SYS_open): return "SYS_open";
        case(SYS_open_by_handle_at): return "SYS_open_by_handle_at";
        case(SYS_openat): return "SYS_openat";
        case(SYS_pause): return "SYS_pause";
        case(SYS_perf_event_open): return "SYS_perf_event_open";
        case(SYS_personality): return "SYS_personality";
        case(SYS_pipe): return "SYS_pipe";
        case(SYS_pipe2): return "SYS_pipe2";
        case(SYS_pivot_root): return "SYS_pivot_root";
        case(SYS_poll): return "SYS_poll";
        case(SYS_ppoll): return "SYS_ppoll";
        case(SYS_prctl): return "SYS_prctl";
        case(SYS_pread64): return "SYS_pread64";
        case(SYS_preadv): return "SYS_preadv";
        case(SYS_prlimit64): return "SYS_prlimit64";
        case(SYS_process_vm_readv): return "SYS_process_vm_readv";
        case(SYS_process_vm_writev): return "SYS_process_vm_writev";
        case(SYS_pselect6): return "SYS_pselect6";
        case(SYS_ptrace): return "SYS_ptrace";
        case(SYS_putpmsg): return "SYS_putpmsg";
        case(SYS_pwrite64): return "SYS_pwrite64";
        case(SYS_pwritev): return "SYS_pwritev";
        case(SYS_query_module): return "SYS_query_module";
        case(SYS_quotactl): return "SYS_quotactl";
        case(SYS_read): return "SYS_read";
        case(SYS_readahead): return "SYS_readahead";
        case(SYS_readlink): return "SYS_readlink";
        case(SYS_readlinkat): return "SYS_readlinkat";
        case(SYS_readv): return "SYS_readv";
        case(SYS_reboot): return "SYS_reboot";
        case(SYS_recvfrom): return "SYS_recvfrom";
        case(SYS_recvmmsg): return "SYS_recvmmsg";
        case(SYS_recvmsg): return "SYS_recvmsg";
        case(SYS_remap_file_pages): return "SYS_remap_file_pages";
        case(SYS_removexattr): return "SYS_removexattr";
        case(SYS_rename): return "SYS_rename";
        case(SYS_renameat): return "SYS_renameat";
        case(SYS_request_key): return "SYS_request_key";
        case(SYS_restart_syscall): return "SYS_restart_syscall";
        case(SYS_rmdir): return "SYS_rmdir";
        case(SYS_rt_sigaction): return "SYS_rt_sigaction";
        case(SYS_rt_sigpending): return "SYS_rt_sigpending";
        case(SYS_rt_sigprocmask): return "SYS_rt_sigprocmask";
        case(SYS_rt_sigqueueinfo): return "SYS_rt_sigqueueinfo";
        case(SYS_rt_sigreturn): return "SYS_rt_sigreturn";
        case(SYS_rt_sigsuspend): return "SYS_rt_sigsuspend";
        case(SYS_rt_sigtimedwait): return "SYS_rt_sigtimedwait";
        case(SYS_rt_tgsigqueueinfo): return "SYS_rt_tgsigqueueinfo";
        case(SYS_sched_get_priority_max): return "SYS_sched_get_priority_max";
        case(SYS_sched_get_priority_min): return "SYS_sched_get_priority_min";
        case(SYS_sched_getaffinity): return "SYS_sched_getaffinity";
        case(SYS_sched_getparam): return "SYS_sched_getparam";
        case(SYS_sched_getscheduler): return "SYS_sched_getscheduler";
        case(SYS_sched_rr_get_interval): return "SYS_sched_rr_get_interval";
        case(SYS_sched_setaffinity): return "SYS_sched_setaffinity";
        case(SYS_sched_setparam): return "SYS_sched_setparam";
        case(SYS_sched_setscheduler): return "SYS_sched_setscheduler";
        case(SYS_sched_yield): return "SYS_sched_yield";
        case(SYS_security): return "SYS_security";
        case(SYS_select): return "SYS_select";
        case(SYS_semctl): return "SYS_semctl";
        case(SYS_semget): return "SYS_semget";
        case(SYS_semop): return "SYS_semop";
        case(SYS_semtimedop): return "SYS_semtimedop";
        case(SYS_sendfile): return "SYS_sendfile";
        case(SYS_sendmmsg): return "SYS_sendmmsg";
        case(SYS_sendmsg): return "SYS_sendmsg";
        case(SYS_sendto): return "SYS_sendto";
        case(SYS_set_mempolicy): return "SYS_set_mempolicy";
        case(SYS_set_robust_list): return "SYS_set_robust_list";
        case(SYS_set_thread_area): return "SYS_set_thread_area";
        case(SYS_set_tid_address): return "SYS_set_tid_address";
        case(SYS_setdomainname): return "SYS_setdomainname";
        case(SYS_setfsgid): return "SYS_setfsgid";
        case(SYS_setfsuid): return "SYS_setfsuid";
        case(SYS_setgid): return "SYS_setgid";
        case(SYS_setgroups): return "SYS_setgroups";
        case(SYS_sethostname): return "SYS_sethostname";
        case(SYS_setitimer): return "SYS_setitimer";
        case(SYS_setns): return "SYS_setns";
        case(SYS_setpgid): return "SYS_setpgid";
        case(SYS_setpriority): return "SYS_setpriority";
        case(SYS_setregid): return "SYS_setregid";
        case(SYS_setresgid): return "SYS_setresgid";
        case(SYS_setresuid): return "SYS_setresuid";
        case(SYS_setreuid): return "SYS_setreuid";
        case(SYS_setrlimit): return "SYS_setrlimit";
        case(SYS_setsid): return "SYS_setsid";
        case(SYS_setsockopt): return "SYS_setsockopt";
        case(SYS_settimeofday): return "SYS_settimeofday";
        case(SYS_setuid): return "SYS_setuid";
        case(SYS_setxattr): return "SYS_setxattr";
        case(SYS_shmat): return "SYS_shmat";
        case(SYS_shmctl): return "SYS_shmctl";
        case(SYS_shmdt): return "SYS_shmdt";
        case(SYS_shmget): return "SYS_shmget";
        case(SYS_shutdown): return "SYS_shutdown";
        case(SYS_sigaltstack): return "SYS_sigaltstack";
        case(SYS_signalfd): return "SYS_signalfd";
        case(SYS_signalfd4): return "SYS_signalfd4";
        case(SYS_socket): return "SYS_socket";
        case(SYS_socketpair): return "SYS_socketpair";
        case(SYS_splice): return "SYS_splice";
        case(SYS_stat): return "SYS_stat";
        case(SYS_statfs): return "SYS_statfs";
        case(SYS_swapoff): return "SYS_swapoff";
        case(SYS_swapon): return "SYS_swapon";
        case(SYS_symlink): return "SYS_symlink";
        case(SYS_symlinkat): return "SYS_symlinkat";
        case(SYS_sync): return "SYS_sync";
        case(SYS_sync_file_range): return "SYS_sync_file_range";
        case(SYS_syncfs): return "SYS_syncfs";
        case(SYS_sysfs): return "SYS_sysfs";
        case(SYS_sysinfo): return "SYS_sysinfo";
        case(SYS_syslog): return "SYS_syslog";
        case(SYS_tee): return "SYS_tee";
        case(SYS_tgkill): return "SYS_tgkill";
        case(SYS_time): return "SYS_time";
        case(SYS_timer_create): return "SYS_timer_create";
        case(SYS_timer_delete): return "SYS_timer_delete";
        case(SYS_timer_getoverrun): return "SYS_timer_getoverrun";
        case(SYS_timer_gettime): return "SYS_timer_gettime";
        case(SYS_timer_settime): return "SYS_timer_settime";
        case(SYS_timerfd_create): return "SYS_timerfd_create";
        case(SYS_timerfd_gettime): return "SYS_timerfd_gettime";
        case(SYS_timerfd_settime): return "SYS_timerfd_settime";
        case(SYS_times): return "SYS_times";
        case(SYS_tkill): return "SYS_tkill";
        case(SYS_truncate): return "SYS_truncate";
        case(SYS_tuxcall): return "SYS_tuxcall";
        case(SYS_umask): return "SYS_umask";
        case(SYS_umount2): return "SYS_umount2";
        case(SYS_uname): return "SYS_uname";
        case(SYS_unlink): return "SYS_unlink";
        case(SYS_unlinkat): return "SYS_unlinkat";
        case(SYS_unshare): return "SYS_unshare";
        case(SYS_uselib): return "SYS_uselib";
        case(SYS_ustat): return "SYS_ustat";
        case(SYS_utime): return "SYS_utime";
        case(SYS_utimensat): return "SYS_utimensat";
        case(SYS_utimes): return "SYS_utimes";
        case(SYS_vfork): return "SYS_vfork";
        case(SYS_vhangup): return "SYS_vhangup";
        case(SYS_vmsplice): return "SYS_vmsplice";
        case(SYS_vserver): return "SYS_vserver";
        case(SYS_wait4): return "SYS_wait4";
        case(SYS_waitid): return "SYS_waitid";
        case(SYS_write): return "SYS_write";
        case(SYS_writev): return "SYS_writev";
    }

#endif

}

AllocMap* dycMemAllocMap;

void addTrack(void* addr, unsigned long asize, const char *fname, long lnum) 
{ 
    ALLOC_INFO *info = new ALLOC_INFO();
    info->address = addr;
    strncpy(info->file, fname, 1024);
    info->line = lnum;
    info->size = asize;
    if (!dycMemAllocMap)
    {
        dycMemAllocMap = new AllocMap;
    }
    dycMemAllocMap->insert(std::make_pair(addr,info));
}

bool RemoveTrack(void* addr)
{
    if(!dycMemAllocMap || 0 == dycMemAllocMap->size())
    {
        return true;
    }
    AllocMap::iterator iter = dycMemAllocMap->find(addr);
    if (iter != dycMemAllocMap->end())
    {
        ALLOC_INFO* info = iter->second;
        delete info;
        dycMemAllocMap->erase(iter);
        return true;
    }
    return false;
}

void dumpUnfreed()
{
    AllocMap::iterator iter;
    ALLOC_INFO* info;
    unsigned long totalSize = 0;
    if(!dycMemAllocMap || 0 == dycMemAllocMap->size())
    {
        return;
    }

    for(iter = dycMemAllocMap->begin(); iter != dycMemAllocMap->end(); iter++)
    {
        printf("%-50s: LINE %lu, ADDRESS 0x%p size %lu unfreed\n", iter->second->file, iter->second->line
                , iter->second->address, iter->second->size);
        totalSize += iter->second->size;
        info = iter->second;
        delete info;
    }
//    printf(" ============== calling map ==========\n");
    delete dycMemAllocMap;
    printf("----------------------------------------------------------- \n");
    printf("Total Unfreed: %lu bytes \n", totalSize);
}

};
