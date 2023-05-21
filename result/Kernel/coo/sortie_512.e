################################################################
# date                    : 2023-05-17
# time                    : 11:32:44
# jobname                 : MPI_PMV
# jobid                   : 2120530
# subhost                 : inti6015
# runhost                 : inti6012
# queue                   : rome
# user                    : tabernera
# group                   : ocre
# time limit              : 180 s
# memory limit            : 1875 MB
# core limit              : 512
# system                  : Linux inti6012 4.18.0-305.88.1.el8_4.x86_64 #1 SMP Thu Apr 6 10:22:46 EDT 2023 x86_64 x86_64 x86_64 GNU/Linux
################################################################

+ SCRIPT_PID=215330
+ set +x
+ /bin/bash -x /ccc/scratch/cont001/ocre/tabernera/.SPOOL/batch/scripts/script.2120530
+ unset _mlshdbg
+ '[' 1 = 1 ']'
+ case "$-" in
+ set +x
+ unset _mlshdbg
+ set -x
+ cd /ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1
+ ccc_mprun ./pmv_mpi -f mm/fidapm37.mtx -c
+ exit 0

################################################################
# date                     : 2023-05-17
# time                     : 11:33:37
# time limit               : 180 s
# time used                : 55 s
# cpus usage (avg)         : 85.45% 
################################################################

SLURM General Summary
--------------------
JobId=2120530 JobName=MPI_PMV
   UserId=tabernera(4224) GroupId=ocre(3000) MCS_label=cont001
   Priority=383450 Nice=0 Account=ocre@cpu QOS=normal
   JobState=RUNNING Reason=None Dependency=(null)
   Requeue=1 Restarts=0 BatchFlag=1 Reboot=0 ExitCode=0:0
   DerivedExitCode=0:0
   RunTime=00:00:56 TimeLimit=00:03:00 TimeMin=N/A
   SubmitTime=2023-05-17T11:32:34 EligibleTime=2023-05-17T11:32:34
   AccrueTime=2023-05-17T11:32:34
   StartTime=2023-05-17T11:32:42 EndTime=2023-05-17T11:35:42 Deadline=N/A
   SuspendTime=None SecsPreSuspend=0 LastSchedEval=2023-05-17T11:32:42 Scheduler=Main
   Partition=rome AllocNode:Sid=inti6015:182446
   ReqNodeList=(null) ExcNodeList=(null)
   NodeList=inti[6012,6015,6018-6019]
   BatchHost=inti6012
   NumNodes=4 NumCPUs=512 NumTasks=512 CPUs/Task=1 ReqB:S:C:T=0:0:*:*
   TRES=cpu=512,mem=937.50G,node=4,billing=512
   Socks/Node=* NtasksPerN:B:S:C=0:0:*:1 CoreSpec=*
   JOB_GRES=(null)
     Nodes=inti[6012,6015,6018-6019] CPU_IDs=0-255 Mem=240000 GRES=
   MinCPUsNode=1 MinMemoryCPU=1875M MinTmpDiskNode=0
   Features=(null) DelayBoot=00:00:00
   OverSubscribe=NO Contiguous=0 Licenses=fs_scratch,fs_work Network=(null)
   Command=/tmp/MPI_job512.sh_yF3bQA
   WorkDir=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1
   StdErr=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1/sortie_512.e
   StdIn=/dev/null
   StdOut=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1/sortie_512.o
   Power=
   


SLURM Memory Summary
--------------------
JobID                 JobName     MaxRSS MaxRSSTask       MaxRSSNode     AveRSS 
------------ ---------------- ---------- ---------- ---------------- ---------- 
2120530               MPI_PMV                                                   
2120530.bat+            batch                                                   
2120530.ext+           extern                                                   
2120530.0             pmv_mpi     76920K         23         inti6012   36808296 

SLURM Accounting Summary
------------------------
         JobName          Account      NCPUS   NNodes   NTasks    Elapsed ExitCode      State 
---------------- ---------------- ---------- -------- -------- ---------- -------- ---------- 
         MPI_PMV         ocre@cpu        512        4            00:00:56      0:0    ENDING
           batch         ocre@cpu        128        1        1   00:00:56      0:0    ENDING
          extern         ocre@cpu        512        4        4   00:00:56      0:0    ENDING
         pmv_mpi         ocre@cpu        512        4      512   00:00:47      0:0  COMPLETED 

SLURM Energy report
-------------------
         JobName ReqCPUFreq AveCPUFreq  ConsumedEnergy
---------------- ---------- ----------  --------------
           batch          0          0        0.00 kWh
          extern          0          0        0.00 kWh
         pmv_mpi    Unknown  20079.17M        0.02 kWh
                                        --------------
                                Total:        0.02 kWh

Wed May 17 11:33:39 CEST 2023 : suppression MSUB_TMPDIR
