#!/bin/bash
#SBATCH --job-name=blast-threaded                       
#SBATCH --output=/home/pp594/hw4/outputs/terminal_out/blast_1m_t.txt     
#SBATCH --time=4:00:00                             
#SBATCH --chdir=/home/pp594/hw4                 
#SBATCH --mem=40000                              
#SBATCH --mail-type=FAIL
#SBATCH -c 64 

srun echo -e "------------------------------------------------\n" >> outputs/blast_1m.txt 
srun date >> outputs/blast_1m.txt
srun ./main /scratch/pp594/data/human.txt  /scratch/pp594/data/human_reads_2_trimmed.fa BLAST random 1000000 | tee -a outputs/blast_1m.txt 
srun echo -e "------------------------------------------------\n" >> outputs/blast_1m.txt 
srun date >> outputs/blast_1m.txt
srun ./main /scratch/pp594/data/human.txt  /scratch/pp594/data/human_reads_2_trimmed.fa BLAST normal 1000000 | tee -a outputs/blast_1m.txt 

