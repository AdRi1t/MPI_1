################################################################
# date                    : 2023-05-17
# time                    : 11:28:55
# jobname                 : MPI_PMV
# jobid                   : 2120473
# subhost                 : login2
# runhost                 : inti6024
# queue                   : rome
# user                    : tabernera
# group                   : ocre
# time limit              : 180 s
# memory limit            : 1875 MB
# core limit              : 2
# system                  : Linux inti6024 4.18.0-305.88.1.el8_4.x86_64 #1 SMP Thu Apr 6 10:22:46 EDT 2023 x86_64 x86_64 x86_64 GNU/Linux
################################################################

+ SCRIPT_PID=125654
+ set +x
+ /bin/bash -x /ccc/scratch/cont001/ocre/tabernera/.SPOOL/batch/scripts/script.2120473
+ unset _mlshdbg
+ '[' 1 = 1 ']'
+ case "$-" in
+ set +x
+ unset _mlshdbg
+ set -x
+ cd /ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1
+ ccc_mprun ./pmv_mpi -f mm/fidapm37.mtx -c
+ ccc_msub MPI_job4.sh
+ exit 0

################################################################
# date                     : 2023-05-17
# time                     : 11:29:14
# time limit               : 180 s
# time used                : 21 s
# cpus usage (avg)         : 61.90% 
################################################################

SLURM General Summary
--------------------
JobId=2120473 JobName=MPI_PMV
   UserId=tabernera(4224) GroupId=ocre(3000) MCS_label=cont001
   Priority=383451 Nice=0 Account=ocre@cpu QOS=normal
   JobState=RUNNING Reason=None Dependency=(null)
   Requeue=1 Restarts=0 BatchFlag=1 Reboot=0 ExitCode=0:0
   DerivedExitCode=0:0
   RunTime=00:00:21 TimeLimit=00:03:00 TimeMin=N/A
   SubmitTime=2023-05-17T11:28:53 EligibleTime=2023-05-17T11:28:53
   AccrueTime=2023-05-17T11:28:53
   StartTime=2023-05-17T11:28:53 EndTime=2023-05-17T11:31:53 Deadline=N/A
   SuspendTime=None SecsPreSuspend=0 LastSchedEval=2023-05-17T11:28:53 Scheduler=Main
   Partition=rome AllocNode:Sid=login2:310644
   ReqNodeList=(null) ExcNodeList=(null)
   NodeList=inti6024
   BatchHost=inti6024
   NumNodes=1 NumCPUs=2 NumTasks=2 CPUs/Task=1 ReqB:S:C:T=0:0:*:*
   TRES=cpu=2,mem=3750M,node=1,billing=2
   Socks/Node=* NtasksPerN:B:S:C=0:0:*:1 CoreSpec=*
   JOB_GRES=(null)
     Nodes=inti6024 CPU_IDs=252-255 Mem=3750 GRES=
   MinCPUsNode=1 MinMemoryCPU=1875M MinTmpDiskNode=0
   Features=(null) DelayBoot=00:00:00
   OverSubscribe=OK Contiguous=0 Licenses=fs_scratch,fs_work Network=(null)
   Command=/tmp/MPI_job2.sh_wAv9e0
   WorkDir=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1
   StdErr=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1/sortie_2.e
   StdIn=/dev/null
   StdOut=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1/sortie_2.o
   Power=
   


SLURM Memory Summary
--------------------
JobID                 JobName     MaxRSS MaxRSSTask       MaxRSSNode     AveRSS 
------------ ---------------- ---------- ---------- ---------------- ---------- 
2120473               MPI_PMV                                                   
2120473.bat+            batch                                                   
2120473.ext+           extern                                                   
2120473.0             pmv_mpi     33260K          0         inti6024     22948K 

SLURM Accounting Summary
------------------------
         JobName          Account      NCPUS   NNodes   NTasks    Elapsed ExitCode      State 
---------------- ---------------- ---------- -------- -------- ---------- -------- ---------- 
         MPI_PMV         ocre@cpu          2        1            00:00:21      0:0    ENDING
           batch         ocre@cpu          2        1        1   00:00:21      0:0    ENDING
          extern         ocre@cpu          2        1        1   00:00:21      0:0    ENDING
         pmv_mpi         ocre@cpu          2        1        2   00:00:13      0:0  COMPLETED 

SLURM Energy report
-------------------
         JobName ReqCPUFreq AveCPUFreq  ConsumedEnergy
---------------- ---------- ----------  --------------
           batch          0          0        0.00 kWh
          extern          0          0        0.00 kWh
         pmv_mpi    Unknown   2892.95M        0.00 kWh
                                        --------------
                                Total:        0.00 kWh

Wed May 17 11:29:15 CEST 2023 : suppression MSUB_TMPDIR
