#!/bin/bash
#SBATCH --job-name=hash_threaded_64c                        
#SBATCH --output=/home/pp594/hw3/outputs/job_op_threaded.txt     
#SBATCH --time=20:00                             
#SBATCH --chdir=/home/pp594/hw3                 
#SBATCH --mem=16000                              
#SBATCH --mail-type=FAIL
#SBATCH -c 64

# load a module, for example

# Run your application: precede the application command with 'srun'
srun make clean
srun make
srun echo -e "------------------------------------------------\n" >> outputs/threaded_op.txt 
srun date >> outputs/threaded_op.txt
srun  make search | tee -a outputs/threaded_op.txt 
