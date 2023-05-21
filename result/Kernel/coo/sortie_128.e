################################################################
# date                    : 2023-05-17
# time                    : 11:30:57
# jobname                 : MPI_PMV
# jobid                   : 2120483
# subhost                 : inti6015
# runhost                 : inti6018
# queue                   : rome
# user                    : tabernera
# group                   : ocre
# time limit              : 180 s
# memory limit            : 1875 MB
# core limit              : 128
# system                  : Linux inti6018 4.18.0-305.88.1.el8_4.x86_64 #1 SMP Thu Apr 6 10:22:46 EDT 2023 x86_64 x86_64 x86_64 GNU/Linux
################################################################

+ SCRIPT_PID=147932
+ set +x
+ /bin/bash -x /ccc/scratch/cont001/ocre/tabernera/.SPOOL/batch/scripts/script.2120483
+ unset _mlshdbg
+ '[' 1 = 1 ']'
+ case "$-" in
+ set +x
+ unset _mlshdbg
+ set -x
+ cd /ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1
+ ccc_mprun ./pmv_mpi -f mm/fidapm37.mtx -c
+ ccc_msub MPI_job256.sh
+ exit 0

################################################################
# date                     : 2023-05-17
# time                     : 11:31:49
# time limit               : 180 s
# time used                : 55 s
# cpus usage (avg)         : 81.82% 
################################################################

SLURM General Summary
--------------------
JobId=2120483 JobName=MPI_PMV
   UserId=tabernera(4224) GroupId=ocre(3000) MCS_label=cont001
   Priority=383451 Nice=0 Account=ocre@cpu QOS=normal
   JobState=RUNNING Reason=None Dependency=(null)
   Requeue=1 Restarts=0 BatchFlag=1 Reboot=0 ExitCode=0:0
   DerivedExitCode=0:0
   RunTime=00:00:55 TimeLimit=00:03:00 TimeMin=N/A
   SubmitTime=2023-05-17T11:30:53 EligibleTime=2023-05-17T11:30:53
   AccrueTime=2023-05-17T11:30:53
   StartTime=2023-05-17T11:30:54 EndTime=2023-05-17T11:33:54 Deadline=N/A
   SuspendTime=None SecsPreSuspend=0 LastSchedEval=2023-05-17T11:30:54 Scheduler=Main
   Partition=rome AllocNode:Sid=inti6015:178254
   ReqNodeList=(null) ExcNodeList=(null)
   NodeList=inti6018
   BatchHost=inti6018
   NumNodes=1 NumCPUs=128 NumTasks=128 CPUs/Task=1 ReqB:S:C:T=0:0:*:*
   TRES=cpu=128,mem=240000M,node=1,billing=128
   Socks/Node=* NtasksPerN:B:S:C=0:0:*:1 CoreSpec=*
   JOB_GRES=(null)
     Nodes=inti6018 CPU_IDs=0-255 Mem=240000 GRES=
   MinCPUsNode=1 MinMemoryCPU=1875M MinTmpDiskNode=0
   Features=(null) DelayBoot=00:00:00
   OverSubscribe=NO Contiguous=0 Licenses=fs_scratch,fs_work Network=(null)
   Command=/tmp/MPI_job128.sh_6R9qUh
   WorkDir=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1
   StdErr=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1/sortie_128.e
   StdIn=/dev/null
   StdOut=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1/sortie_128.o
   Power=
   


SLURM Memory Summary
--------------------
JobID                 JobName     MaxRSS MaxRSSTask       MaxRSSNode     AveRSS 
------------ ---------------- ---------- ---------- ---------------- ---------- 
2120483               MPI_PMV                                                   
2120483.bat+            batch                                                   
2120483.ext+           extern                                                   
2120483.0             pmv_mpi     77016K         44         inti6018   47207200 

SLURM Accounting Summary
------------------------
         JobName          Account      NCPUS   NNodes   NTasks    Elapsed ExitCode      State 
---------------- ---------------- ---------- -------- -------- ---------- -------- ---------- 
         MPI_PMV         ocre@cpu        128        1            00:00:55      0:0    ENDING
           batch         ocre@cpu        128        1        1   00:00:55      0:0    ENDING
          extern         ocre@cpu        128        1        1   00:00:55      0:0    ENDING
         pmv_mpi         ocre@cpu        128        1      128   00:00:45      0:0  COMPLETED 

SLURM Energy report
-------------------
         JobName ReqCPUFreq AveCPUFreq  ConsumedEnergy
---------------- ---------- ----------  --------------
           batch          0          0        0.00 kWh
          extern          0          0        0.00 kWh
         pmv_mpi    Unknown   5943.59M        0.01 kWh
                                        --------------
                                Total:        0.01 kWh

Wed May 17 11:31:50 CEST 2023 : suppression MSUB_TMPDIR
