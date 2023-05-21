################################################################
# date                    : 2023-05-17
# time                    : 11:19:08
# jobname                 : MPI_PMV
# jobid                   : 2120434
# subhost                 : inti6024
# runhost                 : inti6023
# queue                   : rome
# user                    : tabernera
# group                   : ocre
# time limit              : 180 s
# memory limit            : 1875 MB
# core limit              : 4
# system                  : Linux inti6023 4.18.0-305.88.1.el8_4.x86_64 #1 SMP Thu Apr 6 10:22:46 EDT 2023 x86_64 x86_64 x86_64 GNU/Linux
################################################################

+ SCRIPT_PID=362960
+ set +x
+ /bin/bash -x /ccc/scratch/cont001/ocre/tabernera/.SPOOL/batch/scripts/script.2120434
+ unset _mlshdbg
+ '[' 1 = 1 ']'
+ case "$-" in
+ set +x
+ unset _mlshdbg
+ set -x
+ cd /ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1
+ ccc_mprun ./pmv_mpi -f mm/fidapm37.mtx
+ ccc_msub MPI_job8.sh
+ exit 0

################################################################
# date                     : 2023-05-17
# time                     : 11:19:22
# time limit               : 180 s
# time used                : 16 s
# cpus usage (avg)         : 43.75% 
################################################################

SLURM General Summary
--------------------
JobId=2120434 JobName=MPI_PMV
   UserId=tabernera(4224) GroupId=ocre(3000) MCS_label=cont001
   Priority=383451 Nice=0 Account=ocre@cpu QOS=normal
   JobState=RUNNING Reason=None Dependency=(null)
   Requeue=1 Restarts=0 BatchFlag=1 Reboot=0 ExitCode=0:0
   DerivedExitCode=0:0
   RunTime=00:00:16 TimeLimit=00:03:00 TimeMin=N/A
   SubmitTime=2023-05-17T11:19:05 EligibleTime=2023-05-17T11:19:05
   AccrueTime=2023-05-17T11:19:05
   StartTime=2023-05-17T11:19:06 EndTime=2023-05-17T11:22:06 Deadline=N/A
   SuspendTime=None SecsPreSuspend=0 LastSchedEval=2023-05-17T11:19:06 Scheduler=Main
   Partition=rome AllocNode:Sid=inti6024:122681
   ReqNodeList=(null) ExcNodeList=(null)
   NodeList=inti6023
   BatchHost=inti6023
   NumNodes=1 NumCPUs=4 NumTasks=4 CPUs/Task=1 ReqB:S:C:T=0:0:*:*
   TRES=cpu=4,mem=7500M,node=1,billing=4
   Socks/Node=* NtasksPerN:B:S:C=0:0:*:1 CoreSpec=*
   JOB_GRES=(null)
     Nodes=inti6023 CPU_IDs=208-215 Mem=7500 GRES=
   MinCPUsNode=1 MinMemoryCPU=1875M MinTmpDiskNode=0
   Features=(null) DelayBoot=00:00:00
   OverSubscribe=OK Contiguous=0 Licenses=fs_scratch,fs_work Network=(null)
   Command=/tmp/MPI_job4.sh_VebaIn
   WorkDir=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1
   StdErr=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1/sortie_4.e
   StdIn=/dev/null
   StdOut=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1/sortie_4.o
   Power=
   


SLURM Memory Summary
--------------------
JobID                 JobName     MaxRSS MaxRSSTask       MaxRSSNode     AveRSS 
------------ ---------------- ---------- ---------- ---------------- ---------- 
2120434               MPI_PMV                                                   
2120434.bat+            batch                                                   
2120434.ext+           extern                                                   
2120434.0             pmv_mpi     31160K          1         inti6023     25798K 

SLURM Accounting Summary
------------------------
         JobName          Account      NCPUS   NNodes   NTasks    Elapsed ExitCode      State 
---------------- ---------------- ---------- -------- -------- ---------- -------- ---------- 
         MPI_PMV         ocre@cpu          4        1            00:00:16      0:0    ENDING
           batch         ocre@cpu          4        1        1   00:00:16      0:0    ENDING
          extern         ocre@cpu          4        1        1   00:00:16      0:0    ENDING
         pmv_mpi         ocre@cpu          4        1        4   00:00:07      0:0  COMPLETED 

SLURM Energy report
-------------------
         JobName ReqCPUFreq AveCPUFreq  ConsumedEnergy
---------------- ---------- ----------  --------------
           batch          0          0        0.00 kWh
          extern          0          0        0.00 kWh
         pmv_mpi    Unknown   4822.12M        0.00 kWh
                                        --------------
                                Total:        0.00 kWh

Wed May 17 11:19:23 CEST 2023 : suppression MSUB_TMPDIR
