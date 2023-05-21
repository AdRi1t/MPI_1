################################################################
# date                    : 2023-05-17
# time                    : 11:31:49
# jobname                 : MPI_PMV
# jobid                   : 2120494
# subhost                 : inti6018
# runhost                 : inti6015
# queue                   : rome
# user                    : tabernera
# group                   : ocre
# time limit              : 180 s
# memory limit            : 1875 MB
# core limit              : 256
# system                  : Linux inti6015 4.18.0-305.88.1.el8_4.x86_64 #1 SMP Thu Apr 6 10:22:46 EDT 2023 x86_64 x86_64 x86_64 GNU/Linux
################################################################

+ SCRIPT_PID=183104
+ /bin/bash -x /ccc/scratch/cont001/ocre/tabernera/.SPOOL/batch/scripts/script.2120494
+ set +x
+ unset _mlshdbg
+ '[' 1 = 1 ']'
+ case "$-" in
+ set +x
+ unset _mlshdbg
+ set -x
+ cd /ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1
+ ccc_mprun ./pmv_mpi -f mm/fidapm37.mtx -c
+ ccc_msub MPI_job512.sh
+ exit 0

################################################################
# date                     : 2023-05-17
# time                     : 11:32:40
# time limit               : 180 s
# time used                : 54 s
# cpus usage (avg)         : 81.48% 
################################################################

SLURM General Summary
--------------------
JobId=2120494 JobName=MPI_PMV
   UserId=tabernera(4224) GroupId=ocre(3000) MCS_label=cont001
   Priority=383451 Nice=0 Account=ocre@cpu QOS=normal
   JobState=RUNNING Reason=None Dependency=(null)
   Requeue=1 Restarts=0 BatchFlag=1 Reboot=0 ExitCode=0:0
   DerivedExitCode=0:0
   RunTime=00:00:54 TimeLimit=00:03:00 TimeMin=N/A
   SubmitTime=2023-05-17T11:31:43 EligibleTime=2023-05-17T11:31:43
   AccrueTime=2023-05-17T11:31:43
   StartTime=2023-05-17T11:31:46 EndTime=2023-05-17T11:34:46 Deadline=N/A
   SuspendTime=None SecsPreSuspend=0 LastSchedEval=2023-05-17T11:31:46 Scheduler=Main
   Partition=rome AllocNode:Sid=inti6018:147266
   ReqNodeList=(null) ExcNodeList=(null)
   NodeList=inti[6015,6019]
   BatchHost=inti6015
   NumNodes=2 NumCPUs=256 NumTasks=256 CPUs/Task=1 ReqB:S:C:T=0:0:*:*
   TRES=cpu=256,mem=480000M,node=2,billing=256
   Socks/Node=* NtasksPerN:B:S:C=0:0:*:1 CoreSpec=*
   JOB_GRES=(null)
     Nodes=inti[6015,6019] CPU_IDs=0-255 Mem=240000 GRES=
   MinCPUsNode=1 MinMemoryCPU=1875M MinTmpDiskNode=0
   Features=(null) DelayBoot=00:00:00
   OverSubscribe=NO Contiguous=0 Licenses=fs_scratch,fs_work Network=(null)
   Command=/tmp/MPI_job256.sh_RXEBm9
   WorkDir=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1
   StdErr=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1/sortie_256.e
   StdIn=/dev/null
   StdOut=/ccc/work/cont001/ocre/tabernera/MPI/MPI_PMV_1.1/sortie_256.o
   Power=
   


SLURM Memory Summary
--------------------
JobID                 JobName     MaxRSS MaxRSSTask       MaxRSSNode     AveRSS 
------------ ---------------- ---------- ---------- ---------------- ---------- 
2120494               MPI_PMV                                                   
2120494.bat+            batch                                                   
2120494.ext+           extern                                                   
2120494.0             pmv_mpi     76448K         64         inti6015   58381664 

SLURM Accounting Summary
------------------------
         JobName          Account      NCPUS   NNodes   NTasks    Elapsed ExitCode      State 
---------------- ---------------- ---------- -------- -------- ---------- -------- ---------- 
         MPI_PMV         ocre@cpu        256        2            00:00:54      0:0    ENDING
           batch         ocre@cpu        128        1        1   00:00:54      0:0    ENDING
          extern         ocre@cpu        256        2        2   00:00:54      0:0    ENDING
         pmv_mpi         ocre@cpu        256        2      256   00:00:44      0:0  COMPLETED 

SLURM Energy report
-------------------
         JobName ReqCPUFreq AveCPUFreq  ConsumedEnergy
---------------- ---------- ----------  --------------
           batch          0          0        0.00 kWh
          extern          0          0        0.00 kWh
         pmv_mpi    Unknown  20558.06M        0.01 kWh
                                        --------------
                                Total:        0.01 kWh

Wed May 17 11:32:41 CEST 2023 : suppression MSUB_TMPDIR
