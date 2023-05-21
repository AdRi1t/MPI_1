################################################################
# date                    : 2023-05-17
# time                    : 11:20:49
# jobname                 : MPI_PMV
# jobid                   : 2120444
# subhost                 : inti6016
# runhost                 : inti6012
# queue                   : rome
# user                    : tabernera
# group                   : ocre
# time limit              : 180 s
# memory limit            : 1875 MB
# core limit              : 256
# system                  : Linux inti6012 4.18.0-305.88.1.el8_4.x86_64 #1 SMP Thu Apr 6 10:22:46 EDT 2023 x86_64 x86_64 x86_64 GNU/Linux
################################################################

+ SCRIPT_PID=202327
+ set +x
+ /bin/bash -x /ccc/scratch/cont001/ocre/tabernera/.SPOOL/batch/scripts/script.2120444
+ unset _mlshdbg
+ '[' 1 = 1 ']'
+ case "$-" in
+ set +x
+ unset _mlshdbg
+ set -x
+ cd /ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1
+ ccc_mprun ./pmv_mpi -f mm/fidapm37.mtx
+ ccc_msub MPI_job512.sh
+ exit 0

################################################################
# date                     : 2023-05-17
# time                     : 11:21:31
# time limit               : 180 s
# time used                : 45 s
# cpus usage (avg)         : 80.00% 
################################################################

SLURM General Summary
--------------------
JobId=2120444 JobName=MPI_PMV
   UserId=tabernera(4224) GroupId=ocre(3000) MCS_label=cont001
   Priority=383451 Nice=0 Account=ocre@cpu QOS=normal
   JobState=RUNNING Reason=None Dependency=(null)
   Requeue=1 Restarts=0 BatchFlag=1 Reboot=0 ExitCode=0:0
   DerivedExitCode=0:0
   RunTime=00:00:45 TimeLimit=00:03:00 TimeMin=N/A
   SubmitTime=2023-05-17T11:20:46 EligibleTime=2023-05-17T11:20:46
   AccrueTime=2023-05-17T11:20:46
   StartTime=2023-05-17T11:20:46 EndTime=2023-05-17T11:23:46 Deadline=N/A
   SuspendTime=None SecsPreSuspend=0 LastSchedEval=2023-05-17T11:20:46 Scheduler=Main
   Partition=rome AllocNode:Sid=inti6016:158484
   ReqNodeList=(null) ExcNodeList=(null)
   NodeList=inti[6012,6015]
   BatchHost=inti6012
   NumNodes=2 NumCPUs=256 NumTasks=256 CPUs/Task=1 ReqB:S:C:T=0:0:*:*
   TRES=cpu=256,mem=480000M,node=2,billing=256
   Socks/Node=* NtasksPerN:B:S:C=0:0:*:1 CoreSpec=*
   JOB_GRES=(null)
     Nodes=inti[6012,6015] CPU_IDs=0-255 Mem=240000 GRES=
   MinCPUsNode=1 MinMemoryCPU=1875M MinTmpDiskNode=0
   Features=(null) DelayBoot=00:00:00
   OverSubscribe=NO Contiguous=0 Licenses=fs_scratch,fs_work Network=(null)
   Command=/tmp/MPI_job256.sh_CTolQA
   WorkDir=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1
   StdErr=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1/sortie_256.e
   StdIn=/dev/null
   StdOut=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1/sortie_256.o
   Power=
   


SLURM Memory Summary
--------------------
JobID                 JobName     MaxRSS MaxRSSTask       MaxRSSNode     AveRSS 
------------ ---------------- ---------- ---------- ---------------- ---------- 
2120444               MPI_PMV                                                   
2120444.bat+            batch                                                   
2120444.ext+           extern                                                   
2120444.0             pmv_mpi     76840K         57         inti6012   55089488 

SLURM Accounting Summary
------------------------
         JobName          Account      NCPUS   NNodes   NTasks    Elapsed ExitCode      State 
---------------- ---------------- ---------- -------- -------- ---------- -------- ---------- 
         MPI_PMV         ocre@cpu        256        2            00:00:45      0:0    ENDING
           batch         ocre@cpu        128        1        1   00:00:45      0:0    ENDING
          extern         ocre@cpu        256        2        2   00:00:45      0:0    ENDING
         pmv_mpi         ocre@cpu        256        2      256   00:00:36      0:0  COMPLETED 

SLURM Energy report
-------------------
         JobName ReqCPUFreq AveCPUFreq  ConsumedEnergy
---------------- ---------- ----------  --------------
           batch          0          0        0.00 kWh
          extern          0          0        0.00 kWh
         pmv_mpi    Unknown  31042.93M        0.01 kWh
                                        --------------
                                Total:        0.01 kWh

Wed May 17 11:21:32 CEST 2023 : suppression MSUB_TMPDIR
