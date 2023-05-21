################################################################
# date                    : 2023-05-17
# time                    : 11:19:20
# jobname                 : MPI_PMV
# jobid                   : 2120436
# subhost                 : inti6023
# runhost                 : inti6015
# queue                   : rome
# user                    : tabernera
# group                   : ocre
# time limit              : 180 s
# memory limit            : 1875 MB
# core limit              : 8
# system                  : Linux inti6015 4.18.0-305.88.1.el8_4.x86_64 #1 SMP Thu Apr 6 10:22:46 EDT 2023 x86_64 x86_64 x86_64 GNU/Linux
################################################################

+ SCRIPT_PID=152345
+ set +x
+ /bin/bash -x /ccc/scratch/cont001/ocre/tabernera/.SPOOL/batch/scripts/script.2120436
+ unset _mlshdbg
+ '[' 1 = 1 ']'
+ case "$-" in
+ set +x
+ unset _mlshdbg
+ set -x
+ cd /ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1
+ ccc_mprun ./pmv_mpi -f mm/fidapm37.mtx
+ ccc_msub MPI_job16.sh
+ exit 0

################################################################
# date                     : 2023-05-17
# time                     : 11:19:34
# time limit               : 180 s
# time used                : 17 s
# cpus usage (avg)         : 41.18% 
################################################################

SLURM General Summary
--------------------
JobId=2120436 JobName=MPI_PMV
   UserId=tabernera(4224) GroupId=ocre(3000) MCS_label=cont001
   Priority=383451 Nice=0 Account=ocre@cpu QOS=normal
   JobState=RUNNING Reason=None Dependency=(null)
   Requeue=1 Restarts=0 BatchFlag=1 Reboot=0 ExitCode=0:0
   DerivedExitCode=0:0
   RunTime=00:00:17 TimeLimit=00:03:00 TimeMin=N/A
   SubmitTime=2023-05-17T11:19:16 EligibleTime=2023-05-17T11:19:17
   AccrueTime=2023-05-17T11:19:17
   StartTime=2023-05-17T11:19:17 EndTime=2023-05-17T11:22:17 Deadline=N/A
   SuspendTime=None SecsPreSuspend=0 LastSchedEval=2023-05-17T11:19:17 Scheduler=Main
   Partition=rome AllocNode:Sid=inti6023:362276
   ReqNodeList=(null) ExcNodeList=(null)
   NodeList=inti6015
   BatchHost=inti6015
   NumNodes=1 NumCPUs=8 NumTasks=8 CPUs/Task=1 ReqB:S:C:T=0:0:*:*
   TRES=cpu=8,mem=15000M,node=1,billing=8
   Socks/Node=* NtasksPerN:B:S:C=0:0:*:1 CoreSpec=*
   JOB_GRES=(null)
     Nodes=inti6015 CPU_IDs=0-15 Mem=15000 GRES=
   MinCPUsNode=1 MinMemoryCPU=1875M MinTmpDiskNode=0
   Features=(null) DelayBoot=00:00:00
   OverSubscribe=OK Contiguous=0 Licenses=fs_scratch,fs_work Network=(null)
   Command=/tmp/MPI_job8.sh_Rf9CUL
   WorkDir=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1
   StdErr=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1/sortie_8.e
   StdIn=/dev/null
   StdOut=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1/sortie_8.o
   Power=
   


SLURM Memory Summary
--------------------
JobID                 JobName     MaxRSS MaxRSSTask       MaxRSSNode     AveRSS 
------------ ---------------- ---------- ---------- ---------------- ---------- 
2120436               MPI_PMV                                                   
2120436.bat+            batch                                                   
2120436.ext+           extern                                                   
2120436.0             pmv_mpi     32248K          2         inti6015  29590.50K 

SLURM Accounting Summary
------------------------
         JobName          Account      NCPUS   NNodes   NTasks    Elapsed ExitCode      State 
---------------- ---------------- ---------- -------- -------- ---------- -------- ---------- 
         MPI_PMV         ocre@cpu          8        1            00:00:17      0:0    ENDING
           batch         ocre@cpu          8        1        1   00:00:17      0:0    ENDING
          extern         ocre@cpu          8        1        1   00:00:17      0:0    ENDING
         pmv_mpi         ocre@cpu          8        1        8   00:00:07      0:0  COMPLETED 

SLURM Energy report
-------------------
         JobName ReqCPUFreq AveCPUFreq  ConsumedEnergy
---------------- ---------- ----------  --------------
           batch          0          0        0.00 kWh
          extern          0          0        0.00 kWh
         pmv_mpi    Unknown   4728.67M        0.00 kWh
                                        --------------
                                Total:        0.00 kWh

Wed May 17 11:19:35 CEST 2023 : suppression MSUB_TMPDIR
