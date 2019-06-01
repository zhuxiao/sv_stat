# SV_STAT
A tool for Structural Variation Statistics Evaluation

-------------------
SV_STAT is a tool for Structural Variation (SV) Statistics Evaluation. SV_STAT uses a user-called SV set and a benchmark data set as input. It first computes the tranditional metrics, such as the number of true positives (TPs), false positives (TPs), false negatives (FNs), recall, precision and F1 score; and it then computes the variant region size difference between the user-called variants and the corresponding ones in the benchmark data set by computing the distance bwtween their region centers, and it also computes the region size ratio for the two variant regions; and finally, it computes the statistics for different variant types with varies variant size.


## Compiling SV_STAT

The binary file can be generated by typing:
```sh
./autogen.sh
```
and the binary file 'sv_stat' will be output into the folder 'bin'.

## File format description

Before using SV_STAT, both the user-called SV set and the benchmark data set are in bed file format with the first 5 columns are below:
```sh
chromosome	start_ref_pos	end_ref_pos	SV_type	SV_len
```
For translocations, the file format should be bedpe before using SV_STAT, and the first 8 columns are listed as below:
```sh
chromosome1	start_ref_pos1	end_ref_pos1	chromosome2	start_ref_pos2	end_ref_pos2	SV_type	SV_len
```
The SV_type can be TRA or BND, and the SV_len will be 0.

Note that: In SV_STAT, all variant types, including translocations, can be stored together in the same file as the input, for example:
```sh
chr1	1167806	1168012	DEL	-206
chr1	1142384	1142384	INS	87
chr1	841980	843383	INV	1404
chr1	3327738	3329244	DUP	3013
chr1	1	481701	chr2	4273477	4539804	TRA	0
```		
For the second item, there is a insertion of size 87 base pairs at the 1142381 location of chr1, and for the fifth item, it is a translocation between chr1:1-481701 and chr2:4273477-4539804, and the 0 in the last second column means the SV_len which will be 0 for translocations.


## Usage

SV_STAT can be used to convert VCF/BED/CSV file format to bed or bedpe file format by typing:
```sh
sv_stat convert -f vcf var.vcf var.bed
sv_stat convert -f bed var.vcf var.bed
sv_stat convert -f csv var.vcf var.bed
```

Invalid long user-called regions can be removed by using -m option as they are two long to be a valid variant region, the command can be:
```sh
sv_stat stat -m 10000 user_sv.bed benchmark_sv.bed 
```

------------------------------------------------------------------------------
If you have problems or some suggestions, please contact: xzhu@hrbnu.edu.cn

---- Enjoy !!! -----

