#!/bin/bash
#SBATCH --job-name=FULL_BLAST                       
#SBATCH --output=/home/pp594/hw4/outputs/terminal_out/blast_all_t.txt     
#SBATCH --time=4:00:00                             
#SBATCH --chdir=/home/pp594/hw4                 
#SBATCH --mem=40000                              
#SBATCH --mail-type=FAIL
#SBATCH -c 64 

srun tee outputs/blast_all.txt
srun echo -e "------------------------------------------------\n" >> outputs/blast_all.txt 
srun date >> outputs/blast_all.txt
srun ./main /scratch/pp594/data/human.txt  /scratch/pp594/data/human_reads_2_trimmed.fa BLAST random 3057186663 | tee -a outputs/blast_all.txt 
srun echo -e "------------------------------------------------\n" >> outputs/blast_all.txt 
srun date >> outputs/blast_all.txt
srun ./main /scratch/pp594/data/human.txt  /scratch/pp594/data/human_reads_2_trimmed.fa BLAST normal 3057186663 | tee -a outputs/blast_all.txt 

