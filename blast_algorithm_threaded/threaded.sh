#!/bin/bash
#SBATCH --job-name=Needleman-Wunsch-threaded                       
#SBATCH --output=/home/pp594/hw4/outputs/needleman_terminal_op.txt     
#SBATCH --time=20:00                             
#SBATCH --chdir=/home/pp594/hw4                 
#SBATCH --mem=16000                              
#SBATCH --mail-type=FAIL
#SBATCH -c 64 

# load a module, for example

# Run your application: precede the application command with 'srun'
srun make clean
srun make
srun echo -e "------------------------------------------------\n" >> outputs/needleman_op.txt 
srun date >> outputs/needleman_op.txt
srun  make run | tee -a outputs/needleman_op.txt 
