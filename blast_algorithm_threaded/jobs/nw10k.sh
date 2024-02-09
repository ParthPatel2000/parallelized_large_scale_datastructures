#!/bin/bash
#SBATCH --job-name=Needleman-Wunsch-threaded_10k                       
#SBATCH --output=/home/pp594/hw4/outputs/terminal_out/nw_10k_t.txt     
#SBATCH --time=24:00:00                             
#SBATCH --chdir=/home/pp594/hw4                 
#SBATCH --mem=16000                              
#SBATCH --mail-type=FAIL
#SBATCH -c 64 

srun make
srun echo -e "------------------------------------------------\n" >> outputs/nw_10k_o.txt 
srun date >> outputs/nw_10k_o.txt
srun ./main /scratch/pp594/data/human.txt  /scratch/pp594/data/human_reads_2_trimmed.fa NW random 10000 | tee -a outputs/nw_10k_o.txt 
