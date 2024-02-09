#!/bin/bash
#SBATCH --job-name=blast-threaded                       
#SBATCH --output=/home/pp594/hw4/outputs/terminal_out/blast_10k_t.txt     
#SBATCH --time=4:00:00                             
#SBATCH --chdir=/home/pp594/hw4                 
#SBATCH --mem=40000                              
#SBATCH --mail-type=FAIL
#SBATCH -c 64 

srun echo -e "------------------------------------------------\n" >> outputs/blast_10k.txt 
srun date >> outputs/blast_10k.txt
srun ./main /scratch/pp594/data/human.txt  /scratch/pp594/data/human_reads_2_trimmed.fa BLAST random 10000 | tee -a outputs/blast_10k.txt 
srun echo -e "------------------------------------------------\n" >> outputs/blast_10k.txt 
srun date >> outputs/blast_10k.txt
srun ./main /scratch/pp594/data/human.txt  /scratch/pp594/data/human_reads_2_trimmed.fa BLAST normal 10000 | tee -a outputs/blast_10k.txt 

