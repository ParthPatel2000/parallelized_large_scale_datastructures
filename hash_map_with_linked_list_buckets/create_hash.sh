#!/bin/bash
#SBATCH --job-name=hash_threaded_64c                        
#SBATCH --output=/home/pp594/hw3/outputs/job_op_threaded.txt     
#SBATCH --time=20:00                             
#SBATCH --chdir=/home/pp594/hw3                 
#SBATCH --mem=16000                              
#SBATCH --mail-type=FAIL


# load a module, for example

# Run your application: precede the application command with 'srun'
srun make clean
srun make
srun echo -e "------------------------------------------------\n" >> outputs/threaded_op.txt 
srun date >> outputs/threaded_op.txt
srun echo -e "\n1M\n" >> outputs/threaded_op.txt 
srun  ./main /common/contrib/classroom/inf503/genomes/human.txt /common/contrib/classroom/inf503/human_reads_2_trimmed.fa 1000000 hash| tee -a outputs/threaded_op.txt
srun echo -e "\n10M\n" >> outputs/threaded_op.txt 
srun  ./main /common/contrib/classroom/inf503/genomes/human.txt /common/contrib/classroom/inf503/human_reads_2_trimmed.fa 10000000 hash| tee -a outputs/threaded_op.txt
srun echo -e "\n30M\n" >> outputs/threaded_op.txt 
srun  ./main /common/contrib/classroom/inf503/genomes/human.txt /common/contrib/classroom/inf503/human_reads_2_trimmed.fa 30000000 hash| tee -a outputs/threaded_op.txt
srun echo -e "\n60M\n" >> outputs/threaded_op.txt 
srun  ./main /common/contrib/classroom/inf503/genomes/human.txt /common/contrib/classroom/inf503/human_reads_2_trimmed.fa 60000000 hash| tee -a outputs/threaded_op.txt

