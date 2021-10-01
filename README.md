# SV_STAT
A tool for Structural Variation Statistics Evaluation

-------------------
SV_STAT is a tool for Structural Variation (SV) Statistics Evaluation. SV_STAT uses a user-called SV set and a benchmark data set as input. It first computes the tranditional metrics, such as the number of true positives (TPs), false positives (FPs), false negatives (FNs), recall, precision and F1 score; and it then computes the variant region size difference between the user-called variants and the corresponding ones in the benchmark data set by computing the distance bwtween their region centers, and it also computes the region size ratio for the two variant regions; and finally, it computes the statistics for variants with vary region lengths.


## Prerequisites
SV_STAT depends on the following libraries and tools:
* HTSlib (http://www.htslib.org/download/)
* g++ (v4.7 or higher which supports c++11)

The above library and tools should be installed before compiling SV_STAT.

## Compiling SV_STAT

The binary file can be generated by typing:
```sh
$ git clone https://github.com/zhuxiao/sv_stat.git
$ cd sv_stat/
$ ./autogen.sh
```
And the binary file `sv_stat` will be output into the folder `bin` in this package directory.

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
For the second item, there is a insertion of size 87 base pairs at the 1142381 location of chr1, and for the fifth item, it is a translocation between chr1:1-481701 and chr2:4273477-4539804, and the 0 in the last second column means the SV_len which will be 0 for translocations or translocation breakpoints.


## Usage
There are two commands for SV_STAT: `convert` and `stat`. The help information are below:
```sh
$ sv_stat
Program: SV_STAT (A tool for Structural Variant Statistics Evaluation)
Version: 0.4.2

Usage:  sv_stat  <command> [options]

Commands:
     convert      convert SV results to 5-column BED (or 8-column BEDPE) file format
     stat         compute the SV statistics
```

### `convert` command
SV_STAT can be used to convert VCF/BED/CSV file format to bed or bedpe file format by typing:
```sh
$ sv_stat convert -f vcf var.vcf var.bed
```
or
```sh
$ sv_stat convert -f bed var.bed var_new.bed
```
or
```sh
$ sv_stat convert -f csv var.csv var.bed
```

And the help information are below:
```sh
$ sv_stat convert
Program: SV_STAT (A tool for Structural Variant Statistics Evaluation)
Version: 0.4.2

Usage:  sv_stat convert [options] <infile> <outfile>

Options:
     -f STR       SV input file format (required):
                  bed: BED/BEDPE format
                  vcf: VCF format
                  csv: CSV format
     -o FILE      output directory: [output]
     -r INT       remove redundant variant items [1]: 1 for yes, 0 for no
     -R FILE      redundant variant items file: [redundant_items.bed]
     -h           show this help message and exit
```

### `stat` command
Invalid long user-called regions can be removed by using `-m` option as they are too long to be valid variant regions. The command could be:
```sh
$ sv_stat stat -m 10000 user_sv.bed benchmark_sv.bed 
```
And the help information are shown below:
```sh
$ sv_stat stat
Program: SV_STAT (A tool for Structural Variant Statistics Evaluation)
Version: 0.4.2

Usage:  sv_stat stat [options] <USER_SV_FILE> <BENCHMARK_SV_FILE>

Description:
     USER_SV_FILE         User called SV result file.
     BENCHMARK_SV_FILE    Benchmark SV file.

Options:
     -m INT       valid maximal region size for statistics: [0]
                  0 is for all variant size are valid, and while positive
                  values are for the valid maximal region size, then longer
                  regions are omitted and saved to the file specified with -l
     -s INT       overlap extend size: [100]
     -t INT       number of threads [0]. 0 for the maximal number of threads
                  in machine
     -o FILE      output directory: [output]
     -l FILE      file name for long SV regions: [long_sv_reg.bed]
     -h           show this help message and exit
```


## Draw statistical figures (To do ...)
Figures can be drawn for more intuitive and detailed illustration for the four statistical categories. Statistical figures can be draw by typing:
```sh
$ draw_command
```


## Output Result Description
There are 4 statistical categories for `stat` command results, which will be saved into the following 4 folders respectively:
* __`1_ref_reg_size_stat`__: variant region size statistics (and the statistical figures) in reference.
* __`2_num_stat`__: the classical number statistics (and the statistical figures), e.g. TP, FP, FN, Recall, Precision, F1 score.
* __`3_size_dif_stat`__: the region size difference and ratio statistics (and statistical figures) for the overlapped variants between the user-called data set and the benchmark data set.
* __`4_size_num_stat`__: the classical number statistics (and the statistical figures) for variants with vary region lengths.
Moreover, the overall simplified statistics will be output to the terminal screen, and these screen results will be saved to the file `stat_screen` in the output directory.


------------------------------------------------------------------------------
## Contact
If you have problems or some suggestions, please contact: zhuxiao_hit@yeah.net without hesitation.

---- Enjoy !!! -----

