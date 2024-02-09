#!/bin/bash
#SBATCH --job-name=Needleman-Wunsch-threaded                       
#SBATCH --output=/home/pp594/hw4/outputs/terminal_out/nwr_100k_t.txt     
#SBATCH --time=30:00:00                             
#SBATCH --chdir=/home/pp594/hw4                 
#SBATCH --mem=16000                              
#SBATCH --mail-type=FAIL
#SBATCH -c 64 

srun make
srun echo -e "------------------------------------------------\n" >> outputs/nwr_100k_o.txt 
srun date >> outputs/nwr_100k_o.txt
srun ./main /scratch/pp594/data/human.txt  /scratch/pp594/data/human_reads_2_trimmed.fa NW random 5000 | tee -a outputs/nwr_100k_o.txt 
